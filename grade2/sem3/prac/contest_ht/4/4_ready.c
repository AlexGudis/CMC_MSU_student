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
    MASK_BTHREE_DOWN = 0x3F,
    TRIPLET = 3,
    QUADRO = 4,
    ADD_BYTE = 2,
    DECODE_TABLE_LENGHT = 80,
    PLUS_INDEX = 43,
    LEFT_ONE = 2,
    RIGHT_LEFT_SEC = 4,
    S_ONE = 1,
    S_TWO = 2,
    S_THREE = 3,
    S_FOUR = 4,
    RIGHT_S_THIRD = 2,
    LEFT_S_THIRD = 6,
    MASK_S1 = 0x30,
    MASK_S2 = 0x0F,
    MASK_S3 = 0x3C,
    MASK_S4 = 0x03,
    MASK_S5 = 0x3F
};

size_t
get_encode_size(size_t size)
{
    long ans = 0;
    if (size % TRIPLET == 0) {
        ans = size / TRIPLET * QUADRO;
    } else if (size % TRIPLET == 1) {
        ans = size / TRIPLET * QUADRO + ADD_BYTE;
    } else {
        ans = size / TRIPLET * QUADRO + TRIPLET;
    }
    return ans;
}

char *
b64u_encode(const uint8_t *data, size_t size)
{
    size_t encode_size = get_encode_size(size);
    char *ans = calloc(encode_size + 1, sizeof(char));
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

int decode_table[DECODE_TABLE_LENGHT];

void
b64_decode_table()
{
    for (int i = 0; i < sizeof(alphabet) - 1; ++i) {
        decode_table[alphabet[i] - PLUS_INDEX] = i;
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
    uint8_t *ans = calloc(ans_len + 1, sizeof(uint8_t));
    size_t ans_ind = 0;
    size_t str_ind = 0;
    uint8_t str_byte = 0;
    uint8_t check_part = 1;
    uint8_t out = 0;
    int check_smth = 0;

    while (str_ind != str_len) {
        str_byte = str[str_ind];
        if (isspace(str[str_ind]) != 0) {
            str_ind++;
            continue;
        }
        str_byte = decode_table[str_byte - PLUS_INDEX];
        if (check_part == S_ONE) {
            out = str_byte << LEFT_ONE;
            check_part = S_TWO;
            check_smth = 1;
        } else if (check_part == S_TWO) {
            out |= (str_byte & MASK_S1) >> RIGHT_LEFT_SEC;
            ans[ans_ind] = out;
            ans_ind++;
            out &= 0;
            check_smth = 0;
            out = (str_byte & MASK_S2) << RIGHT_LEFT_SEC;
            check_part = S_THREE;
            check_smth = 1;
        } else if (check_part == S_THREE) {
            out |= (str_byte & MASK_S3) >> RIGHT_S_THIRD;
            ans[ans_ind] = out;
            ans_ind++;
            out &= 0;
            check_smth = 0;
            out = (str_byte & MASK_S4) << LEFT_S_THIRD;
            check_part = S_FOUR;
            check_smth = 1;
        } else if (check_part == S_FOUR) {
            out |= (str_byte & MASK_S5);
            ans[ans_ind] = out;
            ans_ind++;
            out &= 0;
            check_part = 1;
            check_smth = 0;
        }
        str_ind++;
    }

    if (check_smth && out != 0) {
        ans[ans_ind] = out;
        ans_ind++;
    }
    *p_size = ans_ind;
    *p_data = ans;
    ans[*p_size] = 0;
    return true;
}
