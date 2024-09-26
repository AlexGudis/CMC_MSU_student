#include <iostream>
#include <string>

class MyStr
{
    std::string data_;

public:
    MyStr(const std::string &data = "")
    {
        data_ = data;
    }
    ~MyStr()
    {
        std::cout << data_ << std::endl;
    }
};

void Foo()
{
    std::string data = "";
    if (std::cin >> data)
    {
        MyStr str(data);
        try
        {
            Foo();
        }
        catch (int)
        {
            throw 1;
        }
    }
    else
    {
        throw 1; // no input -> go back in recursion
    }
}

int main(void)
{
    try
    {
        Foo();
    }
    catch (...) // some error
    {
    }
    return 0;
}