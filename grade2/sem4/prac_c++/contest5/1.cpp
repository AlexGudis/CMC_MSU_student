#include <iostream>
#include <bit>
#include <bitset>
#include <vector>
#include <algorithm>

bool cmp(const unsigned long &a, const unsigned long &b)
{
    return std::popcount(a) < std::popcount(b);
}

int main(void)
{
    std::vector<unsigned long> v;
    unsigned long x;
    while (std::cin >> x)
    {
        v.emplace_back(x);
    }

    std::stable_sort(v.begin(), v.end(), cmp);

    for (auto &el : v)
    {
        std::cout << el << std::endl;
    }

    return 0;
}