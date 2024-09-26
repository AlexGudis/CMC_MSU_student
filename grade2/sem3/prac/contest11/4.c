#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

int
main(void)
{
    long n;

    scanf("%ld", &n);
    if (n == 1) {
        printf("1\n");
    } else {
        printf("1");
    }
    fflush(stdout);
    for (long i = 2; i <= n; ++i) {
        int son_pid = fork();
        if (son_pid == 0) {
            printf(" %ld", i);
            if (i == n) {
                printf("\n");
            }
            fflush(stdout);
        } else if (son_pid) {
            break;
        }
    }
    while (wait(NULL) > 0) {
    }
    return 0;
}
