#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int
main(int argc, char *argv[])
{
    int fd[2];
    pipe(fd);
    char x[] = "01\n";
    if (fork()) {
        puts(x + 1);
        write(fd[1], x, 1);
        wait(NULL);
    }
    else {
        write(fd[1], &x[1], 1);
        read(fd[0], x, 1);
        read(fd[0], x + 1, 1);
    }
    puts(x);
    return 0;
}
