#include <iostream>
#include <vector>
#include <set>

template <typename T>
auto process(T cont)
{
    typename T::value_type t{};
    int n = 1;
    for (auto it = cont.rbegin(); it != cont.rend(); ++it)
    {
        if (n == 1 || n == 3 || n == 5)
        {
            t += (*it);
        }
        ++n;
    }
    return t;
}

int main(void)
{
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7};
    std::cout << process(std::set{100}) << std::endl;

    return 0;
}