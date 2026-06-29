#include "hash.hpp"
#include "constants.hpp"

namespace hash {

std::vector<uint32_t> pad(std::span<const uint8_t> input) {
    std::vector<uint32_t> padded(input.begin(), input.end());
    padded.push_back(0x01);
    while (padded.size() % (4*r_lanes) != 0) {
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
    
} // namespace hash