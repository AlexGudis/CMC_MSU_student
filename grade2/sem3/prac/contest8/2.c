#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

enum
{
    BASE = 17
};

int
comp(const void *a, const void *b)
{
    unsigned long long aa = *(unsigned long long *) a;
    unsigned long long bb = *(unsigned long long *) b;
    if (aa > bb) {
        return -1;
    }
    return 1;
}

int
main(int argc, char *argv[])
{
    unsigned long long *arr = calloc(argc - 1, sizeof(unsigned long long));
    for (int i = 1; i < argc; ++i) {
        errno = 0;
        char *eptr = NULL;
        unsigned long long val = strtol(argv[i], &eptr, BASE);
        if (errno || *eptr || eptr == argv[i]) {
            fprintf(stderr, "Cannot convert to ull\n");
            return 1;
        }
        arr[i - 1] = val;
    }
    qsort(arr, argc - 1, sizeof(unsigned long long), comp);
    for (int j = 0; j < argc - 1; ++j) {
        printf("%lld\n", arr[j]);
    }
}
