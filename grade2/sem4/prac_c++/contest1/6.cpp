#include <iostream>

constexpr double prec = 0.000000001;

class Point
{
    double x_, y_;

  public:
    Point(double x = 0, double y = 0)
    {
        x_ = x;
        y_ = y;
    }
    double
    get_x()
    {
        return x_;
    }
    double
    get_y()
    {
        return y_;
    }
};

class Line
{
    Point p1_, p2_;

  public:
    Line(Point p1, Point p2)
    {
        p1_ = p1;
        p2_ = p2;
    }
    Point
    get_p1()
    {
        return p1_;
    }
    Point
    get_p2()
    {
        return p2_;
    }
};

int
get_ans(Line line1, Line line2, double ans[2])
{
    double x1 = line1.get_p1().get_x(), y1 = line1.get_p1().get_y();
    double x2 = line1.get_p2().get_x(), y2 = line1.get_p2().get_y();
    double x3 = line2.get_p1().get_x(), y3 = line2.get_p1().get_y();
    double x4 = line2.get_p2().get_x(), y4 = line2.get_p2().get_y();

    double znam = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (abs(znam) < prec) {                                              // no intersaction definitely
        if (abs((x1 - x3) * (y4 - y3) - (x4 - x3) * (y1 - y3)) < prec) { // P1 in L2
            return 2;
        } else {
            return 0;
        }
    } else {
        ans[0] = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / znam; // x - coord
        ans[1] = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / znam; // y - coord
        return 1;
    }
    return 0;
}

int
main(void)
{
    double x1, x2, x3, x4, y1, y2, y3, y4;
    std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    Point p1(x1, y1), p2(x2, y2), p3(x3, y3), p4(x4, y4);
    Line line1(p1, p2), line2(p3, p4);
    double pp[] = {0, 0};
    int ans = get_ans(line1, line2, pp);
    std::cout << ans << std::endl;
    if (ans == 1) {
        std::cout.setf(std::ios::fixed);
        std::cout.precision(10);
        std::cout << pp[0] << " " << pp[1] << std::endl;
    }
    return 0;
}
