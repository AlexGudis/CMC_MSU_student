#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int
main(void)
{
    int son_pid = fork();
    int grson_pid;
    if (son_pid) {
        // we are in dad
        waitpid(son_pid, NULL, 0); // wait till son end
        printf("1\n");
    } else {
        // we are in son
        grson_pid = fork();
        if (grson_pid) {
            // we are in son
            printf("2 ");
            waitpid(grson_pid, NULL, 0);
            fflush(stdout);
            _exit(0);
        } else {
            // we are in grson
            printf("3 ");
            fflush(stdout);
            _exit(0);
        }
    }
    return 0;
}
