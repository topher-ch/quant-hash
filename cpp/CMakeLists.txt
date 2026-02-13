cmake_minimum_required(VERSION 3.16)
project(quant_hash)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Build the library from permutation.cpp
add_library(quant_hash_lib STATIC src/permutation.cpp)
target_include_directories(quant_hash_lib PUBLIC include)

# Build the main.cpp executable
add_executable(quant_hash src/main.cpp)
target_link_libraries(quant_hash PRIVATE quant_hash_lib)

# Build the testing executable
add_executable(quant_hash_test src/permutation.cpp)
target_include_directories(quant_hash_test PRIVATE include)
target_compile_definitions(quant_hash_test PRIVATE ENABLE_DOCTEST)