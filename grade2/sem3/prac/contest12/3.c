#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int
new_process(char *cmd, int should_wait, int *ans)
{
    int status;
    (*ans)++;
    pid_t pid = fork();
    if (pid < 0) {
        return 1;
    } else if (!pid) {
        // son
        execlp(cmd, cmd, NULL);
        _exit(1);

    } else {
        // father
        if (should_wait) {
            wait(&status);
            if (!(WIFEXITED(status) && !WEXITSTATUS(status))) {
                // error
                (*ans)--;
            }
        }
    }
    return 0;
}

int
main(int argc, char *argv[])
{
    int ans = 0;
    int status;
    int currently_running = 0;
    for (int i = 1; argv[i]; ++i) {
        if (argv[i][0] == 's') {
            while (currently_running) {
                wait(&status);
                if (!(WIFEXITED(status) && !WEXITSTATUS(status))) {
                    ans--;
                }
                currently_running--;
            }
            currently_running++;
            if (new_process(argv[i] + 1, 1, &ans)) {
                ans--;
            }
            currently_running--;
        } else {
            currently_running++;
            if (new_process(argv[i] + 1, 0, &ans)) {
                ans--;
            }
        }
    }

    while (currently_running) {
        wait(&status);
        if (!(WIFEXITED(status) && !WEXITSTATUS(status))) {
            ans--;
        }
        currently_running--;
    }
    printf("%d\n", ans);
    return 0;
}
