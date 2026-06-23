#include "permutation.hpp"

namespace permutation::internal {

uint64_t theta_C(State& s) {
    uint64_t C = 0;
    for (int x = 0; x < 4; x++) {
        for (int z = 0; z < 4; z++) {
            uint64_t running_xor = (s.bits >> (4*x + z)) & 1;
            for (int y = 1; y < 4; y++) {
                running_xor ^= (s.bits >> (4*(4*y + x) + z)) & 1;
            }
            C |= running_xor << (4*x + z);
        }
    }
    return C;
}

uint64_t theta_D(uint64_t C) {
    uint64_t D = 0;
    for (int x = 0; x < 4; x++) {
        for (int z = 0; z < 4; z++) {
            int x1 = (x + 3) & 3;
            int z1 = z;
            int x2 = (x + 1) & 3;
            int z2 = (z + 3) & 3;
            uint64_t d = ((C >> (4*x1 + z1)) & 1) ^ ((C >> (4*x2 + z2)) & 1);
            D |= d << (4*x + z);
        }
    }
    return D;
}

void theta(State& s) {
    uint64_t C = theta_C(s);
    uint64_t D = theta_D(C);
    uint64_t s_new = 0;
    for (int x = 0; x < 4; x++) {
        for (int z = 0; z < 4; z++) {
            uint64_t d = (D >> (4*x + z)) & 1;
            for (int y = 0; y < 4; y++) {
                s_new |= (((s.bits >> (4*(4*y + x) + z)) & 1) ^ d) << (4*(4*y + x) + z);
            }
        }
    }
    s.bits = s_new;
}

/*[ 0 1 3 2 
    2 3 1 0
    3 0 2 1 
    1 2 0 3 ] */
constexpr uint64_t kRhoOffsets = 0x1EB4C963;

void rho(State& s) {
    uint64_t s_new = 0;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            uint64_t rotation = (kRhoOffsets >> 2*(4*y + x)) & 0b11;
            uint64_t lane = (s.bits >> 4*(4*y + x)) & 0b1111;
            uint64_t lane_rotated = ((lane << rotation) & 0b1111) ^ ((lane >> (4 - rotation)) & 0b1111);
            s_new |= lane_rotated << 4*(4*y + x);
        }
    }
    s.bits = s_new;
}

void pi(State& s) {
    uint64_t s_new = 0;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            int x_old = (x + 3*y) % 4;
            int y_old = x;
            uint64_t lane = (s.bits >> 4*(4*y_old + x_old)) & 0b1111;
            s_new |= lane << 4*(4*y + x);
        }
    }
    s.bits = s_new;
}

void chi(State& s) {
    uint64_t s_new = 0;
    for (int y = 0; y < 4; y++) {
        uint64_t lane1 = (s.bits >> 4*(4*y)) & 0b1111;
        uint64_t lane2 = (s.bits >> 4*(4*y + 1)) & 0b1111;
        for (int x = 0; x < 4; x++) {
            uint64_t lane3 = (s.bits >> 4*(4*y + ((x + 2) % 4))) & 0b1111;
            uint64_t lane_new = lane1 ^ ((lane2 ^ 0b1111) & lane3);
            s_new |= lane_new << 4*(4*y + x);
            lane1 = lane2;
            lane2 = lane3;
        }
    }
    s.bits = s_new;
}

// [ 1001 1011 1010 0011 1000 0010 0001 ]
constexpr uint64_t kIotaRoundConstants = 0x9BA3821;

void iota(State& s, int round) {
    uint64_t lane = s.bits & 0b1111;
    uint64_t rc = (kIotaRoundConstants >> (4*round)) & 0b1111;
    uint64_t s_new = ((s.bits >> 4) << 4) | (lane ^ rc);
    s.bits = s_new;
}

} // namespace permutation::internal

namespace permutation {

void permute(State& s) {
    for (int i = 0; i < 7; i++) {
        internal::theta(s);
        internal::rho(s);
        internal::pi(s);
        internal::chi(s);
        internal::iota(s, i);
    }
}

} // namespace permutation