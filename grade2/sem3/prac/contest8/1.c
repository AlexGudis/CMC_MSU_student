#include <stdio.h>
#include <stdlib.h>

enum
{
    COUNT = 3
};

int
comp(const void *a, const void *b)
{
    long long aa = *(long long *) a;
    long long bb = *(long long *) b;
    if (aa > bb) {
        return 1;
    }
    return -1;
}

int
main(void)
{
    long long len = COUNT;
    long long *arr = calloc(len, sizeof(long long));
    long long index = 0;
    long long val = 0;
    while (scanf("%lld", &val) == 1) {
        if (index == len) {
            len += COUNT;
            arr = realloc(arr, len * sizeof(long long));
        }
        arr[index] = val;
        index++;
    }
    qsort(arr, index, sizeof(long long), comp);
    long long ans = 0;
    for (long long i = 0; i < (index + 1) / 2; ++i) {
        if (i == index - i - 1) {
            ans += arr[i];
        }
        else {
            ans += (arr[i] + arr[index - i - 1]);
        }
    }

    printf("%lld\n", ans);
    return 0;
}
