#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>

namespace numbers
{
    class complex

    {
        double re_, im_;

    public:
        complex(double re = 0, double im = 0)
        {
            re_ = re;
            im_ = im;
        }
        explicit complex(std::string s)
        {
            int i;
            std::string re = "";
            std::string im = "";
            for (i = 1; s.at(i) != ','; ++i)
            {
                re += s.at(i);
            }

            ++i;

            for (; s.at(i) != ')'; ++i)
            {
                im += s.at(i);
            }

            re_ = std::stod(re);
            im_ = std::stod(im);
        }

        double re(void) const
        {
            return re_;
        }

        double im(void) const
        {
            return im_;
        }

        double abs2(void) const
        {
            return re_ * re_ + im_ * im_;
        }

        double abs(void) const
        {
            return sqrt(re_ * re_ + im_ * im_);
        }

        std::string to_string(void) const
        {
            std::stringstream stream;
            stream << "(";
            stream << std::fixed << std::setprecision(10) << re_;
            stream << ",";
            stream << std::fixed << std::setprecision(10) << im_;
            stream << ")";
            std::string ans = stream.str();

            return ans;
        }

        complex operator+(const complex &a)
        {
            return complex(a.re_ + re_, a.im_ + im_);
        }

        friend complex operator+(const complex &a, const complex &b)
        {
            return complex(a.re_ + b.re_, a.im_ + b.im_);
        }

        friend complex operator-(const complex &a, const complex &b)
        {
            return complex(a.re_ - b.re_, a.im_ - b.im_);
        }

        friend complex operator*(const complex &a, const complex &b)
        {
            return complex(a.re_ * b.re_ - a.im_ * b.im_, a.re_ * b.im_ + a.im_ * b.re_);
        }

        friend complex operator/(const complex &a, const complex &b)
        {
            return complex((a.re_ * b.re_ + a.im_ * b.im_) / (b.re_ * b.re_ + b.im_ * b.im_), (b.re_ * a.im_ - a.re_ * b.im_) / (b.re_ * b.re_ + b.im_ * b.im_));
        }

        friend complex &operator+=(complex &a, const complex &b)
        {
            a.re_ += b.re_;
            a.im_ += b.im_;
            return a;
        }

        friend complex &operator-=(complex &a, const complex &b)
        {
            a.re_ -= b.re_;
            a.im_ -= b.im_;
            return a;
        }

        friend complex &operator*=(complex &a, const complex &b)
        {

            a = a * b;
            return a;
        }

        friend complex &operator/=(complex &a, const complex &b)
        {
            a = a / b;
            return a;
        }

        friend complex operator~(const complex &a)
        {
            return complex(a.re_, -a.im_);
        }

        complex operator-(void)
        {
            return complex(-re_, -im_);
        }
    };
    class complex_stack
    {
        int stack_pointer_; // cnt of elements in stack
        complex *stack;

    public:
        complex_stack(int stack_pointer = 0)
        {
            stack_pointer_ = stack_pointer;
            stack = new complex[stack_pointer_ + 1];
        }

        complex_stack(complex_stack old, complex new_elem)
        {
            // copy elements to the new stack and add the new_elem
            stack_pointer_ = old.stack_pointer_ + 1;
            stack = new complex[stack_pointer_ + 1];
            for (int i = 0; i <= old.stack_pointer_; ++i)
            {
                stack[i] = old.stack[i];
            }
            stack[stack_pointer_] = new_elem;
        }

        size_t size()
        {
            return (size_t)(stack_pointer_ + 1);
        }

        const complex &operator[](int i)
        {
            return stack[i];
        }

        friend complex_stack operator<<(const complex_stack &cs, const complex &c)
        {
            return complex_stack(cs, c);
        }

        friend complex &operator+(const complex_stack &cs)
        {
            return cs.stack[cs.stack_pointer_];
        }

        friend complex_stack operator~(const complex_stack &old_stack)
        {
            complex_stack new_stack = complex_stack(old_stack.stack_pointer_ - 1);
            for (int i = 0; i <= new_stack.stack_pointer_; ++i)
            {
                new_stack.stack[i] = old_stack.stack[i];
            }
            return new_stack;
        }

        ~complex_stack()
        {
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            delete[] stack;
        }
    };
}

int main(void)
{
    numbers::complex a("(1,2)");
    numbers::complex b("(3,-1)");

    a.operator+(a);

    std::cout << "re   = " << a.re() << std::endl;
    std::cout << "im   = " << a.im() << std::endl;
    std::cout << "abs2 = " << a.abs2() << std::endl;
    std::cout << "abs  = " << a.abs() << std::endl;
    std::cout << a.to_string() << std::endl;

    std::cout << "+ " << (a + b).to_string() << std::endl;
    std::cout << "- " << (a - b).to_string() << std::endl;
    std::cout << "* " << (a * b).to_string() << std::endl;
    std::cout << "/ " << (a / b).to_string() << std::endl;

    std::cout << "~ " << (~a).to_string() << std::endl;
    std::cout << "- " << (-a).to_string() << std::endl;

    std::cout << "a.re   = " << a.re() << std::endl;
    std::cout << "a.im   = " << a.im() << std::endl;
    std::cout << "b.re   = " << b.re() << std::endl;
    std::cout << "b.im   = " << b.im() << std::endl;
    a /= b;
    std::cout << "/= " << a.to_string() << std::endl;

    return 0;
}