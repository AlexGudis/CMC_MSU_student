#include <stdio.h>
#include <unistd.h>

int
proc(void)
{
    int pid = fork();
    if (!pid) {
        // in father proc
        write(1, "1\n", 2);
    }
    return pid;
}

int
main(void)
{
    int summ_pid = proc() + proc() + proc();
    return 0;
}
