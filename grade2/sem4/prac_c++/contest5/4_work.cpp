
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
constexpr int64_t mod = 4294967161;

int main()
{
    std::map<std::pair<uint32_t, uint32_t>, int64_t> mp;
    uint32_t i, j;
    int64_t val;
    while (std::cin >> i >> j >> val)
    {
        if (!i && !j && val == mod)
        {
            break;
        }
        mp[{i, j}] = val;
    }
    while (std::cin >> i >> j >> val)
    {
        mp[{i, j}] += val;
        mp[{i, j}] %= mod;
    }
    for (auto &el : mp)
    {
        if (el.second)
        {
            std::cout << el.first.first << " " << el.first.second << " " << el.second << std::endl;
        }
    }
}