//
// Created by Yaroslav on 10.04.2023.
//
#include <iostream>

using namespace std;

class S
{
    int32_t val{};
    bool correct;

public:
    S()
    {

        correct = bool(cin >> val);
        //        cout << val << " " << correct <<  endl;
    }
    S(S &&other) noexcept
    {
        int32_t v;
        cin >> v;
        val = other.val + v;
        correct = 1;
        other.correct = 0;
    }
    explicit operator bool() const
    {
        return bool(cin);
    }
    ~S()
    {
        std::cout << "Destructor working..." << std::endl;

        if (correct)
        {
            cout << val << endl;
        }
    }
};

using namespace std;
void func(S v)
{
    if (v)
    {
        func(move(v));
    }
}

int main(void)
{
    func(S());
}