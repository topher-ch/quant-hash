#include <iostream>
#include "permutation.hpp"

int main() {
    permutation::State s{0x0AA1FFA6E8956479};
    permutation::permute(s);
    uint64_t bits = s.bits;
    std::cout << std::hex << "permuted state: " << bits << "\n";
    return 0;
}