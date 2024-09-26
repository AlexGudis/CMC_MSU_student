#include <stdio.h>
#include <stdlib.h>

int
comp(const void *a, const void *b)
{

    int x1 = *(const int *) a;
    int x2 = *(const int *) b;

    if (abs(x1) % 2 == 1) {
        if (abs(x2) % 2 == 0)
            return 1;
        if (x1 > x2) {
            return -1;
        }
        return 1;
    }

    if (abs(x1) % 2 == 0) {
        if (abs(x2) % 2 == 1)
            return -1;
        if (x1 > x2) {
            return 1;
        }
        return -1;
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
