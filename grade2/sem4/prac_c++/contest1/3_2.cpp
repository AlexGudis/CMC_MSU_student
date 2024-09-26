#include <iostream>

int
main(void)
{
    char before = 'p', now = 'p';
    std::string ans = "";
    int mode = 0; // 0 - out of digit, 1 - in digit
    while (std::cin.get(now)) {
        if (before == '0' && (now < '0' || now > '9')) { // after a digit
            ans += before;
        }
        
        if (now > '9' || now < '0') { // not a digit
            ans += now;
        }

        before = now;

        if (now >= '1' && now <= '9') {
            mode = 1;
        }
        else if (now < '0' || now > '9'){
            mode = 0;
        }

        if (mode && (now >= '0' && now <= '9')) { // in digit
            ans += now;
            before = '$'; // only about digits, doesn't matter what char is there
        }
    }
    if (before == '0') {
        ans += before;
    }
    std::cout << ans;
    return 0;
}
