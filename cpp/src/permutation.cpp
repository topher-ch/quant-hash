#include "permutation.hpp"

namespace permutation {

void print_state(const State& s) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++)
            std::cout << std::hex << s[idx(x, y)] << " ";
        std::cout << "\n";
    }
    std::cout << "\n";
}

void theta(State& s) {
    std::cout << "theta (before):\n";
    print_state(s);
    std::array<uint32_t, 3> C{};
    for (int x = 0; x < 3; x++) {
        C[x] = s[idx(x,0)] ^ s[idx(x,1)] ^ s[idx(x,2)];
    }
    std::cout << std::hex << "C\n" << C[0] << " " << C[1] << " " << C[2] << "\n\n";
    std::array<uint32_t, 3> D{};
    for (int x = 0; x < 3; x++) {
        D[x] = C[(x-1 + 3) % 3] ^ std::rotr(C[(x+1) % 3], 1);
    }
    std::cout << std::hex << "D\n" << D[0] << " " << D[1] << " " << D[2] << "\n\n";
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            s[idx(x,y)] = s[idx(x,y)] ^ D[x];
        }
    }
    std::cout << "theta (after):\n";
    print_state(s);
}

} // namespace permutation