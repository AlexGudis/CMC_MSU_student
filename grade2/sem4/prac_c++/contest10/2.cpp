#include <iostream>
#include <map>
#include <string>

int main(void)
{
    std::string data;
    std::map<std::string, bool> str;
    while (std::cin >> data)
    {
        if (data[0] == 'S')
        {
            str[data] = true;
        }
        else
        {
            str[data] = false;
        }
    }

    for (auto &el : str)
    {
        std::cout << el.first << " " << el.second << std::endl;
    }

    return 0;
}