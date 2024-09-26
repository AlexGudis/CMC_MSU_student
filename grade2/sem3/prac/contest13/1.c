#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int
main(void)
{
    int pfd[2];
    pipe(pfd);
    pid_t son = fork();
    if (!son) {
        // we are in son
        pid_t gr_son = fork();
        if (!gr_son) {
            // we are in gr_son
            pid_t grgr_son = fork();
            if (!grgr_son) {
                // we are in grgr_son
                time_t ttime4 = time(NULL);
                write(pfd[1], &ttime4, sizeof(ttime4));
                write(pfd[1], &ttime4, sizeof(ttime4));
                write(pfd[1], &ttime4, sizeof(ttime4));
                _exit(0);
            }
            // we are in gr_son
            wait(NULL);
            time_t ttime3;
            read(pfd[0], &ttime3, sizeof(ttime3));
            struct tm tm3;
            localtime_r(&ttime3, &tm3);
            printf("D:%02d\n", tm3.tm_mday);
            fflush(stdout);
            close(pfd[1]);
            close(pfd[0]);
            _exit(0);
        } else if (gr_son) {
            // we are in son
            wait(NULL);
            time_t ttime2;
            read(pfd[0], &ttime2, sizeof(ttime2));
            struct tm tm2;
            localtime_r(&ttime2, &tm2);
            printf("M:%02d\n", tm2.tm_mon + 1);
            fflush(stdout);
            close(pfd[1]);
            close(pfd[0]);
            _exit(0);
        }
    }
    wait(NULL);
    time_t ttime1;
    read(pfd[0], &ttime1, sizeof(ttime1));
    struct tm tm1;
    localtime_r(&ttime1, &tm1);
    printf("Y:%04d\n", tm1.tm_year + 1900);
    fflush(stdout);
    close(pfd[0]);
    close(pfd[1]);
    return 0;
}
