#include <iostream>
#include <string>
#include <iomanip>

void
check(char c, std::string *now, std::string *ans)
{
    int len = (*now).length();
    if (len > 4 || (*now).at(len - 1) == '#') {
        std::string s = std::string() + '#';
        s = s + (*now).at(len - 1);
        std::ostringstream ss;
        ss << std::hex << len;
        std::string result = ss.str();
        s = s + result;
        s = s + '#';
        (*ans) += s;
    } else {
        (*ans) += (*now);
    }
    (*now) = "";
}

int
main(void)
{
    std::string data_now = "";
    std::string data_ans = "";
    long len;
    char c = '$';
    while (std::cin.get(c)) {
        len = data_now.length();
        if (len > 0 && c != data_now.at(len - 1)) {
            check(c, &data_now, &data_ans);
        }
        data_now += c;
    }
    len = data_now.length();
    if (len) {
        check(c, &data_now, &data_ans);
    }
    std::cout << data_ans;
    return 0;
}
