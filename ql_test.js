import http from 'k6/http';
import { check } from 'k6';


export const options = {
    // Сценарий нагрузки
    stages: [
        { duration: '1m', target: 10 },  // Разогрев: за 1 минуту выходим на 10 VU
        { duration: '3m', target: 20 },  // Плавный рост до 50 VU за 3 минуты
        { duration: '5m', target: 20 },  // Постоянная нагрузка 50 VU в течение 5 минут
        { duration: '3m', target: 20 },  // Снижение до 10 VU
        { duration: '1m', target: 0 },   // Завершение
    ],

    // Контрольные точки (thresholds)
    thresholds: {
        // 95% запросов должны выполняться быстрее, чем за 500 мс
        http_req_duration: ['p(95)<500'],

        // Доля успешных проверок должна быть выше 95%t6y
        checks: ['rate>0.95'],

        // Должно быть не менее 1000 запросов за всё время теста
        http_reqs: ['count>1000'],
    },
};



const jsonData = JSON.parse(open('/data/all_data.json')); // Загрузка JSON-файла как строки и преобразование в объект
const token = open('/info/token.txt').trim(); // Фиксированное значение 
const tarantool_url = 'http://x5id-tdg2-test.x5.ru:8190/graphql'; // URL куда отправлять запросы на tdg

// URL's по видам запросов на тест
const test_urls = [

    // POST /get Запрос данных клиента из профиля
    /*{
        url: "https://id-test.x5.ru/api/secure/client-service/get",
        percentage: 39,
    },*/

    // GET /get Получение карт пользователя по .... Нетворк all
    {
        url: "https://id-test.x5.ru/api/secure/card-service/all/get",
        percentage: 35,
    },


    // POST /getByCard Получение данных клиента по карте
    /*{
        url: "https://id-test.x5.ru/api/secure/client-service/getByCard",
        percentage: 21,
    },*/

    //GET /get Получение карт пользователя, по номеру телефона. Нетворк tcx
    {
        url: "https://id-test.x5.ru/api/secure/card-service/tcx/get",
        percentage: 2,
    },


    // POST /id/get Поиск cipId клиента по номеру телефона
    /*{
        url: "https://id-test.x5.ru/api/secure/client-service/id/get",
        percentage: 1,
    },
    */


    // GET /get Получение карт пользователя, по номеру телефона. Нетворк tc5
    {
        url: "https://id-test.x5.ru/api/secure/card-service/tc5/get",
        percentage: 1,
    },
];


// выбор URL на основе распределения запросов
function getRequestConfigByPercentage() {
    const random = Math.random() * 100;
    let cumulative = 0;

    for (const entry of test_urls) {
        cumulative += entry.percentage;
        if (random < cumulative) {
            return entry;
        }
    }
    return test_urls[test_urls.length - 1];
}

// Выбор произвольного пользователя из общей базы
function getRandomUserProfile() {
    const index = Math.floor(Math.random() * jsonData.data.sg_user_profile.length);
    return jsonData.data.sg_user_profile[index];
}


// Функция проверки наличия у пользователя массива cip_relation_ids с cip_id
function hasCipRelation(userProfile) {
    return Array.isArray(userProfile.cip_relation_ids) && userProfile.cip_relation_ids.length > 0;
}

// Функция проверки, что у пользователя есть массив привязанных карт
function hasLinkedCards(userProfile) {
    return Array.isArray(userProfile.linked_cards) && userProfile.linked_cards.length > 0;
}

// Функция для проверки и установки значения cip_id для использования значения в запросах
function check_and_install_cip(user) {
    let cipId = false;
    if (hasCipRelation(user)) {
        cipId = user.cip_relation_ids[0].cip_id
        return cipId
    }
}


