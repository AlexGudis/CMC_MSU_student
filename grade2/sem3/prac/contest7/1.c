#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum
{
    DEGREE = 3,
    PASS_OVERFLOW = 2
};

int
main(void)
{
    int c, check_overflow;
    long long ans = 0;
    long long ans_tmp = 0;
    int check = 0;
    int ans_overflow = 0;
    while ((c = getchar()) != EOF) {
        if (c == 'a') {
            check_overflow = 0;
            check = 1;
            ans_tmp = ans;
            check_overflow = __builtin_mul_overflow(ans, DEGREE, &ans);
            if (check_overflow && ans_tmp > 0) {
                check_overflow = 0;
                ans = ans_tmp;
                check_overflow += __builtin_sub_overflow(ans, 1, &ans);
                check_overflow += __builtin_mul_overflow(ans, DEGREE, &ans);
                check_overflow += __builtin_add_overflow(ans, PASS_OVERFLOW, &ans);
                if (check_overflow > 0) {
                    ans_overflow = 1;
                }
            } else if (!check_overflow) {
                ans -= 1;
            } else {
                ans_overflow = 1;
            }
        } else if (c == '1') {
            check_overflow = 0;
            check = 1;
            ans_tmp = ans;
            check_overflow = __builtin_mul_overflow(ans, DEGREE, &ans);
            if (check_overflow && ans_tmp < 0) {
                check_overflow = 0;
                ans = ans_tmp;
                check_overflow += __builtin_add_overflow(ans, 1, &ans);
                check_overflow += __builtin_mul_overflow(ans, DEGREE, &ans);
                check_overflow += __builtin_sub_overflow(ans, PASS_OVERFLOW, &ans);
                if (check_overflow > 0) {
                    ans_overflow = 1;
                }
            } else if (!check_overflow) {
                ans += 1;
            } else {
                ans_overflow = 1;
            }

        } else if (c == '0') {
            check = 1;
            check_overflow = __builtin_mul_overflow(ans, DEGREE, &ans);
            if (check_overflow) {
                ans_overflow = 1;
            }
        }
        if (check && isspace(c)) {
            if (ans_overflow) {
                printf("18446744073709551616\n");
            } else {
                printf("%lld\n", ans);
            }
            ans = 0;
            check = 0;
            ans_overflow = 0;
        }
    }
    if (check) {
        if (ans_overflow) {
            printf("18446744073709551616\n");
        } else {
            printf("%lld\n", ans);
        }
    }
    return 0;
}
