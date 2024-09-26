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
    FILE *fp = fopen ("input5.bin", "wb");
    FILE *fo = fopen("output5.bin", "wb");
    char a;
    int digits;
    scanf("%d", &digits);
    while (digits){
        scanf("%hhu", &a);
        fwrite (&a, 1, 1, fp);
        digits--;
    }
    fclose (fp);
    fclose(fo);




    if (argc <= 3) {
        fprintf(stderr, "line 10, not enough parametrs\n");
        return 1;
    }

    char *file_input = argv[1];
    char *file_output = argv[2];

    char *eptr = NULL;
    errno = 0;
    long mod = strtol(argv[3], &eptr, BASE);
    if (errno || *eptr || eptr == argv[3] || (int) mod != mod) {
        fprintf(stderr, "line 45, cannot convert mod\n");
        return 1;
    }

    int fd_in = open(file_input, O_RDONLY);
    if (fd_in == -1) {
        fprintf(stderr, "line 50, problem with opening input file\n");
        return 1;
    }

    int fd_out = open(argv[2], O_TRUNC | O_RDWR | O_CREAT, 0666);
    if (fd_out == -1){
        fprintf(stderr, "line 56, problem with opening output file\n");
        return 1;
    }


    printf("Input file: %s\n", file_input);
    printf("Output file: %s\n", file_output);
    printf("MOD: %ld\n", mod);



    char bytes;
    long long digit = 0;
    while (read(fd_in, &bytes, 1) == 1){
        int x = 0;
        //printf("bytes: %d\n", bytes);
        for (long long i = 1; i < CHAR_BITS + 1; ++i){
            if ((bytes >> (i - 1)) & 1){
                printf("X: %lld\n", i + digit);
                x = ((2*(i + digit) + 1) * ((i+digit)*(i+digit) + (i + digit)) / POW_SUMM_DIV) % mod;
                if (write(fd_out, &x, INT_BYTES) == -1){
                    fprintf(stderr, "line 76, error in writing new value\n");
                    return 1;
                }
            }
        }
        digit += CHAR_BITS;
    }

    int check;
    printf("%ld\n", lseek(fd_out, 0, SEEK_END));
    lseek(fd_out, 0, SEEK_SET);
    while (read(fd_out, &check, INT_BYTES) == 4){
        printf("%d ", check);
    }

    close(fd_in);
    close(fd_out);
    return 0;
}

