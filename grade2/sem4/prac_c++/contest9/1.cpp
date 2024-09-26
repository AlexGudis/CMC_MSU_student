#include <iostream>

int main(void)
{

    std::string data;

    while (std::cin >> data)
    {
        bool check_change = false;
        bool check = true;

        for (auto &el : data)
        {
            if ((check_change && (el == '3' || el == '4')) || (el != '3' && el != '4' && el != '2' && el != '1'))
            {
                std::cout << 0 << std::endl;
                check = false;
                break;
            }

            if (el == '1' || el == '2')
            {
                check_change = true;
            }
        }
        if (check)
        {
            std::cout << 1 << std::endl;
        }
    }
    return 0;
}