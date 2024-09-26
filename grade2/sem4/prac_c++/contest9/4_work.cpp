//
// Created by Yaroslav on 17.04.2023.
//

//<A> ::= 'a' <A> | ε
//<B> ::= 'b' <B> | ε
//<C> ::= 'c' <C> | ε
//<D> ::= 'd' <D> | ε

#include <iostream>

void generateStrings(int k, const std::string &prefix)
{
    if (k == 0)
    {
        std::cout << prefix << std::endl;
        return;
    }
    if (k > 3)
    {
        generateStrings(k - 1, prefix + "a");
    }
    if (k > 2)
    {
        generateStrings(k - 1, prefix + "b");
    }
    if (k > 1)
    {
        generateStrings(k - 1, prefix + "c");
    }
    generateStrings(k - 1, prefix + "d");
}

int main()
{
    int k;
    std::cin >> k;
    generateStrings(k, "");

    return 0;
}