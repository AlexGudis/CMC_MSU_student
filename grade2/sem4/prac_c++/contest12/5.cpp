#include <iostream>
#include <thread>
#include <mutex>

double data[3];
constexpr int thread_cnt = 3;
constexpr int op_cnt = 1000000;
constexpr int mult = 100;
std::mutex mtx;

void func(int n)
{
    for (int i = 0; i < op_cnt; ++i)
    {
        mtx.lock();
        data[n] += (n + 1) * mult;
        data[(n + 1) % thread_cnt] -= ((n + 1) * mult + 1);
        mtx.unlock();
    }
}

int main(void)
{

    std::thread th0(func, 0);
    std::thread th1(func, 1);
    std::thread th2(func, 2);

    th0.join();
    th1.join();
    th2.join();

    printf("%.10g\n", data[0]);
    printf("%.10g\n", data[1]);
    printf("%.10g\n", data[2]);

    return 0;
}