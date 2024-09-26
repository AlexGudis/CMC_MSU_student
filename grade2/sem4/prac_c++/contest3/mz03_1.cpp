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
            stream << std::setprecision(10) << re_;
            stream << ",";
            stream << std::setprecision(10) << im_;
            stream << ")";
            std::string ans = stream.str();

            return ans;
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

        complex &operator+=(const complex &b)
        {
            re_ += b.re_;
            im_ += b.im_;
            return *this;
        }

        complex &operator-=(const complex &b)
        {
            re_ -= b.re_;
            im_ -= b.im_;
            return *this;
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

        complex operator-(void) const
        {
            return complex(-re_, -im_);
        }
    };
}