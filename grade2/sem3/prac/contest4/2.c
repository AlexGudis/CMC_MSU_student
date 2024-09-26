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
    D_BYTES = 8
};

int
main(int argc, char *argv[])
{
    FILE *fp = fopen ("input1.bin", "wb");
    double a = 5;
    int digits;
    scanf("%d", &digits);
    while (digits){
        double a;
        scanf("%lf", &a);
        fwrite (&a, D_BYTES, 1, fp);
        digits--;
    }
    fclose (fp);




    if (argc <= 2) {
        fprintf(stderr, "line 10, not enough parametrs\n");
    }

    char *pathname = argv[1];

    char *eptr = NULL;
    errno = 0;
    long n = strtol(argv[2], &eptr, BASE);
    if (errno || *eptr || eptr == argv[2] || (int) n != n) {
        fprintf(stderr, "Cannot convert N\n");
    }

    int fd = open(pathname, O_RDWR);
    if (fd == -1) {
        fprintf(stderr, "Problem with open file\n");
        return 1;
    }

    printf("Pathname: %s\n", pathname);
    printf("N: %ld\n", n);

    off_t file_size = lseek(fd, 0, SEEK_END); // file size
    if (file_size <= D_BYTES) {               // 1 or 0 digits
        return 0;
    }

    int check = 1;
    lseek(fd, 8, SEEK_SET); // in[1]
    double in_i;
    double out_i_1;
    off_t cur_pose;
    while (check < n && check * D_BYTES < file_size) {
        cur_pose = lseek(fd, 0, SEEK_CUR);
        printf("CUR_POSE: %ld\n", cur_pose);

        read(fd, &in_i, D_BYTES);
        lseek(fd, -D_BYTES, SEEK_CUR);
        lseek(fd, -D_BYTES, SEEK_CUR);
        printf("in_i: %lf\n", in_i);

        cur_pose = lseek(fd, 0, SEEK_CUR);
        printf("CUR_POSE: %ld\n", cur_pose);

        read(fd, &out_i_1, D_BYTES);
        printf("out_i_1: %lf\n", out_i_1);
        double out_i = in_i - out_i_1;

        cur_pose = lseek(fd, 0, SEEK_CUR);
        printf("CUR_POSE: %ld\n", cur_pose);

        write(fd, &out_i, D_BYTES);
        printf("out_i: %lf\n", out_i);
        check++;
        printf("\n");
    }
    int reading = 0;
    double check_d;
    printf("FILE_SIZE: %ld\n", lseek(fd, 0, SEEK_END));
    lseek(fd, 0, SEEK_SET);
    while (reading * D_BYTES < file_size){
        read(fd, &check_d, D_BYTES);
        printf("%lf ", check_d);
        reading++;
    }
    return 0;
}
