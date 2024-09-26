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
    INT_BYTES = 4,
    CHAR_BITS = 8,
    POW_SUMM_DIV = 6
};

int
main(int argc, char *argv[])
{
    if (argc <= 3) {
        fprintf(stderr, "line 20, not enough parametrs\n");
        return 1;
    }

    char *file_input = argv[1];
    char *file_output = argv[2];

    char *eptr = NULL;
    errno = 0;
    long mod = strtol(argv[3], &eptr, BASE);
    if (errno || *eptr || eptr == argv[3] || (int) mod != mod) {
        fprintf(stderr, "line 30, cannot convert mod\n");
        return 1;
    }

    int fd_in = open(file_input, O_RDONLY);
    if (fd_in == -1) {
        fprintf(stderr, "line 36, problem with opening input file\n");
        return 1;
    }

    int fd_out = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0666);
    if (fd_out == -1) {
        fprintf(stderr, "line 42, problem with opening output file\n");
        return 1;
    }

    char bytes;
    long long digit = 0;
    while (read(fd_in, &bytes, 1) == 1) {
        int x = 0;
        for (long long i = 1; i < CHAR_BITS + 1; ++i) {
            if ((bytes >> (i - 1)) & 1) {
                x = ((2 * (i + digit) + 1) * ((i + digit) * (i + digit) + (i + digit)) / POW_SUMM_DIV) % mod;
                if (write(fd_out, &x, INT_BYTES) == -1) {
                    fprintf(stderr, "line 55, error in writing new value\n");
                    return 1;
                }
            }
        }
        digit += CHAR_BITS;
    }

    close(fd_in);
    close(fd_out);
    return 0;
}
