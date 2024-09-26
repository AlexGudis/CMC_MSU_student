#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

int
main(void)
{
    int x = 0;
    int father = 1;
    while (scanf("%d", &x) != EOF) {
        printf("OUT: %d %d\n", getpid(), x); fflush(stdout);
        if (!father) {
            //printf("Send: %d\n", x); fflush(stdout);
            _exit(x);
        }
        for (int i = 0; i < x; ++i) {
            if (!fork()) {
                //printf("i, x:%d %d\n", i, x);
                //printf("New proc\n"); fflush(stdout);
                father = 0;
            }
            else {
                int status;
                wait(&status);
                if (!father) {
                    //printf("Got status: %d\n", WEXITSTATUS(status)); fflush(stdout);
                    _exit(WEXITSTATUS(status));
                }
                else {
                    x = WEXITSTATUS(status);
                    if (x == 150) return 0;
                    i = -1;
                    //printf("New i, x: %d %d\n", i, x);fflush(stdout);
                }
            }
        }
    }
    x = 150;
    if (!father) {
        _exit(x);
    }
    return 0;
}
