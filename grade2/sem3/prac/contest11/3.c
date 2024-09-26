#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

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
        // we are in dad
        //waitpid(son1, NULL, 0); // waiting till son1 end
        int son2 = fork();
        if (son2) {
            // we are in dad
            //waitpid(son2, NULL, 0);
            int son3 = fork();
                // we are in dad
                //waitpid(son3, NULL, 0);
            if (son3 == 0) {
                //we are in son 3
                char s3[LEN];
                //read(0, s3, LEN);
                scanf("%s", s3);
                eptr = NULL;
                errno = 0;
                lval = strtol(s3, &eptr, BASE);
                if (errno || *eptr || eptr == s3 || (int) lval != lval) {
                    fprintf(stderr, "Error while converting value\n");
                    _exit(1);
                }
                printf("3 %ld\n", lval * lval);
                fflush(stdout);
                _exit(0);
            }
        } else if (son2 == 0){
            // we are in son 2
            char s2[LEN];
            //read(0, s2, LEN);
            scanf("%s", s2);
            eptr = NULL;
            errno = 0;
            lval = strtol(s2, &eptr, BASE);
            if (errno || *eptr || eptr == s2 || (int) lval != lval) {
                fprintf(stderr, "Error while converting value\n");
                _exit(1);
            }
            printf("2 %ld\n", lval * lval);
            fflush(stdout);
            _exit(0);
        }
    } else if (son1 == 0){
        // we are in son1
        char s1[LEN];
        //read(0, s1, LEN);
        scanf("%s", s1);
        eptr = NULL;
        errno = 0;
        lval = strtol(s1, &eptr, BASE);
        if (errno || *eptr || eptr == s1 || (int) lval != lval) {
            fprintf(stderr, "Error while converting value\n");
            _exit(1);
        }
        printf("1 %ld\n", lval * lval);
        fflush(stdout);
        _exit(0);
    }
    wait(NULL);
    wait(NULL);
    wait(NULL);
    return 0;
}
