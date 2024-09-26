#include <stdio.h>

enum
{
    DIVIDER = 2,
};

STYPE
bit_reverse(STYPE value)
{
    UTYPE value_u = (UTYPE) value;
    UTYPE check = (UTYPE) -1;
    UTYPE ans = 0;
    UTYPE bits_number = 0;
    while (check) {
        bits_number++;
        check /= DIVIDER;
    }

    for (UTYPE i = 0; i < bits_number; ++i) {
        if (value_u & (((UTYPE) 1) << i)) {
            ans |= ((UTYPE) 1) << (bits_number - (UTYPE) 1 - i);
        }
    }
    STYPE ans_s = (STYPE) ans;
    return ans_s;
}
