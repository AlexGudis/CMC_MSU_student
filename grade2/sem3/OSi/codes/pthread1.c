#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 3
/*общая переменная, используемая нитями */
int shared_counter = 0;
/*функция - точка входа в нить */
void *
thr_fn(void *arg)
{
    /*локальная переменная*/
    int local = 0;
    /*пауза для "перемешивания" выполнения нитей*/
    sleep(abs(5 - (int) arg));
    /*выводим информацию о нити (порядковый номер и системный
    идентификатор), текущее значение общей переменной (и увеличиваем
    его на 1), значение локальной переменной*/
    printf("***Thread #%d with ID %#x: shared value is %d, local value is %d\n", (int) arg, pthread_self(),
           shared_counter++, local++);
    return NULL;
}
int
main()
{
    pthread_t th_id;
    int i, err;
    for (i = 0; i < NUM_THREADS; i++) {
        /*cсоздаем нить, используем последний аргумент для передачи порядкового
        номера по значению! */
        err = pthread_create(&th_id, NULL, thr_fn, (void *) i);
        printf("MAIN: created thread with ID %#x\n", th_id);
    }
    /*пауза - дать возможность всем нитям отработать и вывести информацию о себе*/
    sleep(10);
    return 0;
}
