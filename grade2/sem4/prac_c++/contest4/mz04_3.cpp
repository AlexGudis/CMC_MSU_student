#include <iostream>
#include <vector>
#include <algorithm>

void process(const std::vector<int> &v1, std::vector<int> &v2)
{
    // sort v1
    std::vector<int> v(v1);
    std::sort(v.begin(), v.end());
    auto last = std::unique(v.begin(), v.end());
    v.erase(last, v.end());

    // del form v2
    int count = 0;
    for (auto it = v.begin(); it < v.end(); ++it)
    {
        if ((*it) >= 0 && ((*it) - count) < (int)v2.size())
        {
            v2.erase(v2.begin() + (*it) - count);
            count++;
        }
    }
}