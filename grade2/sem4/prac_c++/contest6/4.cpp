#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

template <typename It_ind, typename It_elem>
auto myremove(It_ind beg_ind, It_ind end_ind, It_elem beg_el, It_elem end_el)
{
    std::vector v(beg_ind, end_ind);
    std::sort(v.begin(), v.end());
    auto last = std::unique(v.begin(), v.end());
    v.erase(last, v.end());

    int elem_cnt = end_el - beg_el;

    // del form v2
    for (auto it = beg_el; it != end_el; ++it)
    {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    long swap_cnt = 0;
    auto ans = end_el;
    --ans;
    auto ptr = beg_el;
    std::cout << "BEFORE:" << (*ans) << std::endl;
    for (auto it_ind = v.begin(); it_ind != v.end(); ++it_ind)
    {
        if ((*it_ind) >= 0 && (*it_ind) < elem_cnt)
        {
            std::rotate(beg_el + (*it_ind) - swap_cnt, beg_el + (*it_ind) - swap_cnt + 1, end_el);

            for (auto it = beg_el; it != end_el; ++it)
            {
                std::cout << *it << ' ';
            }
            std::cout << std::endl;

            --ans;
            ++swap_cnt;
        }
    }
    if (swap_cnt == elem_cnt)
    {
        return beg_el;
    }
    else
    {
        return ans;
    }
}

int main(void)
{
    std::vector<int> vec_ind = {2, 5, 2, 5, 2, 5, 2, 5, 185, 25, -581, 581};
    std::vector<int> vec_elem = {1, 2, 3, 4, 5, 6, 7};
    auto iter = myremove(vec_ind.begin(), vec_ind.end(), vec_elem.begin(), vec_elem.end());

    for (; iter >= vec_elem.begin(); --iter)
    {
        std::cout << (*iter) << " ";
    }
    return 0;
}