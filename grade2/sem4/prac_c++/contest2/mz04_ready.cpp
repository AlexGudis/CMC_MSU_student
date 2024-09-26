#include <iostream>
#include <algorithm>
#include <string>

using std::string;
class BinaryNumber
{
    string digit;

  public:
    BinaryNumber(const string &s) { digit = s; }
    operator string() const { return digit; }
    const BinaryNumber &
    operator++()
    {
        int len = digit.length();
        string tmp;
        int add = 1;
        for (int i = len - 1; i >= 0; --i) {
            if (add && digit.at(i) == '0') {
                tmp += '1';
                add = 0;
            } else if (add && digit.at(i) == '1') {
                tmp += '0';
            } else {
                tmp += digit.at(i);
            }
        }
        if (add) {
            tmp += '1';
        }
        std::reverse(tmp.begin(), tmp.end());

        digit = tmp;
        return *this;
    }
};
