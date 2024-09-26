#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    int pfd1[2];
    int pfd2[2];
    pipe2(pfd1, O_CLOEXEC);
    pipe2(pfd2, O_CLOEXEC);
    int status;
    int no_error = 1;
    for (int i = 1; argv[i]; ++i) printf("Command: %s\n", argv[i]);
    for (int i = 1; argv[i] != NULL; ++i) {
        pid_t cmd = fork();
        if (!cmd) {
            printf("Gonna start %s\n", argv[i]);
            // we are in son
            if (i % 2) {
                if (i != 1) {
                    dup2(pfd1[0], 0);
                }
                if (i != argc - 1) {
                    dup2(pfd2[1], 1);
                }
            }
            else {
                dup2(pfd2[0], 0);
                if (i != argc - 1) {
                    dup2(pfd1[1], 1);
                }
            }
            close(pfd1[0]); close(pfd1[1]); close(pfd2[0]); close(pfd2[1]);
            execlp(argv[i], argv[i], NULL);
            _exit(1);
        }
        else if (cmd < 0) {
            return 1;
        }
        waitpid(cmd, &status, 0);
        /*if (!(WIFEXITED(status) && !WEXITSTATUS(status))) {
            no_error = 0;
            break;
        }*/
    }

    return 0;
}
