#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

class Sum
{
    double sum_;

public:
    Sum(void) { sum_ = 0; }
    void operator()(double n) { sum_ += n; }
    double get_sum(void)
    {
        return sum_;
    }
};

int main(void)
{
    std::vector<double> v1;
    double d;
    while (std::cin >> d)
    {
        v1.push_back(d);
    }

    int size = v1.size();
    std::vector<double> v2;
    v2.assign(v1.begin() + ((int)size * 0.1), v1.end() - ((int)size * 0.1));

    std::sort(v2.begin(), v2.end());

    int size_2 = v2.size();
    std::vector<double> v;
    v.assign(v2.begin() + ((int)size_2 * 0.1), v2.end() - ((int)size_2 * 0.1));

    Sum s = std::for_each(v.begin(), v.end(), Sum());

    std::cout << std::fixed << std::setprecision(10) << s.get_sum() / v.size() << std::endl;
    return 0;
}
