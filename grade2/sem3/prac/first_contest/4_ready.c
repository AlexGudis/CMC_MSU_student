#include <stdio.h>
#include <stdlib.h>

int
comp(const void *a, const void *b)
{

    int x1 = *(const int *) a;
    int x2 = *(const int *) b;

    if ((x1 & 1) && (x2 & 1)){
        return (x1 < x2);
    }
    if (!(x1 & 1) && !(x2 & 1)){
        return (x1 > x2);
    }
    if ((x1 & 1) != (x2 & 1)){
        return (x1 & 1) - (x2 & 1);
    }
    return 0;
}

void
sort_even_odd(size_t count, int *data)
{
    qsort(data, count, sizeof(data[0]), comp);
    return;
}
