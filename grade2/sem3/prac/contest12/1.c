#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

enum
{
    FILE1_IDX = 2,
    FILE2_IDX = 3,
    FILE3_IDX = 4,
    ERROR = 42
};

int
main(int argc, char *argv[])
{
    int status;
    pid_t pid = fork();
    if (!pid) {
        int fd = open(argv[FILE1_IDX], O_RDONLY);
        if (fd < 0) {
            fprintf(stderr, "Cannot open file 1\n");
            _exit(ERROR);
        }
        dup2(fd, 0); // to stdin
        close(fd);

        fd = open(argv[FILE2_IDX], O_WRONLY | O_CREAT | O_APPEND, 0660);
        if (fd < 0) {
            fprintf(stderr, "Cannot open file 2\n");
            _exit(ERROR);
        }
        dup2(fd, 1); // to stdout
        close(fd);

        fd = open(argv[FILE3_IDX], O_WRONLY | O_CREAT | O_TRUNC, 0660);
        if (fd < 0) {
            fprintf(stderr, "Cannot open file 3\n");
            _exit(ERROR);
        }
        dup2(fd, 2); // to stderr
        close(fd);

        execlp(argv[1], argv[1], argv[FILE1_IDX], argv[FILE2_IDX], argv[FILE3_IDX], NULL);
        _exit(ERROR);
    } else {
        wait(&status);
        printf("%d\n", status);
    }
    return 0;
}
