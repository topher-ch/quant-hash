#include "hash.hpp"
#include "constants.hpp"

namespace hash {

std::vector<uint32_t> pad(std::span<const uint8_t> input) {
    std::vector<uint8_t> padded(input.begin(), input.end());
    padded.push_back(0x01);
    while (padded.size() % 16 != 0) {
        padded.push_back(0x00);
    }
    padded.back() |= 0x80;

    std::vector<uint32_t> output;
    for (int i = 0; i < padded.size(); i += 4) {
        uint32_t block = 0;
        block |= (uint32_t)padded[i];
        block |= (uint32_t)padded[i+1] << 8;
        block |= (uint32_t)padded[i+2] << 16;
        block |= (uint32_t)padded[i+3] << 24;
        output.push_back(block);
    }
    return output;
}

permutation::State absorb(std::vector<uint32_t> input) {
    permutation::State s{};
    std::span<const uint32_t> input_span{input};
    for (int i = 0; i < input.size(); i = i + 4) {
        absorb_block(s, input_span.subspan(i, 4));
    }
    return s;
}

void absorb_block(permutation::State& s, std::span<const uint32_t> block) {
    for (int i = 0; i < 4; i++) {
        s[i] ^= block[i];
    }
    permutation::permute(s);
}

static std::vector<uint8_t> squeeze_n(const permutation::State& s, size_t n) {
    std::vector<uint8_t> digest(n);
    for (size_t i = 0; i < n; i++) {
        int lane = i / 4;
        int byte_in_lane = i % 4;
        digest[i] = (s[lane] >> (8 * byte_in_lane)) & 0xff;
    }
    return digest;
}

Digest64 squeeze_64(const permutation::State& s) {
    std::array<uint8_t, 8> out{};
    auto v = squeeze_n(s, 8);
    std::copy(v.begin(), v.end(), out.begin());
    return out;
}

Digest32 squeeze_32(const permutation::State& s) {
    std::array<uint8_t, 4> out{};
    auto v = squeeze_n(s, 4);
    std::copy(v.begin(), v.end(), out.begin());
    return out;
}

Digest16 squeeze_16(const permutation::State& s) {
    std::array<uint8_t, 2> out{};
    auto v = squeeze_n(s, 2);
    std::copy(v.begin(), v.end(), out.begin());
    return out;
}

Digest8 squeeze_8(const permutation::State& s) {
    std::array<uint8_t, 1> out{};
    auto v = squeeze_n(s, 1);
    std::copy(v.begin(), v.end(), out.begin());
    return out;
}

Digest64 out_64(std::span<const uint8_t> input) {
    return squeeze_64(absorb(pad(input)));
}

Digest32 out_32(std::span<const uint8_t> input) {
    return squeeze_32(absorb(pad(input)));
}

Digest16 out_16(std::span<const uint8_t> input) {
    return squeeze_16(absorb(pad(input)));
}

Digest8 out_8(std::span<const uint8_t> input) {
    return squeeze_8(absorb(pad(input)));
}
    
} // namespace hash