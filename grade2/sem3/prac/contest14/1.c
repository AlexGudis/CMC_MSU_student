#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

volatile sig_atomic_t counter;
volatile sig_atomic_t flag;

void
handler(int s)
{
    if (counter < 5) {
        printf("%d\n", counter);
        fflush(stdout);
    }
    counter++;
    flag = 1;
}

int
main(void)
{
    sigset_t s1, s2;
    sigemptyset(&s1);
    sigaddset(&s1, SIGHUP);
    sigprocmask(SIG_BLOCK, &s1, NULL);
    sigemptyset(&s2);
    sigaction(SIGHUP, &(struct sigaction){.sa_handler = handler, .sa_flags = SA_RESTART}, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    while (counter != 6) {
        while (!flag) {
            sigsuspend(&s2);
        }
        flag = 0;
    }
    return 0;
}
