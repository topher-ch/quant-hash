#include "hash.hpp"
#include <array>
#ifdef ENABLE_DOCTEST
#include <doctest.h>
#endif

namespace hash::internal {

const int kRate = 48;
uint64_t state = 0;
std::array<uint8_t, kRate> buffer;
size_t buffer_len = 0;

void absorb(const uint8_t* data, size_t len) {}
void absorb_pad() {}
void absorb_block() {}
void squeeze() {}
uint64_t get_state() {}

} // namespace hash::internal

namespace hash {

void out_8() {}
void out_12() {}
void out_16() {}
void out_32() {}
void out_64() {}

} // namespace hash