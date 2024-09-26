#include <iostream>
#include <sstream>
char c; // текущий символ
std::string s;
std::stringstream ss;
void A();
void B();
void gc()
{
    ss >> c;
    // std::cout << "Check c = " << c << std::endl;
}

void S()
{
    if (c == 'a')
    {
        // std::cout << "S -> aAb" << std::endl;
        gc();
        A();
        gc();
        if (c != 'b')
            throw c;
    }
    else if (c == 'c')
    {
        // std::cout << "S -> cB" << std::endl;
        gc();
        B();
    }
    else
        throw c;
}

void A()
{
    if (c == 'c')
    {
        // std::cout << "A -> cAd" << std::endl;
        gc();
        A();
        gc();
        if (c != 'd')
            throw c;
    }
    else if (c == 'e')
        ; // std::cout << "A -> e" << std::endl;
    else
        throw c;
}
void B()
{
    if (c == 'b')
    {
        ; // std::cout << "B -> bB" << std::endl;
        gc();
        B();
    }
    else if (c == 'd')
        ; // std::cout << "B -> d" << std::endl;
    else if (isalpha(c))
        ;
    else
        throw c;
}

int main(void)
{
    try
    {
        while (std::cin >> c)
        {
            if (!isspace(c))
            {
                s.append(1, c);
            }
        }
        ss = std::stringstream(s);
        gc();
        S();
        // std::cout << std::cin.eof() << std::endl;
        if (std::cin >> c)
            throw c;
        std::cout << "1" << std::endl;
    }
    catch (char)
    {
        std::cout << "0" << std::endl;
    }
    return 0;
}
