cmake_minimum_required(VERSION 3.16)
project(quant_hash)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(quant_hash_lib
    src/permutation.cpp
)

target_include_directories(quant_hash_lib PUBLIC include)
add_executable(quant_hash src/main.cpp)
target_link_libraries(quant_hash PRIVATE quant_hash_lib)