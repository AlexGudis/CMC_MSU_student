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
main(int argc, char *argv[])
{
    int check = 0; // checking architecure of pc
    if (LLONG_MIN != -LLONG_MAX) {
        check = NOTHING_TO_DO;
    }

    if (argc <= 1) {
        fprintf(stderr, "Not enough parametrs\n");
        return 1;
    }

    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        fprintf(stderr, "Cannot open input file\n");
        return 1;
    }

    long long minn = LLONG_MAX;
    long long digit;
    long long pose = 0;
    int read_smth = 0;
    while (read(fd, &digit, LL_SIZE) == LL_SIZE) {
        read_smth = 1;
        if (digit < minn) {
            minn = digit;
            pose = lseek(fd, -LL_SIZE, SEEK_CUR);
        }
    }

    if (!(check == NOTHING_TO_DO && minn == LLONG_MIN)) {
        minn *= -1;
    }

    if (read_smth && (lseek(fd, pose, SEEK_SET) != -1)) {
        if (write(fd, &minn, LL_SIZE) == -1) {
            fprintf(stderr, "Error while writing new value in file\n");
            return 1;
        }
    }

    if (close(fd) == -1) {
        fprintf(stderr, "Error while closing file\n");
        return 1;
    }
    return 0;
}
