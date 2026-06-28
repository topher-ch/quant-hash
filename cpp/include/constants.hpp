#pragma once
#include <array>
#include <cstdint>
#include <bitset>

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

constexpr int NUM_ROUNDS = 8;

constexpr bool iota_rcbit(int t) {
    if (t % 255 == 0) return 1;
    uint16_t R = 0b1;
    for (int i = 1; i <= t % 255; i++) {
        bool b = (R >> 8) & 1;
        R <<= 1;
        R &= 0x1ff;
        if (b) {
            R ^= (1 << 0);
            R ^= (1 << 4);
            R ^= (1 << 5);
            R ^= (1 << 6);
        }
    }
    return R & 1;
}

constexpr std::array<uint32_t, NUM_ROUNDS> iota_RC() {
    std::array<uint32_t, NUM_ROUNDS> rcs{};
    for (int i = 0; i < NUM_ROUNDS; i++) {
        uint32_t rc = 0;
        for (int j = 0; j <= 5; j++ ) {
            rc |= (uint32_t)iota_rcbit(j + 7*i) << ((1 << j) - 1);
        }
        rcs[i] = rc;
    }
    return rcs;
}

constexpr auto RC = iota_RC();

} // namespae constants