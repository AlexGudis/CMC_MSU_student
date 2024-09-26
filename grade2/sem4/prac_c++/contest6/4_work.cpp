//
// Created by Yaroslav on 27.03.2023.
//
#include <vector>
#include <algorithm>
#include <iostream>

template <typename T1, typename T2>
T2 myremove(T1 begin, T1 end, T2 del_begin, T2 del_end)
{
    std::vector v(begin, end);
    std::sort(v.begin(), v.end());
    auto v_end = std::unique(v.begin(), v.end());

    auto v_begin = v.begin();
    for (; v_begin != v_end && *v_begin < 0; ++v_begin)
        ;
    int index = 0;
    int col = 0;
    auto tmp = del_begin;
    for (; del_begin != del_end; ++del_begin, ++index)
    {
        if (v_begin != v_end && index == *v_begin)
        {
            ++v_begin;
            ++col;
        }
        else
        {
            *tmp++ = std::move(*del_begin);
        }
    }
    if (!col)
    {
        return del_end;
    }
    return tmp;
}

int main(void)
{
    std::vector<int> vec_ind = {0, 1, 2, 3, 4, 4, 3, 2, 1, 1, 2, 3, 4, 4, 3, 2, 1};
    std::vector<int> vec_elem = {1};
    auto iter = myremove(vec_ind.begin(), vec_ind.end(), vec_elem.begin(), vec_elem.end());

    for (; iter >= vec_elem.begin(); --iter)
    {
        std::cout << (*iter) << " ";
    }
    return 0;
}