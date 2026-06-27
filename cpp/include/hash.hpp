#pragma once
#include <array>
#include <cstdint>

using Digest64 = std::array<uint8_t, 8>
using Digest32 = std::array<uint8_t, 4>
using Digest16 = std::array<uint8_t, 2>
using Digest12 = std::array<uint8_t, 2>
using Digest8  = std::array<uint8_t, 1>

namespace hash {

    Digest64 out_64();
    Digest32 out_32();
    Digest16 out_16();
    Digest12 out_12();
    Digest8  out_8() ;

} // namespace hash