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
    std::map<std::vector<uint32_t>, int64_t> matr1{};
    std::map<std::vector<uint32_t>, int64_t> matr2{};
    uint32_t row, column;
    int64_t value;
    std::cin >> row >> column >> value;
    while (!(row == 0 && column == 0 && value == MOD))
    {
        std::vector<uint32_t> key = {row, column};
        matr1[key] = (value % MOD);
    }

    while (std::cin >> row >> column >> value)
    {
        std::vector<uint32_t> key = {row, column};
        matr2[key] = (value % MOD);
    }

    for (const auto &[key, value] : matr1)
    {
        if (value)
        {
            std::cout << key[0] << " " << key[1] << " " << value << std::endl;
        }
    }
}