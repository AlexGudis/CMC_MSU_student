#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <math.h>
#include <stdlib.h>

volatile sig_atomic_t simple;
volatile sig_atomic_t sigint_cnt;
volatile sig_atomic_t find_simp;

void
find_simple(long low, long high)
{
    int check = 1;
    for (long i = low; i < high; ++i) {
        for (long j = 2; j < (long) (sqrt(i) + 1); ++j) {
            if (i % j == 0) {
                check = 0;
                break;
            }
        }
        if (check) {
            simple = i;
            find_simp = 1;
        }
        check = 1;
    }
    printf("-1\n");
    fflush(stdout);
    _exit(0);
}

void
handler_int(int p)
{
    if (sigint_cnt < 3) {
        if (find_simp) {
            printf("%d\n", simple);
            fflush(stdout);
        } else {
            printf("0\n");
            fflush(stdout);
        }
    }
    sigint_cnt++;
    if (sigint_cnt == 4) {
        _exit(0);
    }
}

void
handler_term(int p)
{
    _exit(0);
}

int
main(int argc, char *argv[])
{
    long low = 0;
    scanf("%ld", &low);

    if (low < 0) { // no simple < 0
        low = 2;
    }

    long high = 0;
    scanf("%ld", &high);

    if (high < 0) { // no simple < 0
        high = 2;
    }

    sigaction(SIGINT, &(struct sigaction){.sa_handler = handler_int, .sa_flags = SA_RESTART}, NULL);
    sigaction(SIGTERM, &(struct sigaction){.sa_handler = handler_term, .sa_flags = SA_RESTART}, NULL);

    printf("%d\n", getpid());
    fflush(stdout);
    find_simple(low, high);

    return 0;
}
