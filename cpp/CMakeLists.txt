cmake_minimum_required(VERSION 3.16)
project(quant_hash)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Build the library from permutation.cpp
add_library(quant_hash_lib STATIC 
    src/permutation.cpp
    src/hash.cpp
)
target_include_directories(quant_hash_lib PUBLIC include)

# Build the main.cpp executable
add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE quant_hash_lib)

# Build the testing executable
set(TEST_SOURCES
    tests/test_main.cpp
    tests/test_permutation.cpp
    )
add_executable(tests ${TEST_SOURCES})
target_include_directories(tests PRIVATE include)
target_compile_definitions(tests PRIVATE ENABLE_DOCTEST)