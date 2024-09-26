#include <iostream>
#include <vector>
#include <set>

template <class T>
class comparator
{
public:
    comparator() = default;
    bool operator()(const T &lhs, const T &rhs) const
    {
        if (lhs < rhs)
            return true;
        return false;
    }
};

template <typename Iterator, typename Compare = std::less<>>
void selection_sort(Iterator start, Iterator stop, Compare comp = Compare{})
{
    for (auto i = start; i != stop; ++i)
    {
        auto min_idx = i;
        for (auto j = i; j != stop; ++j)
        {
            if (comp(*j, *min_idx))
                min_idx = j;
        }

        if (min_idx != i)
            std::swap(*min_idx, *i);
    }
}