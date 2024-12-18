#include <stdio.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <wait.h>

struct msg
{
    long type;
    long long x2;
    long long x3;
} msg;

int
main(int argc, char *argv[])
{
    key_t key;
    int n, pid, msgid;
    //key = strtol(argv[1], NULL, 10);
    key = ftok("/bin", 'a');
    n = strtol(argv[2], NULL, 10);
    long long value1, value2, maxval;
    value1 = strtol(argv[3], NULL, 10);
    value2 = strtol(argv[4], NULL, 10);
    maxval = strtol(argv[5], NULL, 10);

    msgid = msgget(key, IPC_CREAT | 0666);

    int flag = 0;

    for (int i = 0; i < n; ++i) {
        if (!(pid = fork())) {
            if (!i) {
                flag = 1;
            }
            msgid = msgget(key, IPC_CREAT | 0666);
            // in son
            long long x1, x2, x3, next_proc_type;
            // loop to get x1 and x2
            while (msgrcv(msgid, &msg, sizeof(msg) - sizeof(msg.type), i + 1, 0)) {
                x1 = msg.x2;
                x2 = msg.x3;
                if (x2 < 0 && !flag && x2 != -1000){
                    // stop it

                    exit(0);
                } else if (flag) { // val2 can be < 0 from father when game starts
                    flag = 0;
                }

                if (x2 == -1000) {
                    printf("Got fork issue\n");
                    fflush(stdout);
                    exit(0);
                }

                x3 = x1 + x2;
                printf("%d %lld\n", i, x3);
                fflush(stdout);
                next_proc_type = x3 % n;
                if (x3 <= maxval) {
                    msg.type = next_proc_type + 1;
                    msg.x2 = x2;
                    msg.x3 = x3;
                    msgsnd(msgid, (const void *) &msg, sizeof(msg) - sizeof(msg.type), 0);
                } else {
                    // stop all process
                    for (int k = 0; k <= n; ++k) {
                        msg.type = k;
                        msg.x3 = -1; // it's impossible by def
                        msgsnd(msgid, (const void *) &msg, sizeof(msg) - sizeof(msg.type), 0);
                    }
                    msgctl(msgid, IPC_RMID, NULL);

                    exit(0);
                }
            }
            msgctl(msgid, IPC_RMID, NULL);

            exit(0);
        } else if (pid < 0) {
            // error in fork
            printf("Error in fork\n");
            fflush(stdout);
            for (int k = 0; k <= n; ++k) {
                msg.type = k;
                msg.x3 = -1000;
                msgsnd(msgid, (const void *) &msg, sizeof(msg) - sizeof(msg.type), 0);
            }
            while (wait(NULL) > 0) {
            }
            // wait for all sons
            msgctl(msgid, IPC_RMID, NULL);

            return 1;
        }
        //printf("New proc: %d\n", pid);
        //fflush(stdout);
    }
    msg.type = 1;
    msg.x2 = value1;
    msg.x3 = value2;
    msgsnd(msgid, (const void *) &msg, sizeof(msg) - sizeof(msg.type), 0);
    while (wait(NULL) > 0) {
    }
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
