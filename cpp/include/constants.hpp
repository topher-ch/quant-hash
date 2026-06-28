#pragma once
#include <array>
#include <cstdint>

namespace permutation {

constexpr int idx(int x, int y) { return x + 3*y; }

constexpr std::array<int, 9> rho_ROT() {
    std::array<int, 9> rot{};
    int x = 1, y = 0;
    for (int t = 0; t < 8; t++) {
        rot[idx(x,y)] = ((t+1)*(t+2)/2) % 32;
        int X = y, Y = (x + y) % 3;
        x = X; y = Y;
    }
    return rot;
}

constexpr auto ROT = rho_ROT();

} // namespae constants