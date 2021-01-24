cmake_minimum_required(VERSION 3.15)
project(ASD2_Labs_2020)

set(CMAKE_CXX_STANDARD 14)

add_executable(hashmap_main main.cpp Chaining.cpp Linear_probing.cpp TernarySearchTree.h Corrector.h)
add_subdirectory(catch2_tests)
