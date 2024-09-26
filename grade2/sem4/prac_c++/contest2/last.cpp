#include <iostream>
using std::cout;

class Matrix
{
    int matr_[3][3];

  public:
    Matrix(int p = 0)
    {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                matr_[i][j] = p;
            }
        }
    }

    Matrix
    operator[](int idx)
    {
        return matr_[idx][idx];
    }
};

int
main()
{
    Matrix m;
    m[1, 1] = 5;

    for (const auto &row : m) {
        for (auto cell : row) {
            cout << cell << " ";
        }
        cout << "\n";
    }
}
