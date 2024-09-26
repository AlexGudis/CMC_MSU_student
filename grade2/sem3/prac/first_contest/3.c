#include <stdio.h>
#include <stdlib.h>

enum
{
    MAX_VALUE = 2000,
    MIN_VALUE = 1
};

int
fast_degree(int degr, int a, int n)
{
    int res = 1;
    int mult = a;
    while (degr != 0) {
        if (degr % 2) {
            res *= mult;
            res = res % n;
        }
        mult *= mult;
        mult = mult % n;
        degr /= 2;
    }
    return res;
}

int
main(void)
{
    int n;
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "3.c, line 32, cannot read n value\n");
        return 1;
    }
    if (n >= MAX_VALUE || n <= MIN_VALUE) {
        fprintf(stderr, "3.c, line 36, incorrect n\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            printf("%d ", i * fast_degree(n - 2, j + 1, n) % n);
        }
        printf("\n");
    }

    return 0;
}
