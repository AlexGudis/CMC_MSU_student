#include <iostream>
#include <istream>
#include <ostream>

namespace N
{
    std::ostream & func1(int a, int b)
    {
        return std::cout << a + b;
    }
}

class A
{
    public:
    A(int a, int b = 10, int c = 20)
    {
        N::func1(a,b) << c << std::endl;
    }
};

int
main(void)
{
    A(30,40);
    return 0;
}