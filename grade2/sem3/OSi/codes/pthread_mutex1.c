#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N_SIZE 10
/*разделяемый ресурс*/
char str[N_SIZE + 1];
/*объявление и инициализация мьютекса, состояние "открыт"*/
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
/*точка входа в нить */
void *
fThread(void *arg)
{
    pthread_mutex_lock(&mutex); /*вход в критическую секцию*/
    /*добавляем символ к разделяемой строке*/
    int iPos = strlen(str);
    str[iPos] = 'A' + iPos;
    pthread_mutex_unlock(&mutex); /*выход из критической секции*/
    return NULL;
}
int
main()
{
    pthread_t th_id;
    int i;
    /*инициализация 0 всего массива символов*/
    memset(str, 0, N_SIZE + 1);
    /*порождение N_SIZE параллельно работающих нитей, каждая из
    которых добавляет символ к разделяемой строке*/
    for (i = 0; i < N_SIZE; i++) {
        pthread_create(&th_id, NULL, fThread, NULL);
    }
    sleep(5);           /*пауза для ожидания завершения всех нитей*/
    printf("%s\n", str); /*печать итоговой строки*/
    return 0;
}
