#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

long
maxx(long a, long b)
{
    if (a > b) {
        return a;
    }
    return b;
}

int
main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Incorrect number of input arguments\n");
        return 1;
    }

    DIR *fir_dir = opendir(argv[1]);
    if (fir_dir == NULL) {
        fprintf(stderr, "Error in opening dir1\n");
        return 1;
    }
    struct dirent *ddir1;
    errno = 0;
    long long ans = 0;
    while ((ddir1 = readdir(fir_dir)) != NULL) {
        char filename1[PATH_MAX];
        int ret1 = snprintf(filename1, sizeof(filename1), "%s/%s", argv[1], ddir1->d_name);
        if (ret1 >= sizeof(filename1)) {
            fprintf(stderr, "Path is too long\n");
            return 1;
        }
        struct stat file1;
        if (lstat(filename1, &file1) == -1) {
            fprintf(stderr, "Error in lstat\n");
            return 1;
        }

        if (S_ISREG(file1.st_mode) && (access(filename1, W_OK) == 0)) {
            DIR *sec_dir = opendir(argv[2]);
            if (sec_dir == NULL) {
                fprintf(stderr, "Error in opening dir2\n");
                return 1;
            }
            struct dirent *ddir2;
            errno = 0;
            while ((ddir2 = readdir(sec_dir)) != NULL) {
                char filename2[PATH_MAX];
                int ret2 = snprintf(filename2, sizeof(filename2), "%s/%s", argv[2], ddir2->d_name);
                if (ret2 >= sizeof(filename2)) {
                    fprintf(stderr, "Path is too long\n");
                    return 1;
                }
                struct stat file2;
                if (stat(filename2, &file2) == -1) {
                    fprintf(stderr, "Error in stat\n");
                    return 1;
                }
                if (file1.st_ino == file2.st_ino && file1.st_dev == file2.st_dev &&
                    (!strncmp(ddir1->d_name, ddir2->d_name, maxx(strlen(ddir1->d_name), strlen(ddir2->d_name))))) {
                    ans += file1.st_size;
                }
            }

            if (errno) {
                fprintf(stderr, "Error in readding second directory: %s\n", strerror(errno));
                return 1;
            }
            if (closedir(sec_dir) == -1) {
                fprintf(stderr, "Error on closing second dir\n");
                return 1;
            }
        }
    }
    if (errno) {
        fprintf(stderr, "Error in readding first directory\n");
        return 1;
    }
    if (closedir(fir_dir) == -1) {
        fprintf(stderr, "Error on closing first dir\n");
        return 1;
    }
    printf("%lld\n", ans);
}
