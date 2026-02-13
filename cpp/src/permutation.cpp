#include "permutation.hpp"
#ifdef ENABLE_DOCTEST
#include <doctest.h>
#endif

namespace permutation {

void permute(State& s) {}

} // namespace permutation

namespace permutation::internal {

void theta(State& s) {}
void rho(State& s) {}
void pi(State& s) {}
void chi(State& s) {}
void iota(State& s) {}

#ifdef ENABLE_DOCTEST
TEST_CASE("Simple zero equals zero") {
    CHECK(0 == 0);
}
#endif

} // namespace permutation::internal