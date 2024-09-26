#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

enum
{
    ACCESS_BASE = 8,
    BASE = 10
};

int
main(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i) {
        char *eptr = NULL;
        errno = 0;
        long digit = strtol(argv[i], &eptr, ACCESS_BASE);
        if (errno || *eptr || eptr == argv[i] || (int) digit != digit) {
            fprintf(stderr, "Cannot convert N\n");
            return 1;
        }

        char s[ACCESS_BASE + 1] = {"rwxrwxrwx"};
        for (int j = ACCESS_BASE; j > -1; --j) {
            long check = digit;
            if ((check >> j) & 1) {
                printf("%c", s[ACCESS_BASE - j]);
            } else {
                printf("-");
            }
        }
        printf("\n");
    }
    return 0;
}
