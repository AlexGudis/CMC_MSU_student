#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile sig_atomic_t flag;

void handler(int s)
{
    flag = 1;
}

int main()
{
    sigset_t s1, s2;
    // формируем множество блокируемых сигналов из SIGINT
    sigemptyset(&s1); sigaddset(&s1, SIGINT);
    sigprocmask(SIG_BLOCK, &s1, NULL);
    // пустое множество временно блокируемых сигналов для sigsuspend
    sigemptyset(&s2);
    sigaction(SIGINT, &(struct sigaction) { .sa_handler = handler, .sa_flags = SA_RESTART }, NULL);
    while (1) {
        while (!flag) {
            // sigsuspend вместо pause
            sigsuspend(&s2);
        }
        flag = 0;
        printf("signal received\n");
    }
}
