#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stdint.h>

enum
{
    MOD = 4294967161
};

int main(void)
{
    std::map<std::vector<uint32_t>, int64_t> matr{};
    uint32_t row, column;
    int64_t value;
    while (std::cin >> row >> column >> value)
    {
        if (row == 0 && column == 0 && value == MOD)
        {
            continue; // next matrix
        }
        std::vector<uint32_t> key = {row, column};
        if (matr.find(key) == matr.end())
        {
            matr[key] = 0;
        }
        matr[key] += (value % MOD);
        matr[key] %= MOD;
    }
    for (const auto &[key, value] : matr)
    {
        if (value)
        {
            std::cout << key[0] << " " << key[1] << " " << value << std::endl;
        }
    }
}