#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int
create_check_proccess(char *cmd)
{

    int status;
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Error while creating new proccess\n");
        return 0;
    } else if (!pid) {
        execlp(cmd, cmd, NULL);
        _exit(1);
    } else {
        wait(&status);
        if (!(WIFEXITED(status) && !WEXITSTATUS(status))) {
            // error
            return 0;
        }
    }
    return 1;
}

int
main(int argc, char *argv[])
{
    int a = 0, b = 0, c = 0;
    a = create_check_proccess(argv[1]);
    if (!a) {
        b = create_check_proccess(argv[2]);
    }
    if (a || b) {
        c = create_check_proccess(argv[3]);
    }
    if (!c) {
        return 1;
    }
    return 0;
}
