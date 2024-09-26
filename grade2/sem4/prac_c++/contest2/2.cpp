#include <iostream>

class C
{
    char pole_;
    const static char c;

  public:
    C(char b = 'f') { pole_ = b; }
    static void
    f()
    {
    }
};

const char C::c = '+';

int
main(void)
{
    C ob;
    C::f();
    return 0;
}
