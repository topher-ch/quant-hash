#include "hash.hpp"
#include "permutation.hpp"
#include <iostream>
#include <iomanip>
#include <random>
#include <set>
#include <unordered_map>

int main() {
    // random number generators
    // std::mt19937 gen(42);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> lens(1, 100);
    std::uniform_int_distribution<int> nums(0, 255);

    // set to keep track of inputs
    std::set<std::vector<uint8_t>> inputs;
    // std::unordered_map<uint8_t, std::vector<uint8_t>> hashes_to_inputs;
    std::unordered_map<uint16_t, std::vector<uint8_t>> hashes_to_inputs;
    while (true) {
        // generate length of random input
        int len = lens(gen);
        std::vector<uint8_t> input(len);
        // generate random input
        for (int i = 0; i < len; i++) {
            input[i] = (uint8_t)nums(gen);
        }
        // check if input has already been hashed, if so skip and re-generate
        if (inputs.contains(input)) {
            continue;
        } else {
            inputs.insert(input);
        }

        // compute hash
        // uint8_t output = hash::out_8(input)[0];
        uint16_t output;
        {
            auto digest = hash::out_16(input);
            output = (digest[0]) | (digest[1] << 8);  // pack 2 bytes into uint16_t
        }

        // print input
        std::cout << "input:  ";
        for (int i = 0; i < input.size(); i++) {
            std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)input[i] << " ";
        }
        std::cout << "\n";
        // print output
        std::cout << "output: " << (int)output << "\n\n";

        // check if output has been seen before, if so collision found,
        // otherwise add to both unordered maps and continue searching
        if (hashes_to_inputs.contains(output)) {
            std::cout << "collision detected!\n";
            // print inputs
            std::vector<uint8_t> input1 = hashes_to_inputs[output];
            std::vector<uint8_t> input2 = input;
            std::cout << "inputs: ";
            for (int i = 0; i < input1.size(); i++) {
                std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)input1[i] << " ";
            }
            std::cout << "\n        ";
            for (int i = 0; i < input2.size(); i++) {
                std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)input2[i] << " ";
            }
            std::cout << "\n";
            // print output
            std::cout << "output: " << (int)output << "\n";
            // print number of hashes required to reach collision
            std::cout << std::dec << "number: " << inputs.size() << "\n";
            break;
        } else {
            hashes_to_inputs.insert({output, input});
        }
    }
    return 0;
}