#include <iostream>
#include <regex>
#include <string>

int main() {
    std::regex pattern("^([34]*)([12]*)$");

    std::string input;
    while (std::cin >> input) {
        if (std::regex_match(input, pattern)) {
            std::cout << "1" << std::endl;
        } else {
            std::cout << "0" << std::endl;
        }

    }

    return 0;
}