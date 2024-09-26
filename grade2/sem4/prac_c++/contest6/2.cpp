#include <iostream>
#include <vector>
#include <set>

bool pred(const int &value)
{
    return (value > 10 && value < 100);
}

template <typename T1, typename T2>
auto myfilter(T1 cont, T2 compare)
{
    T1 new_obj{};
    for (auto it = cont.begin(); it != cont.end(); ++it)
    {
        if (compare(*it))
        {
            std::cout << *it << std::endl;
            new_obj.insert(new_obj.end(), *it);
        }
    }
    return new_obj;
}

int main(void)
{
    std::vector<int> vec = {1, 50, 37, 1000, 200, 11, 9};
    myfilter(std::set{1, 100, 25}, pred);

    return 0;
}