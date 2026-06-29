#pragma once
#include <array>
#include <cstdint>

namespace permutation {

using State = std::array<uint32_t, 9>;

void print_state(const State& s);

void theta(State& s);
void pi(State& s);
void rho(State& s);
void chi(State& s);
void iota(State& s, int round);

void permute(State& s);

} // namespace permutation