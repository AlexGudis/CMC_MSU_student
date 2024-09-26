#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

enum
{
    MASK_END = 0x0f,
    MASK_START = 0xf0,
    OFFSET = 4,
    OFFSET_BYTE_FOUR = 24,
    OFFSET_BYTE_THREE = 16,
    OFFSET_BYTE_TWO = 8,
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

    unsigned char a = 0, b = 0, c = 0;
    unsigned int empty = 0;
    while (scanf("%u", &empty) != EOF) {
        a = empty >> OFFSET_BYTE_THREE;
        b = empty >> OFFSET_BYTE_TWO;
        c = empty;
        unsigned char ans1, ans2, ans3, ans4;
        unsigned int ans;
        ans1 = MASK_END & (a >> OFFSET);
        ans2 = (MASK_START & (a << OFFSET)) | (MASK_END & (b >> OFFSET));
        ans3 = MASK_END & b;
        ans4 = c;
        ans = (ans1 << OFFSET_BYTE_FOUR) | (ans2 << OFFSET_BYTE_THREE) | (ans3 << OFFSET_BYTE_TWO) | ans4;
        unsigned int ans_new = ((empty << 4) & 0x0f000000) | ((empty << 4) & 0x00ff0000) | (empty & 0x00000fff);
        printf("Ans: %d\n", ans);
        printf("Ans: %d\n", ans_new);
        if (write(fd_out, &ans, BYTES_NUM) == -1) {
            fprintf(stderr, "cannot write in file\n");
            return 1;
        }
    }
    return 0;
}