// Функции для формирования запросов POST /get
// Пункт 1: Поиск external_id профиля клиента по cip_id
function post_get_part1(user) {

    let cipId = check_and_install_cip(user);
    if (!cipId) {
        return false;
    }

    const query = `query($cipId: String!) {
        cip_relation_ids(cip_id: $cipId) {
            golden_id,
            system,
            external_id_long
        }
    }`;
    return JSON.stringify({ query, variables: { cipId } });
}
// Пункт 2: Поиск по внешнему id профиля. Запроса автогенерируемый в зависимости от профиля:
function post_get_part2(user) {
    // TODO: пока что формируем запрос не на все поля, а на какие-то. В оригинальных запросах обращение на
    // 20+ и 30+ полей

    let cipId = check_and_install_cip(user);
    if (!cipId) {
        return false;
    }

    const commercialNetwork = cipId.slice(0, 3).toLowerCase();

    /*Фараза "Как правило это cip_id" в инструкции звучит ненадежно, но пока что id это цифры из cip_id*/
    const id = parseInt(cipId.replace(/^\D+/, ''), 10); // Преобразуем в целое число

    let query = '';
    let variables = { id };

    if (commercialNetwork === 'idx') {
        query = `query($id: Long!) { sg_user_profile(x5id: $id) { mobilePhone } }`;
    } else if (commercialNetwork === 'tc5') {
        query = `query($id: Long!) { clm5_customers(cus_id: $id) { cus_last_name } }`;
    } else if (commercialNetwork === 'tcx') {
        query = `query($id: Long!) { clm3_cardholders(crh_id: $id) { crh_phone } }`;
    } else {
        // В случае если у пользователя сеть сломана или неизвестна, то запрос составлен не будет
        return false;
    }

    return JSON.stringify({ query, variables });
}


// Функции для формирования POST /getByCard
// Пункт 1: Получение профиля по карте
function post_getbycard_part1(user, queryField) {
    // А если сеть idx?? Что тогда?
    // Пока что в запрос отправляем не все поля

    if (!hasLinkedCards(user)) {
        return false;
    }

    const { cardNo, commercialNetwork } = user.linked_cards[0];

    let query = '';
    let variables = { cardNo };

    if (commercialNetwork.toLowerCase() === 'tcx') {
        query = `query($cardNo: String!) {
            clm3_cards(crd_no: $cardNo) {
                settings: cardholder { crh_status },
                cardholder { crh_phone }
            }
        }`;
    } else if (commercialNetwork.toLowerCase() === 'tc5') {
        query = `query($cardNo: String!) {
            clm5_identifiers(idn_no: $cardNo) {
                settings: customer { cus_status },
                customer { cus_user_ip }
            }
        }`;
    } else {
        // В случае непопадания в предложенные сети функция отменяет формирование запроса
        return false
    }

    return JSON.stringify({ query, variables });
}
// Пункт 2: Получение профиля по номеру телефона
function post_getbycard_part2(user) {
    // А октуда мы берем сеть в данном случае? Из linken_card или из cip_id???????????????????????????

    // Если нет номера телефона у пользователя, то запрос не может быть сформирован
    if (!user?.mobilePhone) {
        return false;
    }

    // Далее проверяем, что сеть можем достать хотя бы из какого-то места: либо linked_cards, либо cip_relation_ids
    if (hasLinkedCards(user) == false && hasCipRelation(user) == false) {
        return false;
    }

    let mobilePhone = user.mobilePhone;
    let commercialNetwork = null;
    if (hasLinkedCards(user)) {
        commercialNetwork = user.linked_cards[0].commercialNetwork.toLowerCase();
    }
    else if (hasCipRelation(user)) {
        commercialNetwork = user.cip_relation_ids[0].cip_id.slice(0, 3).toLowerCase();
    }
    else {
        return false;
    }


    let query = '';
    let variables = { phone: mobilePhone };

    if (commercialNetwork === 'tcx') {
        query = `query($phone: String!) {
            clm3_cardholders(crh_mobile: $phone) {
                cards { crd_no }
            }
        }`;
    } else if (commercialNetwork === 'tc5') {
        query = `query($phone: String!) {
            clm5_customers(addr_mobile: $phone) {
                cards { idn_no }
            }
        }`;
    } else {
        return false;
    }

    return JSON.stringify({ query, variables });
}




