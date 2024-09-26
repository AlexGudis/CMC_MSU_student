#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    TO_LONG_VALUE = 10000,
    TO_GET_PERCENTAGE = 1000000,
    CHECK_ROUND = 500000
};

int main(int argc, char* argv[])
{
    double value;
    long long value_ll;
    if (!argv[1]) {
        fprintf(stderr, "line 6, no default value\n");
        return 1;
    } else {
        char* eptr = NULL;
        errno = 0;
        value = strtod(argv[1], &eptr);
        if (errno || *eptr || eptr == argv[1] || (double)value != value) {
            fprintf(stderr, "line 13, cannot read value %s\n", argv[1]);
            return 1;
        }
        value_ll = (long long)(value * TO_LONG_VALUE);
    }

    for (int i = 2; argv[i] != NULL; ++i) {
        char* eptr = NULL;
        errno = 0;
        double change = strtod(argv[i], &eptr);
        if (errno || *eptr || eptr == argv[i] || (double)change != change) {
            fprintf(stderr, "line 13, cannot read value %s\n", argv[i]);
            return 1;
        }
        printf("Value before changing: %lld\n", value_ll);
        printf("Check1 : %lld\n", value_ll);
        long long change_ll = (long long)(change * TO_LONG_VALUE);
        printf("Check2 : %lld\n", change_ll);
        value_ll = value_ll * (TO_GET_PERCENTAGE + change_ll);
        printf("Check4: %lld\n", value_ll);
        int check = 0; // round
        if (value_ll % TO_GET_PERCENTAGE >= CHECK_ROUND) {
            check = 1;
        }
        value_ll /= TO_GET_PERCENTAGE;
        printf("Check5 %lld\n", value_ll);
        printf("ROUND??? %d\n", check);
        value_ll += check;
        printf("Value after changing: %lld\n", value_ll);
    }
    value = (double)value_ll / TO_LONG_VALUE;
    printf("%.4f\n", value);
    return 0;
}
