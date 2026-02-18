#include "hash.hpp"
#ifdef ENABLE_DOCTEST
#include <doctest.h>
#include <array>
#endif

namespace hash::internal {

int kRate = 48;
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

void 8out() {}
void 12out() {}
void 16out() {}
void 32out() {}
void 64out() {}

} // namespace hash