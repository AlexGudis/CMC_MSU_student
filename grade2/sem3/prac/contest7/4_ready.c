#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

enum
{
    BYTE = 8
};

int
main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Not enough parametrs\n");
        return 1;
    }

    char *file_input = argv[1];

    int fd_in = open(file_input, O_RDWR);
    if (fd_in == -1) {
        fprintf(stderr, "Problem with opening input file\n");
        return 1;
    }
    long size = lseek(fd_in, 0, SEEK_END);

    long x;
    while (scanf("%ld", &x) != EOF) {
        if (BYTE * size >= abs(x)) {
            char byte;
            long offset_from_start = (abs(x) - 1) / BYTE;
            long offset_in_byte = (abs(x) - 1) - offset_from_start * BYTE;
            lseek(fd_in, offset_from_start, SEEK_SET);
            read(fd_in, &byte, 1);
            if (x > 0) {
                byte |= (1 << offset_in_byte);
            } else if (x < 0) {
                byte &= ~(1 << offset_in_byte);
            }
            lseek(fd_in, -1, SEEK_CUR);
            write(fd_in, &byte, 1);
        }
    }
    close(fd_in);
    return 0;
}
