#include <iostream>

int
main(void)
{
    char before = 'p', now = 'p';
    while (std::cin >> now) {
        if (before == '0' && (now < '0' || now > '9')) {
            std::cout << before;
        }
        if (now != '0') {
            std::cout << now;
        }
        before = now;
    }
    if (now == '0') {
        std::cout << now;
    }
    return 0;
}
