#include <iostream>
#include "permutation.hpp"

int main() {
    quant_hash::Permutation perm;

    perm.setState();
    perm.apply();
    perm.getState();

    std::cout << "Compiled successfully\n";
    return 0;
}