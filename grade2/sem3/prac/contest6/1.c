#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>

enum
{
    LETTERS_CHECK = 3
};

int
main(int argc, char *argv[])
{
    int ans = 0;
    if (argc != 2) {
        fprintf(stderr, "Incorrect number of input arguments\n");
        return 1;
    }

    DIR *dir = opendir(argv[1]);
    if (dir == NULL) {
        fprintf(stderr, "Error in opening dir %s : %s\n", argv[1], strerror(errno));
        return 1;
    }

    struct dirent *ddir;
    errno = 0;
    while ((ddir = readdir(dir)) != NULL) {
        // printf("current filename: %s\n", ddir->d_name);

        char filenameBuf[PATH_MAX];
        int ret = snprintf(filenameBuf, sizeof(filenameBuf), "%s/%s", argv[1], ddir->d_name); // creates full path
        if (ret >= sizeof(filenameBuf)) {
            fprintf(stderr, "Absolute path is too long\n");
            return 1;
        }

        struct stat sfilestat;
        if (stat(filenameBuf, &sfilestat) < 0) {
            fprintf(stderr, "Error in stat for filename %s: %s\n", filenameBuf, strerror(errno));
            return 1;
        }

        int check = 0;
        int len = strlen(filenameBuf);
        for (int i = 0; i < len; ++i) {
            if (filenameBuf[i] == '.') {
                if (i + 1 < len && filenameBuf[i + 1] == 'e' && i + 2 < len && filenameBuf[i + 2] == 'x' &&
                    i + 3 < len && filenameBuf[i + 3] == 'e' && i + 4 == len) {
                    check = 1;
                    break;
                }
            }
        }
        // printf("File %s has %d\n", filenameBuf, check);
        if ((!S_ISDIR(sfilestat.st_mode)) && (!access(filenameBuf, X_OK)) && S_ISREG(sfilestat.st_mode) && check) {
            // printf("File %s is cool\n", filenameBuf);
            ans++;
        }
    }
    printf("%d\n", ans);
    closedir(dir);
}
