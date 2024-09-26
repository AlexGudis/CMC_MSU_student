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

int main(void)
{
    const std::vector<int> v1 = {1, 4, -2, 7, -5, -1, 0, 2, 4, -2, 1, 7, 7, 0, -1};
    std::vector<int> v2 = {3, 2, -7, 4, 15, -2, 0};
    process(v1, v2);
    for (auto it = v2.begin(); it != v2.end(); ++it)
    {
        std::cout << *it << ' ';
    }
}
