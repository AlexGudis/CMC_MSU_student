#include <iostream>
#include <cstdint>
#include <vector>

void process(std::vector<unsigned long> &v, unsigned int &s)
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

            /*
            for (auto &el : v)
            {
                std::cout << el << " ";
            }
            std::cout << std::endl;
            */

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

int main(void)
{
    std::vector<unsigned long> v = {2, 3, 4, 5, 6};
    unsigned int s = 2;
    process(v, s);

    for (auto &el : v)
    {
        std::cout << el << " ";
    }

    return 0;
}