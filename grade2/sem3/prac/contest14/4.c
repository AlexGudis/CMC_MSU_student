#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/signalfd.h>
#include <errno.h>
#include <stdlib.h>

void work(int serial, int max_val, int rfd, int wfd)
{
    sigset_t ss;
    sigemptyset(&ss); sigaddset(&ss, SIGUSR1);
    int sfd = signalfd(-1, &ss, 0);
    int v;
    struct signalfd_siginfo sinfo;

    while (v != max_val) {
        struct signalfd_siginfo sinfo;
        //printf("I'm here1 %d\n", getpid());
        read(sfd, &sinfo, sizeof(sinfo)); // wake up proc
        //printf("I'm here2 %d\n", getpid());
        //fscanf(rfd, "%d", &v); // read from pipe
        read(rfd, &v, sizeof(v));
        //printf("I'm here3 %d\n", getpid());
        if (v != max_val) {
            printf("%d %d\n", serial, v);
            v++;
        }
        //fprintf(wfd, "%d\n", v);
        write(wfd, &v, sizeof(v));
        kill(sinfo.ssi_pid, SIGUSR1);
    }
    close(sfd);
    close(wfd);
}

int
main(int argc, char *argv[])
{
    sigset_t ss;
    sigemptyset(&ss); sigaddset(&ss, SIGUSR1);
    sigprocmask(SIG_BLOCK, &ss, NULL);

    char *eptr = NULL;
    errno = 0;
    int max_val = strtol(argv[1], &eptr, 10);
    if (*eptr || eptr == argv[1] || errno) {
        fprintf(stderr, "Cannot convert value\n");
        return 1;
    }

    int fd[2];
    pipe(fd);
    FILE *wfd = fdopen(fd[1], "w");
    FILE *rfd = fdopen(fd[0], "r");
    int pid1 = fork();
    if (!pid1) {
        work(1, max_val,fd[0],fd[1]);
        _exit(0);
    }
    int pid2 = fork();
    if (!pid2) {
        int v = 1;
        //fprintf(wfd, "%d\n", v);
        write(fd[1], &v, sizeof(v));
        kill(pid1, SIGUSR1);
        work(2, max_val, fd[0], fd[1]);
        _exit(0);
    }
    while (wait(NULL) > 0) {}
    printf("Done\n");
}
