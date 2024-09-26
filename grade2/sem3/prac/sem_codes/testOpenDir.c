#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

enum
{
    ERR_INCORRECT_NUM_OF_ARGS = 1,
    ERR_INCORRECT_OPEN_DIR = 2,
    ERR_IN_READDIR = 3,
    ERR_IN_FULL_PATH = 4,
    ERR_IN_LSTAT = 5
};

int
main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Incorrect number of input arguments\n");
        return ERR_INCORRECT_NUM_OF_ARGS;
    }

    DIR* dir = opendir(argv[1]);
    if (dir == NULL) {
        fprintf(stderr, "Error in opening dir %s : %s\n", argv[1], strerror(errno));
        return ERR_INCORRECT_OPEN_DIR;
    }

    struct dirent *ddir;
    errno = 0;
    while((ddir = readdir(dir)) != NULL) {
        printf("current filename: %s\n", ddir->d_name);

        char filenameBuf[PATH_MAX];
        int ret = snprintf(filenameBuf, sizeof(filenameBuf), "%s/%s", argv[1], ddir->d_name);
        if (ret >= sizeof(filenameBuf))
        {
            fprintf(stderr, "Absolute path is too long\n");
            return ERR_IN_FULL_PATH;
        }

        struct stat sfilestat;
        if (lstat(filenameBuf, &sfilestat) < 0)
        {
            /*Try to check if filename is file, not dir */
            fprintf(stderr, "Error in lstat for filename %s: %s\n", filenameBuf, strerror(errno));
            return ERR_IN_LSTAT;
        }

        if (S_ISDIR(sfilestat.st_mode))
        {
            printf("File %s is directory\n", filenameBuf);
        }
    }

    if (errno) {
        fprintf(stderr, "Error in readdir: %s\n", strerror(errno));
        return ERR_IN_READDIR;
    }

    closedir(dir);
}
