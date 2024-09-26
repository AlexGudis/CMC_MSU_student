#include <iostream>

class Sum
{
    int a_, b_;

  public:
    int const
    get()
    {
        return a_ + b_;
    }

    Sum(int a = 0, int b = 0) // default + non_default
    {
        a_ = a;
        b_ = b;
    }

    Sum(Sum s, int c)
    {
        a_ = s.get();
        b_ = c;
    }
};

int
main(void)
{
    int a, b, c;
    std::cin >> a >> b >> c;
    std::cout << Sum(a, b).get() << std::endl;
    std::cout << Sum(Sum(a, b), c).get() << std::endl;
    return 0;
}
