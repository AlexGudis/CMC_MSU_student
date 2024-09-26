#include <iostream>
#include <vector>
#include <cstdint>

void process(std::vector<int64_t> &vec, int64_t n)
{
    vec.reserve(vec.size() * 2);
    for (auto it = vec.rbegin(); it < vec.rend(); ++it)
    {
        if ((*it) >= n)
        {
            vec.emplace_back(*it);
        }
    }
    vec.resize(vec.size());
}

int main(void)
{
    std::vector<int64_t> vec = {0, -3, 14, 4};
    long long int n;
    std::cin >> n;
    process(vec, n);

    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        std::cout << *it << ' ';
    }
}
