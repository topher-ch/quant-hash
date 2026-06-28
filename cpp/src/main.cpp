#include "hash.hpp"
#include "permutation.hpp"
#include <iostream>

int main() {
    std::array<uint32_t, 9> s{};
    for (int i = 0; i < 9; i++) {
        s[i] = 0xfffffff0 + i;
    }
    permutation::theta(s);
    permutation::pi(s);
    permutation::rho(s);
    return 0;
}