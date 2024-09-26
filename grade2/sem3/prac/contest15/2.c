#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <wait.h>
#include <sys/signalfd.h>

int proc1;
char byte_print;
char n_bit;
volatile sig_atomic_t flag;

void
func(char bit)
{
    byte_print |= (bit << n_bit);
    n_bit++;
    if (n_bit == 8) {
        printf("%c", byte_print);
        fflush(stdout);
        n_bit = 0;
        byte_print = 0;
    }
}

void
alrm(int s)
{
    NULL;
}

int
main(int argc, char *argv[])
{
    sigaction(SIGALRM, &(struct sigaction){.sa_handler = alrm, .sa_flags = SA_RESTART}, NULL);

    proc1 = fork();
    if (!proc1) {
        // in son1
        sigset_t ss;
        sigemptyset(&ss);
        sigaddset(&ss, SIGUSR1);
        sigaddset(&ss, SIGUSR2);
        sigaddset(&ss, SIGIO);
        sigprocmask(SIG_BLOCK, &ss, NULL);
        int sfd = signalfd(-1, &ss, 0);
        while (!flag) {
            struct signalfd_siginfo sinfo;
            read(sfd, &sinfo, sizeof(sinfo));
            if (sinfo.ssi_signo == SIGUSR1) {
                func(0);
            } else if (sinfo.ssi_signo == SIGUSR2) {
                func(1);
            } else { // SIGIO
                flag = 1;
                exit(0);
            }
            kill(sinfo.ssi_pid, SIGALRM);
        }
        // wait till SIGIO
        exit(0);
    }
    int proc2;
    proc2 = fork();
    if (!proc2) {
        // in son2
        int fd = open(argv[1], O_RDONLY);
        char byte;
        char bit;
        while (read(fd, &byte, sizeof(byte)) > 0) {
            for (int i = 0; i < 8; ++i) {
                bit = (byte >> i) & 1;
                if (bit) {
                    // send bit 1
                    kill(proc1, SIGUSR2);
                } else {
                    // send bit 0
                    kill(proc1, SIGUSR1);
                }
                pause(); // wait for SIGALRM
            }
        }
        close(fd);
        kill(proc1, SIGIO);
    }

    while (wait(NULL) > 0) {
    }
    return 0;
}
