#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>

void
work(int serial, int max_val, FILE *r, FILE *w)
{
    int val = 0;
    // start val for different sons
    if (serial == 1) {
        val = 1;
    } else {
        val = 2;
    }

    while (val < max_val && fscanf(r, "%d", &val) != EOF) {
        printf("%d %d\n", serial, val);
        fflush(stdout);
        val++;
        fprintf(w, "%d\n", val);
        fflush(w);
        val++;
    }
    fclose(r);
    fclose(w);
}

int
main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Wrong amount of parametrs\n");
        return 1;
    }
    char *eptr = NULL;
    errno = 0;
    int max_val = strtol(argv[1], &eptr, 10);
    if (*eptr || eptr == argv[1] || errno) {
        fprintf(stderr, "Cannot convert value\n");
        return 1;
    }
    int p1[2]; // канал, на котором ждет первый сын
    int p2[2]; // канал, на котором ждет второй сын
    if (pipe(p1) == -1) {
        fprintf(stderr, "Cannot create pipe for son1\n");
        return 1;
    }
    if (pipe(p2) == -1) {
        fprintf(stderr, "Cannot create pipe for son2\n");
        return 1;
    }
    FILE *rf1 = fdopen(p1[0], "r");
    if (rf1 == NULL) {
        fprintf(stderr, "Error in fdopen for p1[0]\n");
        return 1;
    }
    FILE *wf1 = fdopen(p1[1], "w");
    if (wf1 == NULL) {
        fprintf(stderr, "Error in fdopen for p1[1]\n");
        return 1;
    }
    FILE *rf2 = fdopen(p2[0], "r");
    if (rf2 == NULL) {
        fprintf(stderr, "Error in fdopen for p2[0]\n");
        return 1;
    }
    FILE *wf2 = fdopen(p2[1], "w");
    if (wf2 == NULL) {
        fprintf(stderr, "Error in fdopen for p2[1]\n");
        return 1;
    }
    int pid_son1 = fork();
    if (!pid_son1) {
        // первый сын
        work(1, max_val, rf1, wf2);
        _exit(0);
    } else if (pid_son1 < 0) {
        fprintf(stderr, "Error in fork for son1\n");
        return 1;
    }
    int pid_son2 = fork();
    if (!pid_son2) {
        // второй сын
        work(2, max_val, rf2, wf1);
        _exit(0);
    } else if (pid_son2 < 0) {
        fprintf(stderr, "Error in fork for son2\n");
        return 1;
    }
    int val = 1;
    fprintf(wf1, "%d\n", val);
    fflush(wf1);
    if (fclose(rf1) < 0 || fclose(wf1) < 0 || fclose(rf2) < 0 || fclose(wf2) < 0) {
        fprintf(stderr, "Error in fclose in father\n");
        return 1;
    }
    wait(NULL);
    wait(NULL);
    printf("Done\n");
    return 0;
}
