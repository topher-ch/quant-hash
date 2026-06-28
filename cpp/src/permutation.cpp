#include "permutation.hpp"
#include "constants.hpp"

namespace permutation {

void print_state(const State& s) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++)
            std::cout << std::hex << std::setfill('0') << std::setw(8) << s[idx(x, y)] << " ";
        std::cout << "\n";
    }
    std::cout << "\n";
}

void theta(State& s) {
    // std::cout << "theta (before):\n";
    // print_state(s);
    std::array<uint32_t, 3> C{};
    for (int x = 0; x < 3; x++) {
        C[x] = s[idx(x,0)] ^ s[idx(x,1)] ^ s[idx(x,2)];
    }
    // std::cout << std::hex << "C\n" << C[0] << " " << C[1] << " " << C[2] << "\n\n";
    std::array<uint32_t, 3> D{};
    for (int x = 0; x < 3; x++) {
        D[x] = C[(x-1 + 3) % 3] ^ std::rotr(C[(x+1) % 3], 1);
    }
    // std::cout << std::hex << "D\n" << D[0] << " " << D[1] << " " << D[2] << "\n\n";
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            s[idx(x,y)] = s[idx(x,y)] ^ D[x];
        }
    }
    // std::cout << "theta (after):\n";
    // print_state(s);
}

void pi(State& s) {
    // std::cout << "pi (before):\n";
    // print_state(s);
    State tmp{};
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            int X = y, Y = (x + y) % 3;
            tmp[idx(X,Y)] = s[idx(x,y)];
        }
    }
    s = tmp;
    // std::cout << "pi (after):\n";
    // print_state(s);
}

void rho(State& s) {
    // std::cout << "rho (before):\n";
    // print_state(s);
    for (int i = 0; i < 9; i++) {
        s[i] = std::rotl(s[i], ROT[i]);
    }
    // std::cout << "rho (after):\n";
    // print_state(s);
}

void chi(State& s) {
    // std::cout << "chi (before):\n";
    // print_state(s);
    State tmp{};
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            tmp[idx(x,y)] = s[idx(x,y)] ^ (~s[idx((x+1)%3,y)] & s[idx((x+2)%3,y)]);
        }
    }
    s = tmp;
    // std::cout << "chi (after):\n";
    // print_state(s);
}

void iota(State& s, int round) {
    // std::cout << "iota (before):\n";
    // print_state(s);
    s[idx(0,0)] ^= RC[round];
    // std::cout << "iota (after):\n";
    // print_state(s);
}

void permute(State& s) {
    std::cout << "permute (before):\n";
    print_state(s);
    for (int i = 0; i < NUM_ROUNDS; i++) {
        theta(s);
        pi(s);
        rho(s);
        chi(s);
        iota(s, i);
    }
    std::cout << "permute (after):\n";
    print_state(s);
}

} // namespace permutation