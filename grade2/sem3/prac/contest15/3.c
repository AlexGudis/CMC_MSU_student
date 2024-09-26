#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/sem.h>
#include <errno.h>
#include <unistd.h>


int
main(int argc, char *argv[])
{
    char *eptr = NULL;
    errno = 0;
    long count = strtol(argv[1], &eptr, 10);
    if (errno || *eptr || eptr == argv[1] || (int) count != count) {
        fprintf(stderr, "Cannot convert value from str to long\n");
        return 1;
    }
    
    key_t key = ftok("/tmp", 'E');
    int semid = semget(key, count, IPC_CREAT | 0666);
    int pid;
    for (int i = 0; i < count; ++i) {
        semctl(semid, 0, SETVAL, 0); // s = 0;
        pid = fork();
        if (!pid) {
            int x;
            long next_proc;
            //semid = semget(key, count, IPC_CREAT | 0666);
            
            printf("Proc %d started\n", i);
            fflush(stdout);
            struct sembuf op;
            op.sem_num = i;
            op.sem_flg = 0;
            op.sem_op = -1;
            if (semop(semid, &op, 1) < 0){
                fprintf(stderr, "Error in semop in %d proc\n", i);
                fflush(stdout);
                return 1;
            } // down(&s, 1) -> block
            // sem op
            //
            printf("Proc %d before while\n", i);
            fflush(stdout);
            while(scanf("%d", &x) != EOF) {
                //printf("Proc %d in while\n", i);
                //fflush(stdout);
                printf("RESULT: %d %d\n", i, x);
                fflush(stdout);
                next_proc = x % count;
                //printf("Next: %ld\n", next_proc);
                //fflush(stdout);
                op.sem_num = next_proc;
                op.sem_flg = 0;
                op.sem_op = 1;
                if (semop(semid, &op, 1) < 0){
                    fprintf(stderr, "Error in semop in %d proc\n", i);
                    fflush(stdout);
                    return 1;
                }
                op.sem_num = i;
                op.sem_flg = 0;
                op.sem_op = -1;
                // down(&s, 1) -> block
                if (semop(semid, &op, 1) < 0){
                    fprintf(stderr, "Error in semop in %d proc\n", i);
                    fflush(stdout);
                    return 1;
                }
            }
            // up all to stop all
            for (int j = 0; j < count; ++j) {
                op.sem_num = j;
                op.sem_flg = 0;
                op.sem_op = 1;
                if (semop(semid, &op, 1) < 0){
                    fprintf(stderr, "Error in semop in %d proc\n", i);
                    fflush(stdout);
                    return 1;
                }
            }
            exit(0);
        }
    }


    struct sembuf op;
    op.sem_num = 0;
    op.sem_flg = 0;
    op.sem_op = 1;
    semop(semid, &op, 1);
    while(wait(NULL) > 0) {}
    for (int i = 0; i < count; ++i) {
        semctl(semid, i, IPC_RMID, NULL);
    }
    return 0;
}
