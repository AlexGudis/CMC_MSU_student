#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
enum
{
    SIZE = 1024
};

int
main(int argc, char *argv[])
{
    long ans = 0;
    for (int i = 1; i < argc; ++i) {
        if (access(argv[i], F_OK) == 0) {
            struct stat pt;
            if (lstat(argv[i], &pt) == -1) {
                fprintf(stderr, "Error in lstat\n");
                return 1;
            }
            if (S_ISREG(pt.st_mode) && (pt.st_nlink == 1) && (pt.st_size % SIZE == 0)) {
                ans += pt.st_size;
            }
        }
    }
    printf("%ld\n", ans);
}
