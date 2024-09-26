#include <iostream>
#include <stdint.h>

struct Result
{
    int64_t cur_val_;

    Result(int64_t cur_val = 0) : cur_val_(cur_val) {}
};

int64_t func(int64_t a, int64_t b, uint32_t k)
{

    if (!k)
    {
        throw Result(a + b);
    }

    else if (k > 0 && b == 1)
    {
        throw Result(a);
    }
    else
    {
        Result data;
        try
        {
            data.cur_val_ = func(a, b - 1, k);
        }
        catch (Result &r)
        {
            data.cur_val_ = r.cur_val_;
        }

        throw func(a, data.cur_val_, k - 1);
    }
}

int64_t func1(int64_t a, int64_t b, uint32_t k)
{
    if (!k)
    {
        return a + b;
    }
    else if (k > 0 && b == 1)
    {
        return a;
    }
    else
    {
        return func1(a, func1(a, b - 1, k), k - 1);
    }
}

int main(void)
{
    int64_t a, b;
    uint32_t k;
    while (std::cin >> a >> b >> k)
    {
        std::cout << func1(a, b, k) << std::endl;
        Result data;
        try
        {
            data.cur_val_ = func(a, b, k);
        }
        catch (Result &r)
        {
            data.cur_val_ = r.cur_val_;
        }

        std::cout << data.cur_val_;
    }
    return 0;
}