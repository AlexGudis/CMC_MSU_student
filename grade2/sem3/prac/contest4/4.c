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
    READ_TO_INT = 4
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
    while (ret != 12) {
        //printf("LOOP\n");
        if ((check = read(fd, bt + ret, STRUCT_SIZE_BYTE - ret)) < 0) {
            fprintf(stderr, "Error while reading data\n");
            return 1;
        }
        ret += check;
    }
    for (int i = 0; i < STRUCT_SIZE_BYTE; i += READ_TO_INT) {
        fields[i % STRUCT_SIZE_INT] = ((unsigned int) bt[i]) * BYTE_ONE + ((unsigned int) bt[i + 1]) * BYTE_TWO +
                                      ((unsigned int) bt[i + 2]) * BYTE_THREE + ((unsigned int) bt[i + 3]) * BYTE_FOUR;
    }
    // printf("FIELDS key, left, right: %d %d %d\n", fields[0], fields[1], fields[2]);
    if (fields[2] != 0) {
        lseek(fd, fields[2] * STRUCT_SIZE_BYTE, SEEK_SET); // go to right index
        printNodes(fd);
    }
    printf("%d\n", fields[0]);
    if (fields[1] != 0) {
        lseek(fd, fields[1] * STRUCT_SIZE_BYTE, SEEK_SET);
        printNodes(fd);
    }
    return 0;
}

int
main(int argc, char *argv[])
{
    struct Node *root = malloc(sizeof(struct Node));
    root->key = 10;
    root->left_idx = 2;
    root->right_idx = 1;

    struct Node *rt_r = malloc(sizeof(struct Node));
    rt_r->key = 20;
    rt_r->left_idx = 0;
    rt_r->right_idx = 3;

    struct Node *rt_l = malloc(sizeof(struct Node));
    rt_l->key = 5;
    rt_l->left_idx = 0;
    rt_l->right_idx = 0;

    struct Node *rt_rr = malloc(sizeof(struct Node));
    rt_rr->key = 30;
    rt_rr->left_idx = 0;
    rt_rr->right_idx = 0;

    FILE *f_in = fopen("input4.bin", "wb");
    fwrite(root, sizeof(struct Node), 1, f_in);
    fwrite(rt_r, sizeof(struct Node), 1, f_in);
    fwrite(rt_l, sizeof(struct Node), 1, f_in);
    fwrite(rt_rr, sizeof(struct Node), 1, f_in);
    // fseek(f_in, 0L, SEEK_END);
    // int sz = ftell(f_in);
    // printf("SIZE: %d\n", sz);
    fclose(f_in);

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

    if (st.st_size < 12) { // No full Node
        return 0;
    }

    lseek(fd, 0, SEEK_SET);
    printNodes(fd);

    return 0;
}
