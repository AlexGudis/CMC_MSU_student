#include <iostream>

class C
{
    double num_;

  public:
    C(double val = 0) { num_ = val; }
    C(C c, double val) { num_ = c.num_ + val; }

    static double
    get_num(const C &v)
    {
        return v.num_;
    }
    C &
    operator++()
    {
        this->num_++;
        return *this;
    }
    double
    operator*(C v[2])
    {
        num_ *= v[0].num_;
        num_ *= v[1].num_;
        return num_;
    }
    C
    operator&() const
    {
        return *this;
    }
    int
    operator~() const
    {
        return ~(int) num_;
    }
};

int
operator+(int i, const C &val)
{
    return i + C::get_num(val);
}