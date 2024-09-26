#include <iomanip>
#include <iostream>
#include <cmath>

int
main(void)
{
    double x;
    double sum = 0, sum_sq = 0;
    int cnt = 0;
    while (std::cin >> x) {
        sum += x;
        sum_sq += x * x;
        cnt++;
    }

    double avg = sum / cnt;
    std::cout.setf(std::ios::fixed);
    std::cout.precision(10);
    std::cout << avg << std::endl;
    std::cout << sqrt((sum_sq - 2 * avg * sum + cnt * avg * avg) / cnt) << std::endl;
}
