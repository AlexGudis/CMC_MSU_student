#include <iostream>
#include <vector>
#include <cstdint>

void process(const std::vector<uint64_t> &def, std::vector<uint64_t> &change, int n)
{
    auto vi = std::rbegin(change); // to change in reverse order
    for (auto it = def.begin(); it < def.end() && vi < change.rend(); it += n)
    {
        (*vi) += (*it);
        vi++;
    }
}

int main(void)
{
    const std::vector<uint64_t> def = {1, 2, 3, 4};
    std::vector<uint64_t> change = {1, 2, 3};
    int n;
    std::cin >> n;
    process(def, change, n);

    for (auto it = change.begin(); it != change.end(); ++it)
    {
        std::cout << *it << ' ';
    }
}
