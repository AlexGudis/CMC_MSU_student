#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

enum
{
    BASE = 10,
    LEN = 8
};

int
main(void)
{
    char *eptr;
    long lval;
    int son1 = fork();
    if (son1) {
        int son2 = fork();
        if (son2) {
            int son3 = fork();
            if (son3 == 0) {
                char s3[LEN];
                read(0, s3, LEN);
                s3[strlen(s3) - 1] = '\0';
                eptr = NULL;
                errno = 0;
                lval = strtol(s3, &eptr, BASE);
                printf("3 %ld\n", lval * lval);
                fflush(stdout);
                _exit(0);
            }
        } else if (son2 == 0) {
            char s2[LEN];
            read(0, s2, LEN);
            s2[strlen(s2) - 1] = '\0';
            eptr = NULL;
            errno = 0;
            lval = strtol(s2, &eptr, BASE);
            printf("2 %ld\n", lval * lval);
            fflush(stdout);
            _exit(0);
        }
    } else if (son1 == 0) {
        char s1[LEN];
        read(0, s1, LEN);
        s1[strlen(s1) - 1] = '\0';
        eptr = NULL;
        errno = 0;
        lval = strtol(s1, &eptr, BASE);
        printf("1 %ld\n", lval * lval);
        fflush(stdout);
        _exit(0);
    }
    wait(NULL);
    wait(NULL);
    wait(NULL);
    return 0;
}