// Функции для формирования POST /id/get запросов
// Пункт 1: В зависимости от торговой сети формируется запрос на поиск профиля по номеру телефона:
function post_id_get_part1(user) {

    // У пользователя обязан быть номер телефона, иначе нечего проверять
    if (!user.mobilePhone) {
        return false;
    }
    const phone = user.mobilePhone;

    // Дальше пытаемся найти торговую сеть пользователя
    // Она есть либо в массиве cip_relation_ids либо в linked_cards
    if ((!hasLinkedCards(user)) && (!hasCipRelation(user))) {
        return false;
    }
    let commercialNetwork = null;
    if (hasLinkedCards(user)) {
        commercialNetwork = user.linked_cards[0].commercialNetwork.toLowerCase();
    }
    else if (hasCipRelation(user)) {
        commercialNetwork = user.cip_relation_ids[0].cip_id.slice(0, 3).toLowerCase();
    }
    else {
        return false;
    }

    let query = '';
    let variables = {};

    if (commercialNetwork === 'tcx') {
        query = `query ($phone: String!) {
            clm3_cardholders(crh_mobile: $phone, crh_status: "A") {
                cip_relation_ids(system: "TCX") {
                    cip_id
                }
            }
        }`;
        variables = { phone };
    } else if (commercialNetwork === 'tc5') {
        query = `query ($phone: String!) {
            clm5_customers(addr_mobile: $phone, cus_status: "A") {
                cip_relation_ids(system: "TC5") {
                    cip_id
                }
            }
        }`;
        variables = { phone };
    } else if (commercialNetwork === 'idx') {
        query = `query ($phone_with_code: String!) {
            clm5_customers(addr_mobile: $phone_with_code, cus_status: "A") {
                cip_relation_ids(system: "IDX") {
                    cip_id
                }
            }
        }`;
        variables = { phone_with_code: phone.slice(1) }; // Убираем первый символ (код страны)
    } else {
        return false; // Если мы не поняли, что за сеть, то отменяем запрос
    }

    return JSON.stringify({ query, variables });
}
// Пункт 2: Если была передана почта
function post_id_get_part2(user) {
    // У пользователя обязан быть номер телефона, иначе нечего проверять
    if (!user.mail) {
        return false;
    }
    const email = user.mail;

    // Дальше пытаемся найти торговую сеть пользователя
    // Она есть либо в массиве cip_relation_ids либо в linked_cards
    if ((!hasLinkedCards(user)) && (!hasCipRelation(user))) {
        return false;
    }
    let commercialNetwork = null;
    if (hasLinkedCards(user)) {
        commercialNetwork = user.linked_cards[0].commercialNetwork.toLowerCase();
    }
    else if (hasCipRelation(user)) {
        commercialNetwork = user.cip_relation_ids[0].cip_id.slice(0, 3).toLowerCase();
    }
    else {
        return false;
    }

    let query = '';
    let variables = { email };

    if (commercialNetwork === 'tc5') {
        query = `query($email: String!) {
            clm5_customers(addr_email_insensitivity: $email, cus_status: "A") {
                cus_id,
                cip_changed_date
            }
        }`;
    } else if (commercialNetwork === 'idx') {
        query = `query($email: String!) {
            sg_user_profile(mail_insensitivity: $email, first: 100) {
                x5id,
                updated
            }
        }`;
    } else {
        return false
    }

    return JSON.stringify({ query, variables });
}




