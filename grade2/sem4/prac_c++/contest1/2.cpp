#include <iostream>

class A
{
    int num_;
    int construct_;

  public:
    A()
    {
        int dg;
        std::cin >> dg;
        num_ = dg;
        construct_ = 1;
    }
    A(A &a)
    {
        int dg;
        std::cin >> dg;
        num_ = dg + a.num_;
        construct_ = 2;
    }

    ~A()
    {
        if (construct_ == 2) {
            std::cout << num_ << std::endl;
        }
    }
};

int
main(void)
{
    A a, b(a);
    return 0;
}
