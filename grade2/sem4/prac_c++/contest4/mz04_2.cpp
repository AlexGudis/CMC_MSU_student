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