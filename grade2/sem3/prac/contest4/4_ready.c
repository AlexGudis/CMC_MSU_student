#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

enum
{
    BYTE_ONE = 16777216,
    BYTE_TWO = 65536,
    BYTE_THREE = 256,
    BYTE_FOUR = 1,
    STRUCT_SIZE_BYTE = 12,
    STRUCT_SIZE_INT = 3,
    READ_TO_INT = 4,
    RIGHT_IDX = 2,
    LEFT_IDX = 1
};

struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

int
printNodes(int fd)
{
    unsigned char bt[STRUCT_SIZE_BYTE];
    int32_t fields[STRUCT_SIZE_INT];
    int ret = 0;
    int check = 0;
    while (ret != STRUCT_SIZE_BYTE) {
        if ((check = read(fd, bt + ret, STRUCT_SIZE_BYTE - ret)) == -1) {
            fprintf(stderr, "Error while reading data\n");
            return 1;
        }
        ret += check;
    }
    for (int i = 0; i < STRUCT_SIZE_BYTE; i += READ_TO_INT) {
        fields[i % STRUCT_SIZE_INT] = ((unsigned int) bt[i]) * BYTE_ONE + ((unsigned int) bt[i + 1]) * BYTE_TWO +
                                      ((unsigned int) bt[i + 2]) * BYTE_THREE + ((unsigned int) bt[i + 3]) * BYTE_FOUR;
    }
    if (fields[RIGHT_IDX] != 0) {
        if (lseek(fd, fields[RIGHT_IDX] * STRUCT_SIZE_BYTE, SEEK_SET) == -1) {
            fprintf(stderr, "Error while trying to go to the right in a tree\n");
            return 1;
        }
        printNodes(fd);
    }
    printf("%d\n", fields[0]);
    if (fields[LEFT_IDX] != 0) {
        if (lseek(fd, fields[LEFT_IDX] * STRUCT_SIZE_BYTE, SEEK_SET) == -1) {
            fprintf(stderr, "Error while trying to go to the left in a tree\n");
            return 1;
        }
        printNodes(fd);
    }
    return 0;
}

int
main(int argc, char *argv[])
{
    if (argc <= 1) {
        fprintf(stderr, "Not enough parametrs\n");
        return 1;
    }
    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        fprintf(stderr, "Cannot open file\n");
        return 1;
    }

    struct stat st;
    if (fstat(fd, &st) < 0) {
        fprintf(stderr, "Problem with stat functions\n");
        return 1;
    }

    if (st.st_size < STRUCT_SIZE_BYTE) { // No full Node
        return 0;
    }

    if (lseek(fd, 0, SEEK_SET) == -1) {
        fprintf(stderr, "Error while finding position\n");
        return 1;
    }

    printNodes(fd);

    if (close(fd) == -1) {
        fprintf(stderr, "Error while closing file\n");
        return 1;
    }

    return 0;
}
