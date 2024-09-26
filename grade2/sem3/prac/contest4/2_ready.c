#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

enum
{
    BASE = 10,
    READ_PARAM = 2,
    N_INDEX = 2,
    D_BYTES = 8
};

int
main(int argc, char *argv[])
{

    if (argc <= READ_PARAM) {
        fprintf(stderr, "line 21, not enough parametrs\n");
        return 1;
    }

    char *pathname = argv[1];

    char *eptr = NULL;
    errno = 0;
    long n = strtol(argv[N_INDEX], &eptr, BASE);
    if (errno || *eptr || eptr == argv[N_INDEX] || (int) n != n) {
        fprintf(stderr, "line 30, cannot convert N\n");
        return 1;
    }

    int fd = open(pathname, O_RDWR);
    if (fd == -1) {
        fprintf(stderr, "line 36, problem with opening the file\n");
        return 1;
    }

    errno = 0;
    off_t file_size = lseek(fd, 0, SEEK_END); // file size
    if (errno) {
        fprintf(stderr, "line 43, error in calculating file_size\n");
        return 1;
    }
    if (file_size <= D_BYTES) { // 1 or 0 digits -> no need to change the file
        return 0;
    }

    int check = 1;
    if (lseek(fd, D_BYTES, SEEK_SET) == -1) {
        fprintf(stderr, "line 53, error with positioning before loop\n");
        return 1;
    }
    double in_i;
    double out_i_1;
    while (check < n && check * D_BYTES < file_size) {
        if (read(fd, &in_i, D_BYTES) == -1) {
            fprintf(stderr, "line 60, error in reading in[i] from file\n");
            return 1;
        }

        if (lseek(fd, -D_BYTES, SEEK_CUR) == -1) {
            fprintf(stderr, "line 65, error in changing current position\n");
            return 1;
        }
        if (lseek(fd, -D_BYTES, SEEK_CUR) == -1) {
            fprintf(stderr, "line 69, error in changing current position\n");
            return 1;
        }
        if (read(fd, &out_i_1, D_BYTES) == -1) {
            fprintf(stderr, "line 73, error in reading out[i-1] from file\n");
            return 1;
        }

        double out_i = in_i - out_i_1;
        if (write(fd, &out_i, D_BYTES) == -1) {
            fprintf(stderr, "line 79, error in writing out[i]\n");
            return 1;
        }
        check++;
    }
    if (close(fd) == -1) {
        fprintf(stderr, "line 85, error while closing fd\n");
        return 1;
    }
    return 0;
}
