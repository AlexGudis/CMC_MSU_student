#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int
main(void)
{
    int pfd[2];
    pipe(pfd);
    long x;
    pid_t son = fork();
    if (!son) {
        close(pfd[1]);
        // we are in son
        pid_t gr_son = fork();
        if (!gr_son) {
            // we are in gr_son
            close(pfd[1]);
            long val = 0;
            long summ = 0;
            while (read(pfd[0], &val, sizeof(val))) {
                summ += val;
            }
            printf("%ld\n", summ);
            fflush(stdout);
            close(pfd[0]);
            _exit(0);
        }
        close(pfd[0]);
        wait(NULL);
        _exit(0);
    }
    close(pfd[0]);
    while (scanf("%ld", &x) != EOF) {
        write(pfd[1], &x, sizeof(x));
    }
    close(pfd[1]);
    wait(NULL);
    return 0;
}
