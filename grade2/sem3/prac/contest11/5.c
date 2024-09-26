#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

int
main(void)
{
    int val;
    int proc_cnt = 1;
    int check_err = 0;
    while (scanf("%d", &val) != EOF) {
        int son_pid = fork();
        proc_cnt++;
        if (son_pid) {
            int status;
            if (waitpid(son_pid, &status, 0) == -1) {
                _exit(1);
            }
            proc_cnt--;
            if (!(WIFEXITED(status) && !WEXITSTATUS(status))) {
                check_err = 1;
                if (proc_cnt == 1) {
                    break;
                } else {
                    _exit(1);
                }
            }
            printf("%d\n", val);
            fflush(stdout);
            break;
        } else if (son_pid == -1) {
            check_err = 1;
            if (proc_cnt == 1) {
                break;
            } else {
                _exit(1);
            }
        }
    }
    if (proc_cnt == 1 && check_err) {
        printf("-1\n");
        fflush(stdout);
    }
    return 0;
}
