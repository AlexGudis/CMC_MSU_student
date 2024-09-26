#include <iostream>
using namespace std;
char c;
// текущий символ
void gc() { cin >> c; }
// считать очередной символ из входной цепочки
bool scan_G()
{
    enum state
    {
        H,
        A,
        B,
        C,
        S,
        ER
    }; // множество состояний
    state CS;
    CS = H;
    // CS —— текущее состояние
    do
    {
        gc();
        switch (CS)
        {
        case H:
            if (c == 'a')
            {
                CS = A;
            }
            else if (c == 'b')
            {
                CS = B;
            }
            else
                CS = ER;
            break;
        case A:
            if (c == 'b')
            {
                CS = C;
            }
            else
                CS = ER;
            break;
        case B:
            if (c == 'a')
            {
                CS = C;
            }
            else
                CS = ER;
            break;
        case C:
            if (c == 'a')
            {
                CS = A;
            }
            else if (c == 'b')
            {
                CS = B;
            }
            else if (c == '')
                CS = S;
            else
                CS = ER;
            break;
        }
    } while (CS != S && CS != ER);
    return CS == S; // true, если CS != ER,
}

int main(void)
{
    if (scan_G())
    {
        std::cout << "1" << std::endl;
    }
    else
    {
        std::cout << "0" << std::endl;
    }
}