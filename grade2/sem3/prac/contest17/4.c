#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
    int pfd[2];
    pipe(pfd);
    int cmd1, cmd3;
    cmd1 = fork();
    if (!cmd1) {
        // in from file, out to pipe
        int fd = open(argv[2], O_RDONLY);
        dup2(fd, 0);
        dup2(pfd[1], 1);
        close(pfd[0]); close(pfd[1]); close(fd);
        execlp(argv[1], argv[1], NULL);
        _exit(1);
    }
    close(pfd[1]);
    cmd3 = fork();
    if (!cmd3) {
        // in from pipe, out to stdout
        dup2(pfd[0], 0);
        close(pfd[0]);
        execlp(argv[3], argv[3], NULL);
        _exit(1);
    }

    close(pfd[0]);
    int status;
    int exit_check = 0;
    while (wait(&status) > 0) {
        if (!(WIFEXITED(status) && !WEXITSTATUS(status))) {
            printf("Smth worked bad in cmd1 or cmd3\n"); fflush(stdout);
            exit_check++;
        }
    }


    if (exit_check == 2) {
        return 1;
    }

    int cmd4;
    cmd4 = fork();
    if (!cmd4) {
        // in from stdin, out to stdout
        execlp(argv[4], argv[4], NULL);
        _exit(1);
    }

    wait(&status);
    if (!(WIFEXITED(status) && !WEXITSTATUS(status))) {
        printf("Smth worked bad in cmd4\n"); fflush(stdout);
        return 1;
    }
    return 0;
}