// Функции обработки GET {network}/get запросов
// Пункт 1: Получение списка активных карт по номеру телефона
function get_network_part1(user) {
    if (!user.mobilePhone) {
        return false;
    }

    const query = `query ($phone: String!) {
        clm5_customers(addr_mobile: $phone, cus_status: "A") {
            cards { idn_no }
        }
    }`;
    // Номер телефона ведь всегда начинается с расширения 7?
    const variables = { phone: user.mobilePhone.slice(1) };
    return JSON.stringify({ query, variables });
}
// Пункт 2: Поиск профиля TC5
function get_network_part2(user) {
    // Пока что запрашиваю не 30+ полей, а одно
    if (!user.mobilePhone) {
        return false;
    }

    const query = `query ($phone: String!) {
        clm5_customers(addr_mobile: $phone, cus_status: "A") {
            cus_user_ip
        }
    }`;
    // Предполагаю, что номер телефона начинается с расширения 7
    const variables = { phone: user.mobilePhone.slice(1) };
    return JSON.stringify({ query, variables });
}
// Пункт 3: ЛОЙМАКС?????????????????
// Пункт 4.1: Поиск карт в бд
function get_network_part4_1(cardNo) {
    if (!cardNo) {
        return false;
    }

    const query = `query($cardNo: String!) {
        cardByCardNo: clm5_identifiers(idn_no: $cardNo) {
            accNo: idn_acc_id
            cardNo: idn_no
            cardType: idn_type_code
            cardStatusRelation: status { cardStatus: cis_status_api_name }
            truncPan: idn_pan
            customer: customer { customerMainIdNo: cus_main_identifier_no }
            rawStatus: idn_status
            cipChangedDate: cip_changed_date
            block: block
            is_deleted: is_deleted
            state: state
        }
    }`;

    const variables = { cardNo };
    return JSON.stringify({ query, variables });
}
// Пункт 4.2 Поиск в TCX, если не нашли в TC5
function get_network_part4_2(cardNo) {
    if (!cardNo) {
        return false;
    }

    const query = `query($cardNo: String!) {
        cardByCardNo: clm3_cards(crd_no: $cardNo) {
            accNo: crd_acc_no
            cardNo: crd_no
            cardType: crd_type_code
            cardStatusRelation: status { cardStatus: ccs_status_api_code }
            truncPan: crd_truncated_pan
            cardLoy: crd_crd_no
            rawStatus: crd_cst_status
            master: crd_master
            cipChangedDate: cip_changed_date
            block: block
            is_deleted: is_deleted
            state: state
        }
    }`;

    const variables = { cardNo };
    return JSON.stringify({ query, variables });
}






const headers = {
    'Content-Type': 'application/json',
    'Authorization': `Bearer ${token}`,
};

// Функция проверки результата запроса. Статус 200, тело ответа не пустое и ответ содержит что-то формата JSON
function res_check(response) {
    check(response, {
        'status is 200': (r) => r.status === 200,
        'response is not empty': (r) => r.body && r.body.length > 0,
        'response contains valid JSON': (r) => {
            try {
                const json = JSON.parse(r.body);
                return json && typeof json === 'object';
            } catch (e) {
                return false;
            }
        },
    });
}

// Функция печати основной информации о полученном ответе
function printResInfo(res) {
    console.log("Res = ", res.body);
    console.log("STATUS = ", res.status);
    console.log("============================================================================================");
    console.log();
}

// Функция печати информации о запросе
function printRequestInfo(query, additional) {
    console.log();
    console.log("============================================================================================");
    console.log(additional);
    console.log("QUERY = ", query);
}




