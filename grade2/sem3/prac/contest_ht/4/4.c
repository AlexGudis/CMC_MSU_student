#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include <stdint.h>
#include <string.h>
#include <ctype.h>

const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

enum
{
    BYTE_ONE = 1,
    BYTE_TWO = 2,
    BYTE_THREE = 3,
    FIRST_SIX = 2,
    SECOND_SIX = 4,
    THIRD_SIX_LEFT = 2,
    THIRD_SIX_RIGHT = 6,
    MASK_BONE_UP = 0xFC,
    MASK_BONE_DOWN = 0x03,
    MASK_BTWO_UP = 0xF0,
    MASK_BTWO_DOWN = 0x0F,
    MASK_BTHREE_UP = 0xC0,
    MASK_BTHREE_DOWN = 0x3F
};

size_t
get_encode_size(size_t size)
{
    long ans = 0;
    if (size % 3 == 0) {
        ans = size / 3 * 4;
    } else if (size % 3 == 1) {
        ans = size / 3 * 4 + 2;
    } else {
        ans = size / 3 * 4 + 3;
    }
    return ans;
}

char *
b64u_encode(const uint8_t *data, size_t size)
{
    size_t encode_size = get_encode_size(size);
    char *ans = calloc(encode_size, sizeof(char));
    if (ans == NULL) {
        return NULL;
    }
    size_t data_ind = 0;
    size_t ans_ind = 0;
    uint8_t check_part = BYTE_ONE; // byte number
    uint8_t data_byte = 0;
    uint8_t out = 0;
    while (data_ind != size) {
        data_byte = data[data_ind];
        if (check_part == BYTE_ONE) {
            out = (data_byte & MASK_BONE_UP) >> FIRST_SIX;
            ans[ans_ind] = alphabet[out];
            ans_ind++;
            out &= 0;
            out = (data_byte & MASK_BONE_DOWN) << SECOND_SIX;
            check_part = BYTE_TWO;
        } else if (check_part == BYTE_TWO) {
            out |= (data_byte & MASK_BTWO_UP) >> SECOND_SIX;
            ans[ans_ind] = alphabet[out];
            ans_ind++;
            out &= 0;
            out = (data_byte & MASK_BTWO_DOWN) << THIRD_SIX_LEFT;
            check_part = BYTE_THREE;
        } else if (check_part == BYTE_THREE) {
            out |= (data_byte & MASK_BTHREE_UP) >> THIRD_SIX_RIGHT;
            ans[ans_ind] = alphabet[out];
            ans_ind++;
            out &= 0;
            out = (data_byte & MASK_BTHREE_DOWN);
            ans[ans_ind] = alphabet[out];
            ans_ind++;
            out &= 0;
            check_part = BYTE_ONE;
        }
        data_ind++;
    }
    if (ans_ind != encode_size) {
        ans[ans_ind] = alphabet[out];
        ans_ind++;
    }
    ans[ans_ind] = '\0';
    return ans;
}

int decode_table[80];


void b64_decode_table()
{
	for (int i = 0; i < sizeof(alphabet) - 1; ++i) {
		decode_table[alphabet[i]-43] = i;
	}
}

bool
b64u_decode(const char *str, uint8_t **p_data, size_t *p_size)
{
    long len = strlen(str);
    if (str == NULL) {
        return false;
    }
    for (int i = 0; i < len; ++i) {
        if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') ||
              (str[i] >= '0' && str[i] <= '9') || str[i] == '-' || str[i] == '_' || isspace(str[i]) != 0)) {
            return false;
        }
    }
    b64_decode_table();

    long ans_len = strlen(str);
    long str_len = strlen(str);
    //printf("ANS LEN: %ld\n", ans_len);
    uint8_t *ans = calloc(ans_len + 100, sizeof(uint8_t));
    size_t ans_ind = 0;
    size_t str_ind = 0;
    uint8_t str_byte = 0;
    uint8_t check_part = 1;
    uint8_t out = 0;
    int check_smth = 0;


    int cnt = 0;
    while (str_ind != str_len) {
        str_byte = str[str_ind];
        if (isspace(str[str_ind]) != 0) {
            str_ind++;
            continue;
        }
        str_byte = decode_table[str_byte - 43];
        if (check_part == 1) {
            out = str_byte << 2;
            check_part = 2;
            check_smth = 1;
        }
        else if (check_part == 2) {
            out |= (str_byte & 0x30) >> 4;
            ans[ans_ind] = out;
            printf("Write %u on index %ld in part 2\n", out, ans_ind);
            ans_ind++;
            out &= 0;
            check_smth = 0;
            out = (str_byte & 0x0F) << 4;
            check_part = 3;
            check_smth = 1;
        }
        else if (check_part == 3) {
            out |= (str_byte & 0x3C) >> 2;
            printf("Write %u on index %ld in part 3\n", out, ans_ind);

            ans[ans_ind] = out;
            ans_ind++;
            out &= 0;
            check_smth = 0;
            out = (str_byte & 0x03) << 6;
            check_part = 4;
            check_smth = 1;
        }
        else if (check_part == 4) {
            out |= (str_byte & 0x3F);
            printf("Write %u on index %ld in part 4\n", out, ans_ind);
            ans[ans_ind] = out;
            ans_ind++;
            out &= 0;
            check_part = 1;
            check_smth = 0;
        }
        str_ind++;
    }

    if (check_smth && out != 0) {
        printf("Write %u on index %ld\n", out, ans_ind);
        ans[ans_ind] = out;
        ans_ind++;
    }

    //printf("SIZE ATER LOOP: %d\n", cnt);
    *p_size = ans_ind;
    //printf("SIZE %ld\n", *p_size);
    *p_data = ans;
    ans[*p_size] = 0;
    //printf("Size in func: %ld\n", strlen(ans));
    printf("Decode size: %ld\n", *p_size);
    //printf("Dec ans: %s\n", ans);
    printf("Decode: %s\n", *p_data);
    return true;
}

int
main(void)
{
    char *s = malloc(sizeof(char) * 10000);
    fgets(s, 10000, stdin);
    printf("\n");
    printf("Input size: %ld\n", strlen(s));
    char *encoded = b64u_encode(s, strlen(s));
    printf("Encode size: %ld\n", strlen(encoded));
    printf("Encode: %s\n", b64u_encode(s, strlen(s)));
    printf("Decoded\n");
    uint8_t *p_data = malloc(sizeof(char) * 100);
    size_t p_size;
    printf("true or false: %d\n", b64u_decode(s, &p_data, &p_size));
    //printf("Check2\n");
    //printf("Size in main: %ld\n", p_size);
    //printf("Check3\n");
    //printf("Decode str in main: %s\n", p_data);
    return 0;
}
