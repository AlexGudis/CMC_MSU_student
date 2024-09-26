#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/signalfd.h>
#include <errno.h>
#include <stdlib.h>

volatile sig_atomic_t flag;

void
handler(int s)
{
    flag = 1;
}

void
work(int serial, int max_val, FILE *rfd, FILE *wfd)
{
    sigset_t s1, s2;
    sigemptyset(&s1);
    sigaddset(&s1, SIGUSR1);
    sigprocmask(SIG_BLOCK, &s1, NULL);
    sigemptyset(&s2);
    int v;
    int send_to;

    sigaction(SIGUSR1, &(struct sigaction){.sa_handler = handler, .sa_flags = SA_RESTART}, NULL);
    while (v != max_val) {
        while (!flag) {
            sigsuspend(&s2);
        }
        flag = 0;
        fscanf(rfd, "%d", &v); // read from pipe
        fscanf(rfd, "%d", &send_to);
        if (v != max_val) {
            printf("%d %d\n", serial, v);
            fflush(stdout);
            v++;
        }
        fprintf(wfd, "%d\n", v);
        fprintf(wfd, "%d\n", getpid());
        fflush(wfd);
        kill(send_to, SIGUSR1);
    }
    fclose(wfd);
}

int
main(int argc, char *argv[])
{
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
        work(1, max_val, rfd, wfd);
        _exit(0);
    }
    int pid2 = fork();
    if (!pid2) {
        int v = 1;
        fprintf(wfd, "%d\n", v);
        fprintf(wfd, "%d\n", getpid());
        fflush(wfd);
        kill(pid1, SIGUSR1);
        work(2, max_val, rfd, wfd);
        _exit(0);
    }
    while (wait(NULL) > 0) {
    }
    printf("Done\n");
    fflush(stdout);
    return 0;
}
