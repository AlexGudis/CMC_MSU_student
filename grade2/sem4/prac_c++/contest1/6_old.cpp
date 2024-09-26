#include <iostream>

class Point
{
    int x_, y_;

  public:
    Point(int x = 0, int y = 0)
    {
        x_ = x;
        y_ = y;
    }
    int
    get_x()
    {
        return x_;
    }
    int
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
    int x1 = line1.get_p1().get_x(), y1 = line1.get_p1().get_y();
    int x2 = line1.get_p2().get_x(), y2 = line1.get_p2().get_y();
    int x3 = line2.get_p1().get_x(), y3 = line2.get_p1().get_y();
    int x4 = line2.get_p2().get_x(), y4 = line2.get_p2().get_y();

    int znam = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (znam) {
        double px = (double) ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / znam;
        double py = (double) ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / znam;
        ans[0] = px;
        ans[1] = py;
        return 1;
    } else {
        int a1 = x2 - x1, b1 = y2 - y1, a2 = x4 - x3, b2 = y4 - y3;

        if (((x3 - x1) * b1 - a1 * (y3 - y1)) == 0 && ((x3 - x1) * b2 - a2 * (y3 - y1)) == 0 &&
            (a1 * b2 - a2 * b1) == 0) {
            return 2;
        } else {
            return 0;
        }
    }
    return 0;
}

int
main(void)
{
    int x1, x2, x3, x4, y1, y2, y3, y4;

    for (x3 = 0; x3 < 1000; ++x3) {
        for (x4 = 0; x4 < 1000; ++x4) {
            Point p1(-4, 1), p2(72, 2), p3(x3, 4), p4(x4, 6);
            Line line1(p1, p2), line2(p3, p4);
            double pp[] = {0, 0};
            int ans = get_ans(line1, line2, pp);
            /*
            std::cout << "x1 y1: " << x1 << " " << y1 << std::endl;
            std::cout << "x2 y2: " << x2 << " " << y2 << std::endl;
            std::cout << "x3 y3: " << x3 << " " << y3 << std::endl;
            std::cout << "x4 y4: " << x4 << " " << y4 << std::endl;
            */
            // std::cout << ans << std::endl;
            if (ans == 1) {
                if (pp[0] > 100000 || pp[1] > 100000) {
                    std::cout << "ALERT!!!" << std::endl;
                    std::cout.setf(std::ios::fixed);
                    std::cout.precision(7);
                    std::cout << pp[0] << " " << pp[1] << std::endl;
                }
                // std::cout.setf(std::ios::fixed);
                // std::cout.precision(7);
                // std::cout << pp[0] << " " << pp[1] << std::endl;
            }
        }
    }

    /*
        Point p1(x1, y1), p2(x2, y2), p3(x3, y3), p4(x4, y4);
        Line line1(p1, p2), line2(p3, p4);
        double pp[] = {0, 0};
        int ans = get_ans(line1, line2, pp);
        std::cout << ans << std::endl;
        if (ans == 1) {
            std::cout.setf(std::ios::fixed);
            std::cout.precision(7);
            std::cout << pp[0] << " " << pp[1] << std::endl;
        }
        */
    return 0;
}
