#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/signalfd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

int
main(int argc, char *argv[])
{
    char *eptr = NULL;
    errno = 0;
    int n = strtol(argv[1], &eptr, 10);
    if (*eptr || eptr == argv[1] || errno) {
        fprintf(stderr, "Cannot convert value\n");
        return 1;
    }
    int ans = 0;
    int pid;
    int status;
    for (int i = 2; argv[i]; ++i) {
        FILE *file = fopen(argv[i], "r");
        char run[PATH_MAX];
        fscanf(file, "%s", run);
        fclose(file);
        if (i <= n) {
            pid = fork();
            if (!pid) {
                execlp(run, run, NULL);
                _exit(1);
            }
        } else {
            // wait to parallel end
            while (wait(&status) > 0) {
                if (WIFEXITED(status) && !WEXITSTATUS(status)) {
                    ans++;
                }
            }
            pid = fork();
            if (!pid) {
                execlp(run, run, NULL);
                _exit(1);
            }
            while (wait(&status) > 0) {
                if (WIFEXITED(status) && !WEXITSTATUS(status)) {
                    ans++;
                }
            }
        }
    }
    while (wait(&status) > 0) {
        if (WIFEXITED(status) && !WEXITSTATUS(status)) {
            ans++;
        }
    }
    printf("%d\n", ans);
    fflush(stdout);
    return 0;
}
