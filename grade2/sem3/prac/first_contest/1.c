#include <stdio.h>

int main(void)
{
    double x, y;
    scanf("%lf", &x);
    scanf("%lf", &y);
    if ((x >= 2 && x <= 3) && (y >= 1 && y <= 7)) {
        // printf("check1\n");
        printf("1\n");
    } else if ((x >= 3 && x <= 5) && (y >= 3 && y <= 7)) {
        // printf("check2\n");
        printf("1\n");
    } else if ((x >= 3 && x <= 5) && (y >= x - 2 && y <= 3)) {
        // printf("check3\n");
        printf("1\n");
    } else {
        printf("0\n");
    }
    return 0;
}
