#include <iostream>

template <typename T1, typename T2>
auto myfilter(T1 cont, T2 compare)
{
    T1 new_obj{};
    for (auto it = cont.begin(); it != cont.end(); ++it)
    {
        if (compare(*it))
        {
            new_obj.insert(new_obj.end(), *it); // add to a new obj in the end
        }
    }
    return new_obj;
}