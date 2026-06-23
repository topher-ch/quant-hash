#include "hash.hpp"
#include "permutation.hpp"
#include <array>
#include <cstring>

namespace hash::internal {

const size_t kRate = 6;
permutation::State state;
std::array<uint8_t, kRate> buffer;
size_t buffer_len = 0;

void init() {
    permutation::State s{0x0000000000000000};
    state = s;
    buffer_len = 0;
}

void absorb_block() {
    uint64_t buffer_bits = 0;
    for (size_t i = 0; i < buffer_len; i++) {
        buffer_bits <<= 8;
        buffer_bits |= buffer[i];
    }
    buffer_bits <<= 16; 
    state.bits ^= buffer_bits;
    permutation::permute(state);
    buffer_len = 0;
}

void absorb(const uint8_t* data, size_t len) {
    while (len > 0) {
        size_t to_copy = std::min(kRate - buffer_len, len);
        memcpy(buffer.data() + buffer_len, data, to_copy);
        buffer_len += to_copy;
        data += to_copy;
        len -= to_copy;

        if (buffer_len == kRate) {
            absorb_block();
        }
    }
}

void absorb_pad() {
    // TODO: change padding to 10*1 instead of length_to_append*
    uint8_t pad_byte = kRate - buffer_len;
    for (size_t i = 0; i < pad_byte; i++) {
        buffer[buffer_len] = pad_byte;
        buffer_len++;
    }
    absorb_block();
}

uint64_t squeeze() { return (state.bits >> 16); }

} // namespace hash::internal

namespace hash {

uint64_t out_32(const uint8_t* data, size_t len) {
    internal::init();
    internal::absorb(data, len);
    internal::absorb_pad();
    uint64_t digest_48 = internal::squeeze();
    return (digest_48 >> 16);
}

uint64_t out_8(const uint8_t* data, size_t len) { return out_32(data, len) >> 24; }
uint64_t out_12(const uint8_t* data, size_t len) { return out_32(data, len) >> 20; }
uint64_t out_16(const uint8_t* data, size_t len) { return out_32(data, len) >> 16; }

} // namespace hash