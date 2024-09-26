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
    printf("\n");
    for (int i = 0; i < count; i++) {
        printf("%d ", data[i]);
    }

    return;
}

int
main(void)
{
    int i = 0;
    int data[6];
    while (i != 6) {
        scanf("%d", &data[i]);
        i++;
    }
    sort_even_odd(6, data);
}

