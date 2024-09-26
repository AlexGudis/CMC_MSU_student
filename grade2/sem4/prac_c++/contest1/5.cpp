#include <iostream>
#include <cmath>
using std::cin, std::cout;
using std::string;

enum
{
    ALPHABET = 10,
    DIGIT_START = '0',
    ALPHA_START = 'a',
    BIT_NUM = 8,
    HALF_BIT = 4,
    BIT_INT_NUM = 32,
    BASE = 2,
    READ_DATA = 17
};

long
get_val(string data)
{
    long ans = 0;
    for (int i = 0; i < BIT_NUM; ++i) {
        int num = 0;
        if (isdigit(data[i])) { // 0 - 9
            num = data[i] - DIGIT_START;
        } else { // a - f
            num = data[i] - ALPHA_START + ALPHABET;
        }
        for (int j = 0; j < HALF_BIT; ++j) {
            ans += ((num >> j) & 1) * pow(BASE, (BIT_INT_NUM - (i + 1) * HALF_BIT + j));
        }
    }
    return ans;
}

int
main(void)
{
    string data = "";
    string new_data = "";
    int cnt = 0;
    while (cin >> new_data) {
        if (cnt % READ_DATA != 0) { // not a bias
            data += new_data;
        }
        if (data.length() == BIT_NUM) {
            cout << get_val(data) << std::endl;
            data = "";
        }
        cnt++;
    }

    return 0;
}
