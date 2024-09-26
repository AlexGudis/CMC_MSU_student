#include <stdio.h>

enum
{
    BIT_TO_CHANGE = 3,
    BIT_TO_ZERO = 2,
    SYMB_LEN = 64,
    DIGITS_CNT = 10,
    ALPHABET_CNT = 26
};

int
main(void)
{
    char symbols[SYMB_LEN] = "@0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ#";
    int c;
    while ((c = getchar()) != EOF) {

        int new_letter;
        int check = 0;

        if (c >= '0' && c <= '9') {
            new_letter = c - '0' + 1;
            check = 1;
        } else if (c >= 'a' && c <= 'z') {
            new_letter = c - 'a' + DIGITS_CNT + 1;
            check = 1;
        } else if (c >= 'A' && c <= 'Z') {
            new_letter = c - 'A' + DIGITS_CNT + ALPHABET_CNT + 1;
            check = 1;
        }

        if (check) { // if c is in alphabit
            new_letter ^= (1 << BIT_TO_CHANGE);
            new_letter &= ~(1 << BIT_TO_ZERO);
            putchar(symbols[new_letter]);
        }
    }
    return 0;
}
