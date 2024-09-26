#include <iostream>

class Figure
{
public:
    virtual ~Figure() = default;
    virtual bool equals(Figure *ptr) const = 0;
};

class Rectangle : public Figure
{
    int width_, height_;

public:
    Rectangle(int width, int height) : width_(width), height_(height) {}

    bool equals(Figure *ptr) const
    {
        Rectangle *rec = dynamic_cast<Rectangle *>(ptr);
        if (rec)
        {
            if (width_ == rec->width_ && height_ == rec->height_)
            {
                return true;
            }
        }
        return false;
    }
};

class Triangle : public Figure
{
    int a_, b_, c_;

public:
    Triangle(int a, int b, int c) : a_(a), b_(b), c_(c) {}

    bool equals(Figure *ptr) const
    {
        Triangle *rec = dynamic_cast<Triangle *>(ptr);
        if (rec)
        {
            if (a_ == rec->a_ && b_ == rec->b_ && c_ == rec->c_)
            {
                return true;
            }
        }
        return false;
    }
};

/*
class Square : Figure
{
    double len_ = 0;

public:
    Square(double len)
    {
        len_ = len;
    }
    static Square *make(std::string data)
    {
        Square *ptr = new Square(std::stod(data));
        return ptr;
    }

    double get_square() const override
    {
        return len_ * len_;
    }
};
*/

int main(void)
{

    Rectangle r1(10, 5), r2(10, 2), r3(10, 5), r4(5, 10);
    Triangle tr1(1, 2, 3), tr2(3, 2, 1), tr3(1, 2, 3);
    //[[__attribute_maybe_unused__]] Figure *f = &r1;
    Rectangle *r_ptr = &r1;
    Triangle *tr_ptr = &tr1;
    std::cout << r_ptr->equals(tr_ptr) << std::endl;
    return 0;
}