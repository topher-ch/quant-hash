#include "permutation.hpp"
#ifdef ENABLE_DOCTEST
#include <doctest.h>
#endif

namespace permutation {

void permute(State& s) {}

} // namespace permutation

namespace permutation::internal {

int bit_index(int x, int y, int z) {
    return 4*(4*y + x) + z;
}

uint64_t theta_C(State& s) {
    uint64_t C = 0;
    for (int x = 0; x < 4; x++) {
        for (int z = 0; z < 4; z++) {
            uint64_t running_xor = (s.bits >> bit_index(x, 0, z)) & 1;
            for (int y = 1; y < 4; y++) {
                running_xor ^= (s.bits >> bit_index(x, y, z)) & 1;
            }
            C |= running_xor << (4*x + z);
        }
    }
    return C;
}
#ifdef ENABLE_DOCTEST
TEST_CASE("Theta_C") {
    SUBCASE("0") {
        State s{0x0000000000000000};
        CHECK(theta_C(s) == 0);
    }
    SUBCASE("1") {
        State s{0xFFFFFFFFFFFFFFFF};
        CHECK(theta_C(s) == 0);
    }
    SUBCASE("Rand") {
        State s{0x0AA1FFA6E8956479};
        CHECK(theta_C(s) == 0x79EB);    
    }
}
#endif

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
#ifdef ENABLE_DOCTEST
TEST_CASE("Theta_D") {
    SUBCASE("0") {
        CHECK(theta_D(0x0000) == 0);
    }
    SUBCASE("1") {
        CHECK(theta_D(0xFFFF) == 0);
    }
    SUBCASE("Rand") {
        CHECK(theta_D(0x79EB) == 0xE08A);
    }
}
#endif

void theta(State& s) {
    uint64_t C = theta_C(s);
    uint64_t D = theta_D(C);
    uint64_t s_new = 0;
    for (int x = 0; x < 4; x++) {
        for (int z = 0; z < 4; z++) {
            uint64_t d = (D >> (4*x + z)) & 1;
            for (int y = 0; y < 4; y++) {
                s_new |= (((s.bits >> bit_index(x, y, z)) & 1) ^ d) << bit_index(x, y, z);
            }
        }
    }
    s.bits = s_new;
}
#ifdef ENABLE_DOCTEST
TEST_CASE("Theta") {
    SUBCASE("Theta_0") {
        State s{0x0000000000000000};
        theta(s);
        CHECK(s.bits == 0);
    }
    SUBCASE("Theta_1") {
        State s{0xFFFFFFFFFFFFFFFF};
        theta(s);
        CHECK(s.bits == 0xFFFFFFFFFFFFFFFF);
    }
    SUBCASE("Theta_Rand") {
        State s{0x0AA1FFA6E8956479};
        theta(s);
        CHECK(s.bits == 0xEA2B1F2C081F84F3);
    }
}
#endif

void rho(State& s) {}
void pi(State& s) {}
void chi(State& s) {}
void iota(State& s) {}

} // namespace permutation::internal