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
    FILE *fp = fopen ("input4.bin", "wb");
    char a;
    int digits;
    scanf("%d", &digits);
    while (digits){
        scanf("%hhu", &a);
        fwrite (&a, 1, 1, fp);
        digits--;
    }
    fclose (fp);


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
    printf("Input file: %s\n", file_input);
    long size = lseek(fd_in, 0, SEEK_END);
    printf("size: %ld\n", size);

    long x;
    while (scanf("%ld", &x) != EOF) {
        if (BYTE * size >= abs(x)) {
            char byte;
            long offset_from_start = (abs(x) - 1) / BYTE;
            long offset_in_byte = (abs(x) - 1) - offset_from_start * BYTE;
            lseek(fd_in, offset_from_start, SEEK_SET);
            read(fd_in, &byte, 1);
            printf("offset_from_start: %ld\n", offset_from_start);
            printf("offset_in_byte: %ld\n", offset_in_byte);
            printf("byte before: %d\n", byte);
            if (x > 0) {
                byte |= (1 << offset_in_byte);
            }
            else if (x < 0) {
                byte &= ~(1 << offset_in_byte);
            }
            printf("byte: %d\n", byte);
            lseek(fd_in, -1, SEEK_CUR);
            write(fd_in, &byte, 1);
        }
    }

    char check;
    lseek(fd_in, 0, SEEK_SET);
    while (read(fd_in, &check, 1) == 1){
        printf("%d ", check);
    }

    close(fd_in);
    return 0;
}

