#include <iostream>
using std::cout;

class Matrix
{
  public:
    class CRow
    {
        friend class Matrix;

      public:
        int &
        operator[](int col)
        {
            return parent.arr[row][col];
        }

      private:
        CRow(Matrix &parent_, int row_) : parent(parent_), row(row_) {}

        Matrix &parent;
        int row;
    };

    CRow
    operator[](int row)
    {
        return CRow(*this, row);
    }

  private:
    int rows, cols;
    int **arr;
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
