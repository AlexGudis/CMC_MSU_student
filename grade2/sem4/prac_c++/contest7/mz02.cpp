#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <cstdio>

class Circle : public Figure
{
    double radius_;

public:
    Circle(double radius) : radius_(radius) {}

    static Circle *make(std::string data)
    {
        std::stringstream ss(data);
        double radius;
        ss >> radius;
        Circle *circle_ptr = new Circle(radius);
        return circle_ptr;
    }

    double get_square() const
    {
        return radius_ * radius_ * M_PI;
    }
};

class Rectangle : public Figure
{
    double width_, height_;

public:
    Rectangle(double width, double height) : width_(width), height_(height) {}
    static Rectangle *make(std::string data)
    {
        std::stringstream ss(data);
        double width, height;
        ss >> width >> height;
        Rectangle *rec_ptr = new Rectangle(width, height);
        return rec_ptr;
    }

    double get_square() const
    {
        return width_ * height_;
    }
};

class Square : public Figure
{
    double len_;

public:
    Square(double len) : len_(len) {}
    static Square *make(std::string data)
    {
        std::stringstream ss(data);
        double len;
        ss >> len;
        Square *ptr = new Square(len);
        return ptr;
    }

    double get_square() const
    {
        return len_ * len_;
    }
};