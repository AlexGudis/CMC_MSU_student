#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

enum
{
    ARG_CNT = 6,
    PIPE_PARAM = 2,
    FILE1_IND = 4,
    CMD2_IND = 2,
    FILE2_IND = 5,
    CMD3_IND = 3
};

int
main(int argc, char *argv[])
{
    if (argc != ARG_CNT) {
        fprintf(stderr, "Not enought parametrs\n");
        return 1;
    }

    int pfd[PIPE_PARAM];
    if (pipe(pfd) < 0) {
        fprintf(stderr, "cannot create pipe\n");
        return 1;
    }
    pid_t cmd = fork();
    if (!cmd) {
        close(pfd[0]); // cmd no read from pipe
        pid_t cmd1 = fork();
        if (!cmd1) {
            int file1 = open(argv[FILE1_IND], O_RDONLY | O_CLOEXEC);
            if (file1 < 0) {
                fprintf(stderr, "Error in opening file1 in cmd1\n");
                _exit(1);
            }
            dup2(file1, 0);  // cmd1 in from file1
            dup2(pfd[1], 1); // cmd1 out to pipe
            if (close(pfd[1]) < 0 || close(file1) < 0) {
                fprintf(stderr, "Error in close in cmd1\n");
                _exit(1);
            }
            execlp(argv[1], argv[1], NULL);
            _exit(1);
        } else if (cmd1 < 0) {
            fprintf(stderr, "Error in fork for cmd1\n");
            _exit(1);
        }

        int status;
        int check_cmd1 = 1;
        waitpid(cmd1, &status, 0);
        if (!(WIFEXITED(status) && !WEXITSTATUS(status))) {
            // cmd1 worked bad
            check_cmd1 = 0;
        }
        if (check_cmd1) {
            pid_t cmd2 = fork();
            if (!cmd2) {
                // cmd2 in from stdin
                dup2(pfd[1], 1); // cmd2 out to pipe
                close(pfd[1]);
                execlp(argv[CMD2_IND], argv[CMD2_IND], NULL);
                _exit(1);
            } else if (cmd2 < 0) {
                fprintf(stderr, "Error in fork for cmd2\n");
                _exit(1);
            }
        }
        if (close(pfd[1]) < 0) {
            fprintf(stderr, "Error in closing in cmd\n");
            _exit(1);
        }
        wait(NULL);
        _exit(0);
    }
    if (cmd < 0) {
        fprintf(stderr, "Error in fork for cmd\n");
        return 1;
    }
    if (close(pfd[1]) < 0) {
        fprintf(stderr, "Error in closing in origin\n");
        return 1;
    } // cmd3 no write in pipe
    pid_t cmd3 = fork();
    if (!cmd3) {
        int file2 = open(argv[FILE2_IND], O_WRONLY | O_APPEND | O_CLOEXEC | O_CREAT, 0666);
        if (file2 < 0) {
            fprintf(stderr, "Cannot open file2\n");
            _exit(1);
        }
        dup2(pfd[0], 0); // cmd3 in from pipe
        dup2(file2, 1);  // cmd3 out to file2
        if (close(pfd[0]) < 0 || close(file2) < 0) {
            fprintf(stderr, "Error in closing in cmd3\n");
            _exit(1);
        }
        execlp(argv[CMD3_IND], argv[CMD3_IND], NULL);
        _exit(1);
    } else if (cmd3 < 0) {
        fprintf(stderr, "Error in fork for cmd3\n");
        return 1;
    }
    if (close(pfd[0]) < 0) {
        fprintf(stderr, "Error in closing pfd[0] in origin\n");
        return 1;
    }
    wait(NULL);
    wait(NULL);
    return 0;
}
