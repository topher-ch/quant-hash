#pragma once
#include <array>
#include <cstdint>
#include <iostream>
#include <bit>

namespace permutation {

using State = std::array<uint32_t, 9>;

constexpr int idx(int x, int y) { return x + 3*y; }

void print_state(const State& s);

void theta(State& s);
void rho(State& s);
void pi(State& s);
void chi(State& s);
void iota(State& s);

void permute(State& s);

} // namespace permutation