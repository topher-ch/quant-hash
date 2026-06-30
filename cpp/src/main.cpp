#include "hash.hpp"
#include "permutation.hpp"
#include <iostream>
#include <iomanip>

int main() {
    std::array<uint8_t, 100> input{};
    for (int i = 0; i < 100; i++) {
        input[i] = 0x00 + i;
    }
    std::vector<uint32_t> padded = hash::pad(input);
    std::cout << "input (padded):\n";
    for (int i = 0; i < padded.size(); i++) {
        std::cout << std::hex << std::setfill('0') << std::setw(8) << padded[i] << " ";
    }
    std::cout << "\n\n";

    hash::Digest64 d64 = hash::out_64(input);
    hash::Digest32 d32 = hash::out_32(input);
    hash::Digest16 d16 = hash::out_16(input);
    hash::Digest8 d8 = hash::out_8(input);
    return 0;
}