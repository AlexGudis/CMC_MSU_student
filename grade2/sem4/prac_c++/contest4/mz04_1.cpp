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