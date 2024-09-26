#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

enum
{
    MASK_B_ONE = 0x0f000000,
    MASK_B_TWO = 0x00ff0000,
    MASK_B_THREE_FOUR = 0x00000fff,
    OFFSET = 4,
    BYTES_NUM = 4
};

int
main(int argc, char *argv[])
{
    if (argc <= 1) {
        fprintf(stderr, "Not enough parametrs\n");
        return 1;
    }

    int fd_out = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0600);
    if (fd_out == -1) {
        fprintf(stderr, "Cannot open file\n");
        return 1;
    }

    unsigned int empty = 0;
    unsigned int ans_little_end = 0;
    unsigned int ans = 0;
    while (scanf("%u", &empty) != EOF) {
        ans_little_end =
            ((empty << OFFSET) & MASK_B_ONE) | ((empty << OFFSET) & MASK_B_TWO) | (empty & MASK_B_THREE_FOUR);
        ans = __builtin_bswap32(ans_little_end);
        if (write(fd_out, &ans, BYTES_NUM) == -1) {
            fprintf(stderr, "cannot write in file\n");
            return 1;
        }
    }

    close(fd_out);
    return 0;
}
