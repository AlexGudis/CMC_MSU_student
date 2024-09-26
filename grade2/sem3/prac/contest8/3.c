#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

enum
{
    BYTE_BIT = 8
};

int
main(int argc, char *argv[])
{
    FILE *f = fopen("input3.bin", "wb");
    unsigned char c;
    int num;
    scanf("%d", &num);
    while (num > 0) {
        scanf("%hhd", &c);
        fwrite(&c, sizeof(char), 1, f);
        num--;
        printf("NUM: %d\n", num);
    }
    fclose(f);

    if (argc != 2) {
        fprintf(stderr, "Not enought parametrs\n");
        return 1;
    }
    int fd = open(argv[1], O_RDWR);
    int size = lseek(fd, 0, SEEK_END);
    int n = 0;
    for (int i = 0; i < size * BYTE_BIT; ++i) {
        if (i * i == size * BYTE_BIT) {
            n = i;
        }
    }
    printf("N: %d\n", n);
    int index = 1;
    int cur_index = 1;
    lseek(fd, 0, SEEK_SET);
    unsigned char byte = 0;
    int offset = 0;
    while(read(fd, &byte, 1) > 0) {
        cur_index = lseek(fd, 0, SEEK_CUR) * BYTE_BIT;
        printf("Cur_index = %d\n", cur_index);
        printf("index = %d\n", index);
        if (cur_index >= index) {
            offset = cur_index - index;
            byte |= (1 << offset);
            //printf("BYTE: %hhd\n", byte);
            lseek(fd, -1, SEEK_CUR);
            write(fd, &byte, 1);
            index += n + 1;
        }
        //printf("Cur_index = %d\n", cur_index);
        //printf("index = %d\n", index);
        if (cur_index >= index) {
            lseek(fd, -1, SEEK_CUR);
        }
        //printf("CUR POSE: %ld\n", lseek(fd, 0, SEEK_CUR));
    }
    lseek(fd, 0, SEEK_SET);
    while(read(fd, &byte, 1) > 0) {
        printf("%d ", byte);
    }
}