export default function () {
    const userProfile = getRandomUserProfile(); // Select a random user
    const requestConfig = getRequestConfigByPercentage(); // Select a random URL config
    let res = null;

    // POST /get Запрос данных клиента из профиля 
    if (requestConfig.url == "https://id-test.x5.ru/api/secure/client-service/get") {
        console.log();
        console.log("POST /get generating requests...");
        console.log("on user = ", userProfile);
        // А что делать, если пользователь принадлежит нескольким сетям? Тогда по циклу запросы формируем?

        let part1_query = post_get_part1(userProfile);

        if (part1_query) {
            res = http.post(tarantool_url, part1_query, { headers: headers, tags: { request_name: "POST /get part1" } });
            printRequestInfo(part1_query, "POST /get part1")
            res_check(res);
            printResInfo(res);
        }

        let part2_query = post_get_part2(userProfile);
        if (part2_query) {
            res = http.post(tarantool_url, part2_query, { headers: headers, tags: { request_name: "POST /get part2" } });
            printRequestInfo(part2_query, "POST /get part2")
            res_check(res);
            printResInfo(res);
        }
    }


    // GET /get Получение карт пользователя по ... NETWORK/GET
    else if (requestConfig.url == "https://id-test.x5.ru/api/secure/card-service/all/get") {
        console.log();
        console.log("GET {network}/get generating requests...");
        console.log("On user = ", userProfile);
        console.log();

        let part1_query = get_network_part1(userProfile);
        if (part1_query) {
            res = http.post(tarantool_url, part1_query, { headers: headers, tags: { request_name: "GET {network}/get part1" } });
            printRequestInfo(part1_query, "GET {network}/get part1")
            res_check(res);
            printResInfo(res);
        }

        let part2_query = get_network_part2(userProfile);
        if (part2_query) {
            res = http.post(tarantool_url, part2_query, { headers: headers, tags: { request_name: "GET {network}/get part2" } });
            printRequestInfo(part2_query, "GET {network}/get part2")
            res_check(res);
            printResInfo(res);
        }


        // 3. Получение списка карт из ЛОЙМАКС??????????????
        // Эмуляция шага

        let cards = null;
        if (hasLinkedCards(userProfile)) {
            cards = userProfile.linked_cards;
            // 4. Поиск карты в TC5 и, если не найдена, в TCX
            cards.forEach((cardNo) => {
                let part41_query = get_network_part4_1(cardNo);
                if (part41_query) {
                    res = http.post(tarantool_url, part41_query, { headers: headers, tags: { request_name: "GET {network}/get part4_1" } });
                    printRequestInfo(part2_query, "GET {network}/get part4_1")
                    res_check(res);
                    printResInfo(res);
                }

                /*
                if (len(res.body.data.cardByNo) > 0) {}
                */ 

                // Тут какая-то обработка результата?
                let part42_query = get_network_part4_2(cardNo);
                if (part42_query) {
                    res = http.post(tarantool_url, part42_query, { headers: headers, tags: { request_name: "GET {network}/get part4_2" } });
                    printRequestInfo(part2_query, "GET {network}/get part4_2")
                    res_check(res);
                    printResInfo(res);
                }
            });
        }

    }

    // POST /getByCard получение данных клиента по карте
    else if (requestConfig.url == "https://id-test.x5.ru/api/secure/client-service/getByCard") {
        console.log();
        console.log("POST /getByCard generating requests...");
        console.log("on user = ", userProfile);
        console.log();

        let part1_query = post_getbycard_part1(userProfile, "");
        // По хорошему нужно проверять, что составлен json запрос
        if (part1_query) {
            res = http.post(tarantool_url, part1_query, { headers: headers, tags: { request_name: "POST /getByCard part1" } });
            printRequestInfo(part1_query, "POST /getByCard part1")
            res_check(res);
            printResInfo(res);
        }
        else {
            console.log("Some incorrect parametrs found when creating a query part1")
        }

        let part2_query = post_getbycard_part2(userProfile);
        // По хорошему нужно проверять, что составлен json запрос
        if (part2_query) {
            res = http.post(tarantool_url, part2_query, { headers: headers, tags: { request_name: "POST /getByCard part2" } });
            printRequestInfo(part2_query, "POST /getByCard part2")
            res_check(res);
            printResInfo(res);
        }
        else {
            console.log("Some incorrect parametrs found when creating a query part2")
        }
    }

    // # POST /id/get Поиск cipId клиента по номеру телефона
    else if (requestConfig.url == "https://id-test.x5.ru/api/secure/client-service/id/get") {
        console.log();
        console.log("POST /id/get generating requests...");
        console.log("on user = ", userProfile);
        console.log();

        let part1_query = post_id_get_part1(userProfile);
        // Проверяем, что получен валидный запрос, т.е. нашли нужные поля у пользователя
        if (part1_query) {
            res = http.post(tarantool_url, part1_query, { headers: headers, tags: { request_name: "POST /id/get part1" } });
            printRequestInfo(part1_query, "POST /id/get part1")
            res_check(res);
            printResInfo(res);
        }
        else {
            console.log("Some incorrect parametrs found when creating a query part1")
        }

        let part2_query = post_id_get_part2(userProfile);
        // Проверяем, что получен валидный запрос, т.е. нашли нужные поля у пользователя
        if (part2_query) {
            res = http.post(tarantool_url, part2_query, { headers: headers, tags: { request_name: "POST /id/get part2" } });
            printRequestInfo(part2_query, "POST /id/get part2")
            res_check(res);
            printResInfo(res);
        }
        else {
            console.log("Some incorrect parametrs found when creating a query part2")
        }

    }

}

