#include <iostream>

class Sum
{
    int a_, b_;

  public:
    int
    get() const
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