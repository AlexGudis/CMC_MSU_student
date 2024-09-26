#include <iostream>
#include <cstdint>
#include <vector>

void process(std::vector<unsigned long, std::allocator<unsigned long>> &v, unsigned int s)
{
    v.reserve(v.size() + v.size() / s + s);
    unsigned int ind = 0;
    unsigned long summ = 0;
    for (auto it = v.begin(); it != v.end(); it++)
    {
        if (ind == s)
        {
            ind = -1;
            v.insert(it, summ);

            summ -= summ;
        }
        summ += (*it);
        ind++;
    }

    if (ind == s)
    {
        ind = -1;
        v.insert(v.end(), summ);
    }
}