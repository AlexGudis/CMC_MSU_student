#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

enum
{
    BASE = 10,
    UID_INDEX = 2
};

int
maxx(int a, int b)
{
    if (a > b) {
        return a;
    }
    return b;
}

long ans = 0;

int
listFiles(char *fullpath, int depth, long uid)
{
    struct dirent *ddir;
    DIR *dir = opendir(fullpath);
    if (dir == NULL && depth == 1) {
        fprintf(stderr, "Cannot open first directory\n");
        return 1;
    }
    if (dir == NULL && depth != 1) {
        return 0;
    }
    char *s_tt = "..";
    char *s_t = ".";
    while ((ddir = readdir(dir)) != NULL) {
        char *full_name = NULL;
        int ret_full = 0;
        ret_full = asprintf(&full_name, "%s/%s", fullpath, ddir->d_name);
        if (ret_full == -1) {
            fprintf(stderr, "Error in asprintf for fullpath\n");
            return 1;
        }

        struct stat sfilestat;
        if (lstat(full_name, &sfilestat) < 0) {
            fprintf(stderr, "Error in stat for filename %s: %s\n", full_name, strerror(errno));
            return 1;
        }

        if (S_ISREG(sfilestat.st_mode) && sfilestat.st_uid == uid) {
            printf("%s\n", full_name);
            ans += sfilestat.st_size;
        }
        depth++;
        if (S_ISDIR(sfilestat.st_mode) &&
            (strncmp(s_tt, ddir->d_name, maxx(strlen(ddir->d_name), strlen(s_tt))) != 0) &&
            (strncmp(s_t, ddir->d_name, maxx(strlen(ddir->d_name), strlen(s_t))) != 0)) {
            int check = listFiles(full_name, depth, uid);
            if (check) {
                return 1;
            }
        }
        depth--;
        free(full_name);
    }

    closedir(dir);
    return 0;
}

int
main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Incorrect number of input arguments\n");
        return 1;
    }

    char *eptr = NULL;
    errno = 0;
    long uid = strtol(argv[UID_INDEX], &eptr, BASE);
    if (errno || *eptr || eptr == argv[UID_INDEX] || (int) uid != uid) {
        fprintf(stderr, "Cannot convert uid to long\n");
        return 1;
    }
    int check = listFiles(argv[1], 1, uid);
    if (check == -1) {
        fprintf(stderr, "Error in listFiles\n");
        return 1;
    }
    printf("%ld\n", ans);
    return 0;
}
