#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int
maxx(int a, int b)
{
    if (a > b) {
        return a;
    }
    return b;
}

int
comp(const void *str1, const void *str2)
{
    return strncmp(*(const char **) str1, *(const char **) str2,
                   maxx(strlen(*(const char **) str1), strlen(*(const char **) str2)));
}

int
main(int argc, char *argv[])
{
    char *strings[argc - 1];
    for (int i = 1; i < argc; ++i) {
        strings[i - 1] = argv[i];
    }
    qsort(strings, argc - 1, sizeof(char *), comp);
    for (int i = 0; i < argc - 1; ++i) {
        if (strings[i]) {
            printf("%s\n", strings[i]);
        }
    }

    struct stat f1, f2;
    for (int i = 0; i < argc - 1; ++i) {
        for (int j = 0; j < argc - 1; ++j) {
            if (access(strings[i], F_OK) == -1) {
                strings[i] = NULL;
            }
            if (access(strings[j], F_OK) == -1) {
                strings[j] = NULL;
            }
            if (i != j && strings[i] && strings[j]) {
                // fill the order
                if (stat(strings[i], &f1) < 0) {
                    fprintf(stderr, "Error in stat for file i index\n");
                    return 1;
                }
                if (stat(strings[j], &f2) < 0) {
                    fprintf(stderr, "Error in stat for file j index\n");
                    return 1;
                }
                if (f1.st_ino == f2.st_ino && f1.st_dev == f2.st_dev) { // one file actually
                    printf("Check1\n");
                    printf("Files to check: %s / %s\n", strings[i], strings[j]);
                    if (i < j) {
                        strings[i] = NULL;
                    } else {
                        strings[j] = NULL;
                    }
                }
            }
        }
    }

    printf("\nans \n");
    for (int i = 0; i < argc - 1; ++i) {
        if (strings[i]) {
            printf("%s\n", strings[i]);
        }
    }
    return 0;
}
