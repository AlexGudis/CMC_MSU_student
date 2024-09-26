#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

volatile sig_atomic_t s = 1;
volatile sig_atomic_t m = 0;

void
handler_int(int p)
{
    s = 1;
    m = 0;
}

void
handler_quit(int p)
{
    m = 1;
    s = 0;
}

int
main(void)
{
    sigaction(SIGINT, &(struct sigaction){.sa_handler = handler_int, .sa_flags = SA_RESTART}, NULL);
    sigaction(SIGQUIT, &(struct sigaction){.sa_handler = handler_quit, .sa_flags = SA_RESTART}, NULL);

    printf("%d\n", getppid());
    fflush(stdout);

    long digit = 0;
    long summ = 0;
    while (scanf("%ld", &digit) != EOF) {
        if (s) {
            __builtin_add_overflow(summ, digit, &summ);
        } else {
            __builtin_mul_overflow(summ, digit, &summ);
        }
        printf("%ld\n", summ);
        fflush(stdout);
    }
    return 0;
}
