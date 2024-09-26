#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_CNT 10
int target_pid, cnt;
int fd[2];
int status;
void
SigHndlr(int s)
{
    /* в обработчике сигнала происходит и чтение, и запись */
    if (cnt < MAX_CNT) {
        read(fd[0], &cnt, sizeof(int));
        printf("%d %d\n", getpid(), cnt);
        cnt++;
        write(fd[1], &cnt, sizeof(int));
        /* посылаем сигнал второму: пора читать из канала */
        kill(target_pid, SIGUSR1);
    } else if (target_pid == getppid()) {
        /* условие окончания игры проверяется потомком */
        printf("Child is going to be terminated\n");
        close(fd[1]);
        close(fd[0]);
        /* завершается потомок */
        exit(0);
    } else
        kill(target_pid, SIGUSR1);
}

int
main(int argc, char **argv)
{
    pipe(fd);
    signal(SIGUSR1, SigHndlr);
    cnt = 0;
    if (target_pid = fork()) {
        /* В родительском процессе: */
        write(fd[1], &cnt, sizeof(int)); /* старт. синхр.*/
        /* ждем завершения потомка */
        while (wait(&status) == -1)
            ;
        printf("Завершение родительского процесса\n");
        close(fd[1]);
        close(fd[0]);
        return 0;
    } else {
        /* Сыновний процесс – ждем отца: */
        read(fd[0], &cnt, sizeof(int));
        target_pid = getppid();
        /* сыновний процесс начинает пинг-понг */
        write(fd[1], &cnt, sizeof(int));
        kill(target_pid, SIGUSR1);
        for (;;)
            ;
    }
}
