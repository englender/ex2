cmake_minimum_required(VERSION 3.9)
project(part1_tree)

set(CMAKE_CXX_STANDARD 11)

add_executable(part1_tree
               library1.h
               main.cpp
               map_tree.h
               library1_TREE.cpp)
