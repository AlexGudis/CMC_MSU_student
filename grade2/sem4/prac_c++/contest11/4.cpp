#include <iostream>
#include <cstdio>

class Figure
{
public:
    virtual ~Figure() = default;
    virtual bool equals(const Figure *ptr) const = 0;
};

class Rectangle : public Figure
{
    int width_, height_;

public:
    Rectangle(int width, int height) : width_(width), height_(height) {}

    bool equals(const Figure *ptr) const
    {
        auto *rec = dynamic_cast<const Rectangle *>(ptr);
        if (rec != nullptr)
        {
            if (this->width_ == rec->width_ && this->height_ == rec->height_)
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

    bool equals(const Figure *ptr) const
    {
        auto *rec = dynamic_cast<const Triangle *>(ptr);
        if (rec != nullptr)
        {
            if (this->a_ == rec->a_ && this->b_ == rec->b_ && this->c_ == rec->c_)
            {
                return true;
            }
        }
        return false;
    }
};
