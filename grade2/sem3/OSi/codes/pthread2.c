#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
/*функция - точка входа в нить */
void *
thr_fn(void *arg)
{
    /*засыпаем на 0..10 секунд */
    sleep(time(0) % 10);
    pthread_exit(NULL);
}
int
main()
{
    pthread_t th_id;
    void *pret;
    /*создаём нить и запоминаем время создания */
    pthread_create(&th_id, NULL, thr_fn, NULL);
    time_t tm_start = time(0);
    /*ожидаем завершения ранее созданной нити */
    pthread_join(th_id, &pret); 
    printf("Code: %d\n", (int)pret);
    printf("Thread %#x execution time = %u\n ", th_id, time(0) - tm_start);
    return 0;
}
