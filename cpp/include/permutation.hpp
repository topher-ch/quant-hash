#pragma once
#include <array>
#include <cstdint>

namespace permutation {

struct State {
    std::array<uint32_t, 9> lanes{};
};

void theta(State& s);
void rho(State& s);
void pi(State& s);
void chi(State& s);
void iota(State& s);

void permute(State& s);

} // namespace permutation