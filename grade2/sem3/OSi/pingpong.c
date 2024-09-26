#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static int x = 1;
int id = 0;
int mx = 0;
pthread_mutex_t xmut = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mod = PTHREAD_COND_INITIALIZER;

void *play(void *arg) {
    int my_id = strtol((char *)arg, NULL, 10);
    while (x < mx) {
        pthread_mutex_lock(&xmut);
        while (id != my_id) {
            pthread_cond_wait(&mod, &xmut);
        }
        if (x < mx) {
            printf("%d %d\n", my_id + 1, x++);
        }
        id = my_id ^ 1;
        pthread_cond_signal(&mod);
        pthread_mutex_unlock(&xmut);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    mx = strtol(argv[1], NULL, 10);
    pthread_t players[2];
    for (int i = 0; i < 2; ++i) {
        pthread_create(players + i, NULL, play, i ? "1" : "0"); 
    }
    for (int i = 0; i < 2; ++i) {
        pthread_join(players[i], NULL);
    }
    printf("Done\n");
    return 0;
}
