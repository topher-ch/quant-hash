#pragma once
#include <cstdint>

namespace permutation {

struct State {
    std::uint64_t bits = 0;
};

void permute(State& s);

} // namespace permutation