#include <iostream>

class S
{
    long sum_ = 0;
    bool to_print_ = false; // ready for print (go to destructor)
    bool got_smth_ = false; // should destructor print smth?

public:
    S()
    {
        int data;
        if (std::cin >> data)
        {
            got_smth_ = true;
            sum_ += data;
        }
        else
        {
            to_print_ = true;
        }
    }

    S(S &&before)
    {
        long data;
        sum_ = before.sum_;
        got_smth_ = before.got_smth_;

        if (std::cin >> data)
        {
            // std::cout << "GOT data = " << data << std::endl;
            sum_ += data;
        }
        else
        {
            to_print_ = true;
        }
        // std::cout << "Data now = " << sum_ << std::endl;
    }

    operator bool()
    {
        return !to_print_;
    }

    ~S()
    {
        // std::cout << "Destructor working..." << std::endl;
        if (to_print_ && got_smth_)
        {
            std::cout << sum_ << std::endl;
        }
    }
};