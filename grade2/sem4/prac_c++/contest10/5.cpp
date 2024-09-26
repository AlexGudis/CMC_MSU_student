#include <iostream>
#include <string>
#include <stack>

bool check(char symb)
{
    if ((symb >= 'a' && symb <= 'z') || (symb >= 'A' && symb <= 'Z'))
    {
        return true;
    }
    return false;
}

std::string convert(std::string &poliz)
{
    std::stack<std::string> stack;
    std::string ans = "";

    for (auto &el : poliz)
    {
        if (check(el))
        {
            std::string symb(1, el);
            stack.push(symb);
        }
        else
        {
            std::string right = stack.top();
            stack.pop();
            std::string left = stack.top();
            stack.pop();
            ans = "(" + left + el + right + ")";
            stack.push(ans);
        }
    }

    return stack.top();
}

int main(void)
{
    std::string poliz;
    std::cin >> poliz;
    std::cout << convert(poliz) << std::endl;
    return 0;
}