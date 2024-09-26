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

C
func1(const C &v1, int v2)
{
    return C(v2 + v1, ~v1);
}

void
func2(const C *p1, double p2)
{
    C v1 = p2;
    C v2[2][2];
    C v3 = func1(func1(func1(&p1[3], p2), ~p1[2]), ++v1 * v2[1]);
}

int
main(void)
{
    return 0;
}
