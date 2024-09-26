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
    Z_INDEX = 2
};

int
maxx(int a, int b)
{
    if (a > b) {
        return a;
    }
    return b;
}

int
listFiles(char *fullpath, char *otn_path, int depth, long long size)
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

        char *otn_name = NULL;
        char *full_name = NULL;
        int ret_otn = 0;
        int ret_full = 0;
        if (depth == 1) {
            ret_otn = asprintf(&otn_name, "%s", ddir->d_name);

        } else {
            ret_otn = asprintf(&otn_name, "%s/%s", otn_path, ddir->d_name);
        }
        if (ret_otn == -1) {
            fprintf(stderr, "Error in asprintf for otn_name\n");
            return 1;
        }
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

        if (S_ISREG(sfilestat.st_mode) && (!access(full_name, R_OK)) && (sfilestat.st_size <= size)) {
            printf("%s\n", otn_name);
        }
        depth++;
        if (S_ISDIR(sfilestat.st_mode) && depth <= 4 &&
            (strncmp(s_tt, ddir->d_name, maxx(strlen(ddir->d_name), strlen(s_tt))) != 0) &&
            (strncmp(s_t, ddir->d_name, maxx(strlen(ddir->d_name), strlen(s_t))) != 0)) {
            listFiles(full_name, otn_name, depth, size);
        }
        depth--;
        free(otn_name);
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
    long long z = strtol(argv[Z_INDEX], &eptr, BASE);
    if (errno || *eptr || eptr == argv[Z_INDEX] || (long long) z != z) {
        fprintf(stderr, "Cannot convert z to int\n");
        return 1;
    }
    int ans = listFiles(argv[1], NULL, 1, z);
    if (ans) {
        fprintf(stderr, "Error in listFiles\n");
        return 1;
    }
    return 0;
}
