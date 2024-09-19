#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int p(int a, int b){
    int tmp = a;
    for (int i = 0; i < b-1; i++){
        a *= tmp;
    }
    return a;
}

int main(void)
{
    uint16_t x;
    scanf("%hx", &x);
    int base = x, ans = 0;
    for (int i = 1; i < 5; i++){
        for (int j = 1; j < 5; j++){
            x = x << (4 * (i-1) + (j-1));
            x = x & 0x8000;
            x = x >>  (16 - ( (17-i) - (j-1)*4));
            ans = ans | x;
            x = base;
        }
    }
    printf("%04x", ans);
    return 0;
}
