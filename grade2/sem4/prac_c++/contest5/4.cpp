#include <iostream>
#include <vector>
#include <algorithm>

class Matrix
{
public:
    unsigned long row_, column_, val_;

    Matrix(unsigned long row = 0, unsigned long column = 0, unsigned long val = 0)
    {
        row_ = row;
        column_ = column;
        val_ = val;
    }
};

bool cmp(const Matrix cl1, const Matrix cl2)
{
    if (cl1.row_ < cl2.row_)
    {
        return true;
    }
    else if (cl1.row_ == cl2.row_ && cl1.column_ < cl2.column_)
    {
        return true;
    }
    return false;
}

int main(void)
{
    std::vector<Matrix> cells_1;
    std::vector<Matrix> cells_2;
    std::vector<Matrix> cells_ans;
    int devide_cnt = 0;
    unsigned long row, column, value;
    while (std::cin >> row >> column >> value)
    {
        if (row == 0 && column == 0 && value == 4294967161)
        {
            devide_cnt++;
            continue; // next matrix
        }
        Matrix cell(row, column, value % 4294967161);
        if (devide_cnt == 0)
        {
            cells_1.emplace_back(cell);
        }
        else
        {
            cells_2.emplace_back(cell);
        }
    }

    for (auto it_1 = cells_1.begin(); it_1 < cells_1.end(); ++it_1)
    {
        int flag = 0; // if this cell exists in second matrix
        for (auto it_2 = cells_2.begin(); it_2 < cells_2.end(); ++it_2)
        {
            if ((*it_1).row_ == (*it_2).row_ && (*it_1).column_ == (*it_2).column_)
            {
                // std::cout << "CHECK_DATA" << std::endl;
                // std::cout << (*it_1).row_ << (*it_2).row_ << (*it_1).column_ << (*it_2).column_ << std::endl;
                flag = 1; // cell from matr_1 exists in matr_2
                // std::cout << "VALUE2: " << (*it_2).val_ << std::endl;
                Matrix cell((*it_1).row_, (*it_1).column_, ((*it_1).val_ + (*it_2).val_) % 4294967161);
                // std::cout << cell.val_ << std::endl;
                cells_ans.emplace_back(cell);
                cells_2.erase(it_2);
                it_2 = cells_2.end(); // del this cell and exit the loop
            }
        }
        if (!flag)
        {
            cells_ans.emplace_back((*it_1)); // 0 + this cell = this cell
        }
    }

    for (auto &cl2 : cells_2)
    {
        cells_ans.emplace_back(cl2); // add remaining cells from second matrix
    }

    std::sort(cells_ans.begin(), cells_ans.end(), cmp);
    for (auto &cl : cells_ans)
    {
        if (cl.val_)
        {
            std::cout << cl.row_ << " " << cl.column_ << " " << cl.val_ << std::endl;
        }
    }
    return 0;
}