#include <iostream>
#include <sstream>

int main(void)
{
    std::string data;
    while (std::cin >> data)
    {
        bool ans = true;
        long zero_cnt = 0, one_cnt = 0;
        std::stringstream s(data);
        char x;
        s >> x;
        long i = 0, len = data.size();
        ++i;
        while (x == '0' && i <= len)
        {
            s >> x;
            ++zero_cnt;
            ++i;
        }

        while (x == '1' && i <= len)
        {
            s >> x;
            ++one_cnt;
            ++i;
        }

        if (!(zero_cnt > 0 && one_cnt > 0))
        {
            ans = false;
        }

        long now_zero = 0;
        long now_one = 0;
        bool check_zero = true;
        bool check_one = false;
        // std::cout << "One_cnt: " << one_cnt << std::endl;
        // std::cout << "Zero_cnt: " << zero_cnt << std::endl;

        for (auto &el : data)
        {
            if (el != '0' && el != '1')
            {
                ans = false;
                break;
            }

            if (check_one && el == '1')
            {
                now_one++;
            }

            if (check_zero && el == '0')
            {
                now_zero++;
            }
            if (check_zero && el == '1')
            {
                check_zero = false;
                check_one = true;
                now_one = 1;
                if (now_zero != zero_cnt)
                {
                    ans = false;
                    // std::cout << "Crash zero" << std::endl;
                    break;
                }
                else
                {
                    now_zero = 0;
                }
            }

            if (check_one && el == '0')
            {
                check_zero = true;
                check_one = false;
                now_zero = 1;
                if (now_one != one_cnt)
                {
                    ans = false;
                    // std::cout << "Crash one" << std::endl;
                    break;
                }
                else
                {
                    now_one = 0;
                }
            }
        }

        if (ans)
        {
            if (check_one && now_one == one_cnt)
            {
                std::cout << 1 << std::endl;
            }
            else
                ans = false;
        }
        if (!ans)
        {
            std::cout << 0 << std::endl;
        }
    }
    return 0;
}