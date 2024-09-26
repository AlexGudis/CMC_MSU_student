#include <stdio.h>

int myfunc(int x);

int main()
{
    int x;
    scanf("%d", &x);
    printf("result after func = %d\n", myfunc(x));
}
