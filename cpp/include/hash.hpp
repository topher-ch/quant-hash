#pragma once
#include "permutation.hpp"
#include <array>
#include <cstdint>
#include <vector>
#include <span>

using Digest64 = std::array<uint8_t, 8>;
using Digest32 = std::array<uint8_t, 4>;
using Digest16 = std::array<uint8_t, 2>;
using Digest12 = std::array<uint8_t, 2>;
using Digest8  = std::array<uint8_t, 1>;

namespace hash {

std::vector<uint32_t> pad(std::span<const uint8_t> input);
void absorb(permutation::State& s, std::vector<uint32_t> input);
void squeeze_64(permutation::State& s);

Digest64 out_64(std::span<const uint8_t> input);
Digest32 out_32(std::span<const uint8_t> input);
Digest16 out_16(std::span<const uint8_t> input);
Digest12 out_12(std::span<const uint8_t> input);
Digest8 out_8(std::span<const uint8_t> input);

} // namespace hash