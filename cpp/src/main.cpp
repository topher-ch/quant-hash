#include "hash.hpp"
#include "permutation.hpp"
#include <iostream>
#include <iomanip>

int main() {
    std::array<uint8_t, 9> input{};
    for (int i = 0; i < 9; i++) {
        input[i] = 0xf0 + i;
    }
    std::vector<uint32_t> padded = hash::pad(input);
    std::cout << "input (padded):\n";
    for (int i = 0; i < padded.size(); i++) {
        std::cout << std::hex << std::setfill('0') << std::setw(8) << padded[i] << " ";
    }
    std::cout << "\n\n";

    std::array<uint32_t, 9> s{};
    for (int i = 0; i < 9; i++) {
        s[i] = 0xfffffff0 + i;
    }
    permutation::permute(s);
    return 0;
}