#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>

enum
{
    LL_SIZE = 8,
    NOTHING_TO_DO = 1
};

int
main (int argc, char *argv[])
{
    FILE *f_in = fopen("input3.bin", "wb");
    int n;
    long long a;
    scanf("%d", &n);
    while (n){
        scanf("%lld", &a);
        fwrite(&a, sizeof(a), 1, f_in);
        n--;
    }
    fclose(f_in);

    int check = 0; // checking architecure of pc
    if (LLONG_MIN != -LLONG_MAX){
        check = NOTHING_TO_DO;
    }


    if (argc <= 1){
        fprintf(stderr, "line , not enough parametrs\n");
        return 1;
    }

    int fd = open(argv[1], O_RDWR);
    if (fd == -1){
        fprintf(stderr, "line , cannot open input file\n");
        return 1;
    }

    long long minn = LLONG_MAX;
    long long digit;
    long long pose = -1;
    while(read(fd, &digit, LL_SIZE) == LL_SIZE){
        if (digit < minn){
            minn = digit;
            pose = lseek(fd, -LL_SIZE, SEEK_CUR);
       }
    }

    printf("Digit min: %lld\n", minn);
    if (!(check == NOTHING_TO_DO && minn == LLONG_MIN)){
        minn *= -1;
    }
    printf("Write it:%lld\n", minn);
    printf("On pose: %lld\n", pose);

    if (pose != -1 && lseek(fd, pose, SEEK_SET) != -1){
        printf("Writing...\n");
        if(write(fd, &minn, LL_SIZE) == -1){
            fprintf(stderr, "line , error while writing new value in file\n");
            return 1;
        }
    }

    lseek(fd, 0, SEEK_SET);
    long long b;
    while (read(fd, &b, sizeof(long long))){
        printf("%lld ", b);
    }

    if (close(fd) == -1){
        fprintf(stderr, "Error while closing file\n");
        return 1;
    }
    return 0;
}
