#include <iostream>
#include <vector>

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