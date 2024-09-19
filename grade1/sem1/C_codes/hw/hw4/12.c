#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void){
	int k, c, s;
	// k - число символов 
	scanf("%d %d %d", &k, &c, &s);
	char a[1000002];
	char x;
	int a_ind = 0;
	scanf("%c", &x); // Считываем первый символ перевода строки после ввода чисел
	fgets(a, 1000000, stdin);
	char ans[10000][s][k]; // массив столбцов
	int ans_ind = 0; // страница, которую сейчас заполняем
	int ans_ind_s = 0; // строка, которую сейчас заполняем
	char words[100002][k+1]; // Список слов без пробелов
	int words_ind = 0;
	int words_ind_k = 0;
	char len_a = strlen(a);
	int last_s = 0;
	for (int i = 0; i < len_a; i++){
		if (a[i] != ' '){
			words[words_ind][words_ind_k] = a[i];
			words_ind_k++;
		}
		else{
			words[words_ind][words_ind_k] = 0;
			words_ind++; // Начинаем запись другого слова
			words_ind_k = 0; // Начинаем запись с первого символа
		}
	} 
	words[words_ind][words_ind_k] = 0;
	words_ind++;
	words_ind_k = 0;
	
	for (int p = 0; p < words_ind; p++) { // Начинаем пробегаться по номерам слов из списка words 
		while (1){ // Пока не добавлю слово никуда не уйду
			//printf("doing...\n");
			if (strlen(ans[ans_ind][ans_ind_s]) + strlen(words[p]) <= k) { 
				// В конкретную строку конкретного столбца добавлю слово
				int words_p_len = strlen(words[p]);
				int ans_ind_s_len = strlen(ans[ans_ind][ans_ind_s]);
				for (int j = ans_ind_s_len; j < ans_ind_s_len + words_p_len; j++){
					ans[ans_ind][ans_ind_s][j] = words[p][j - ans_ind_s_len];
				}
				int now_len_str = strlen(ans[ans_ind][ans_ind_s]);
				if (now_len_str < k) ans[ans_ind][ans_ind_s][now_len_str] = ' '; // Наш пробел между словами
				break;
			}
			else{
				//printf("p == %d\n", p);
				// То есть я не могу добавить в эту строку этого столбца данное слово
				// Выполним форматирование данной строки конкретного столбца для печати
				int len = strlen(ans[ans_ind][ans_ind_s]);
				// Проверим, что в строке больше одного слова
				int check_space = 0;
				int check = 0;
				//printf("ans_str_len: %ld\n", strlen(ans[ans_ind][ans_ind_s]));
				for (int i = 0; i < len; i++){
					if (ans[ans_ind][ans_ind_s][i] == ' ') check_space  = 1;
					if (ans[ans_ind][ans_ind_s][i] != ' ' && check_space) check = 1;
				}
				if (check){ // В строке больше одного слова
					//printf("check == 1\n");
					//printf("%s", ans[ans_ind][ans_ind_s]);
					int flag = 1;
					while (flag){ // Пока буква не станет к-ым символом
						//printf("replacing..., p == %d\n", p);
						//iprintf("%ld\n", strlen(ans[ans_ind][ans_ind_s]));
						int space = 0;
						for (int i = 0; i < k; i++){
							if (ans[ans_ind][ans_ind_s][i] == ' ' && i != k - 1 && ans[ans_ind][ans_ind_s][i+1] != ' '){
								space++; // Встретили пробел
							}
							else if (ans[ans_ind][ans_ind_s][i] != ' '  && space) { 
								// Добавим в слово один пробел и сдвинем все 
								space = -1;
								char now = ' ';
								char replace;
								for (int j = i; j < k; j++){
									replace = ans[ans_ind][ans_ind_s][j];
									ans[ans_ind][ans_ind_s][j] = now;
									now = replace;
								}
							}
							int lennn = strlen(ans[ans_ind][ans_ind_s]);
							if (lennn == k && ans[ans_ind][ans_ind_s][lennn - 1] != ' '){
								//Если мы идем по циклу и уже сдвинули как можем
								flag = 0;
								break;
							}
						}

					}
				}
				else{ // Добавим пробелов до самого конца строки, так как у нас всего одно слово
					int check = 0;
					for (int i = 0; i < k; i++){
						if (ans[ans_ind][ans_ind_s][i] == ' ') check = 1;
						else if (check == 1) ans[ans_ind][ans_ind_s][i] = ' ';
					}
				}

				if (ans_ind_s == s - 1) { 
					// Если полностью заполнили данный столбец, то переходим на следующий
					ans_ind++;
					ans_ind_s = 0;
				}
				else ans_ind_s++;
			}
		}
	}
	
	//printf("%d", ans_ind);
	//printf("----------\n");
	/*for (int i = 0; i < ans_ind + 1; i++){
		for (int j = 0; j < s; j++){
			for (int p = 0; p < k; p++){
				printf("%c", ans[i][j][p]);
			}
			printf("\n");
		}
		printf("\n");
		printf("\n");
	}
	printf("##############\n");
	*/

	// Выведем наш список ans в соответствии с условием задачи
	int i = 0;
	//printf("%d\n", ans_ind);
	while (i < ans_ind + 1){
		for (int j = 0; j < s; j++){
			for (int f = 0; f < c; f++){
				for (int p = 0; p < k; p++){
					printf("%c", ans[i+f][j][p]);
				}
				if (f != c - 1) printf("    ");
			}
			if (i != ans_ind || (i == ans_ind && j != ans_ind_s)) printf("\n");
		}
		i += c; // Перейдем на следующие сформированные столбцы для каждой страницы
		if (i < ans_ind + 1){
			printf("\n");
			printf("\n");
		}
	}
	return 0;
}
