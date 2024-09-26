#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

class Student
{

    std::string name_;
    double sum_ = 0;
    unsigned long count_ = 0;

public:
    Student(std::string name = "")
    {
        name_ = name;
    }

    void add_grade(const int &x)
    {
        sum_ += x;
        count_++;
    }

    std::string get_name() const
    {
        return name_;
    }

    double get_sum() const
    {
        return sum_;
    }

    double avg() const
    {
        return sum_ / count_;
    }
};

bool cmp(const Student &st1, const Student &st2)
{
    return st1.get_name() < st2.get_name();
}

int main(void)
{
    std::vector<Student> students;
    std::string name;
    int x;
    while (std::cin >> name)
    {
        std::cin >> x; // grade
        int flag = 0;  // to check if student exists
        for (auto &el : students)
        {
            if (el.get_name() == name)
            {
                // std::cout << "CHECK" << std::endl;
                flag = 1; // student exists
                // std::cout << "sum_before = " << el.get_sum() << std::endl;
                el.add_grade(x);
                // std::cout << "sum_after = " << el.get_sum() << std::endl;
            }
        }
        if (!flag)
        { // no student with this name
            // std::cout << "New student created!" << std::endl;
            Student st(name);
            st.add_grade(x);
            students.emplace_back(st);
        }
    }

    std::sort(students.begin(), students.end(), cmp);
    for (auto &el : students)
    {
        std::cout << el.get_name() << " " << el.avg() << std::endl;
    }
    return 0;
}