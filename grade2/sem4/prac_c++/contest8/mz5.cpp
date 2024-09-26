#include <iostream>
#include <string>
#include <cstdint>
#include <sstream>
#include <cmath>

uint64_t get_day(int year, int month, int day)
{
    int a = (14 - month) / 12;
    int y = year + 4800 - a;
    int m = month + 12 * a - 3;
    uint64_t ans = day + (153 * m + 2) / 5 + 365 * y + (y / 4) - (y / 100) + (y / 400) - 32045;
    return ans;
}

int main(void)
{
    uint64_t ans = 0;
    std::string data = "";
    uint64_t cur = 0;
    bool flag = false;

    while (std::cin >> data)
    {
        std::string year_str, month_str, day_str;
        std::stringstream input(data);
        std::getline(input, year_str, '-');
        std::getline(input, month_str, '-');
        std::getline(input, day_str, '-');

        int year, month, day;
        year = stoi(year_str);
        month = stoi(month_str);
        day = stoi(day_str);

        if (!flag)
        {
            cur = get_day(year, month, day);
            flag = true;
        }
        else
        {
            uint64_t check = get_day(year, month, day);
            ans += abs(cur - check);
            cur = check;
        }
    }
    std::cout << ans << std::endl;
}