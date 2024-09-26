#include <iostream>
#include <list>

int main(void)
{
    std::list<long> lst;
    long x;
    while (std::cin >> x)
    {
        if (x != 0)
        {
            lst.push_back(x);
        }
        else
        {
            break;
        }
    }

    long com1, com2;
    while (std::cin >> com1)
    {
        if (com1 > 0)
        { // insert
            std::cin >> com2;
            com1--;
            if (com1 >= 0 && com1 < (long)lst.size())
            {
                std::list<long>::iterator it;
                it = lst.begin();
                std::advance(it, com1);
                lst.insert(it, com2);
            }
            else
            {
                lst.push_back(com2);
            }
        }
        else if (com1 < 0)
        { // delete
            com1 *= -1;
            com1--;
            if (com1 >= 0 && com1 < (long)lst.size())
            {
                std::list<long>::iterator it;
                it = lst.begin();
                std::advance(it, com1);
                lst.erase(it);
            }
        }
    }

    for (auto &el : lst)
    {
        std::cout << el << std::endl;
    }
    return 0;
}