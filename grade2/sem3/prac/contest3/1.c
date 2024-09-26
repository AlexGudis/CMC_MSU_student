#include <stdio.h>

typedef signed char STYPE;
typedef unsigned char UTYPE;

enum
{
    DIVIDER = 2,
};

void
print_bits(UTYPE val, UTYPE bits_num)
{
    UTYPE arr[bits_num];
    UTYPE i = 0;
    printf("%d\n", val);
    while (val){
        arr[i] = val % 2;
        val /= 2;
        i++;
    }
    printf("BITS_OF_VALUE_U ");
    for (int i = bits_num - 1; i > -1; --i){
        printf("%d", arr[i]);
    }
    printf("\n");
}

STYPE bit_reverse(STYPE value)
{
    printf("%d\n", value);
    UTYPE value_u = (UTYPE) value;
    UTYPE check = (UTYPE) -1;
    UTYPE ans = 0;
    UTYPE bits_number = 0;
    while (check) {
        bits_number++;
        check /= DIVIDER;
    }
    printf("BITS: %d\n", bits_number);
    print_bits(value_u, bits_number);
    for (UTYPE i = 0; i < bits_number; ++i) {
        if (value_u & ( ((UTYPE) 1) << i)) {
            ans |= ((UTYPE) 1) << (bits_number - (UTYPE) 1 - i);
        }
        printf("CURRENT VALUE: %d\n", ans);
    }
    printf("UNSIGNED VALUE: %d\n", ans);
    STYPE ans_s = (STYPE) ans;
    return ans_s;
}

int main(void)
{
    signed char x;
    scanf("%hhd", &x);
    printf("%d", bit_reverse(x));
    return 0;
}
