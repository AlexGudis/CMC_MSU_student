#include <iostream>

int
main(void)
{
    char before = 'p', now = 'p';
    while (std::cin >> now) {
        // std::cout << "Before: " << before << ";" << "Now: " << now << std::endl;
        if (before == '0' && (now < '0' || now > '9')) {
            // std::cout << "Test1" << std::endl;
            std::cout << before;
        }
        if (now != '0') {
            // std::cout << "Test2" << std::endl;
            std::cout << now;
        }
        before = now;
    }
    if (now == '0') {
        // std::cout << "Test3" << std::endl;
        std::cout << now;
    }
    return 0;
}
