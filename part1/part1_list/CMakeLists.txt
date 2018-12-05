cmake_minimum_required(VERSION 3.9)
project(part1_list)

set(CMAKE_CXX_STANDARD 11)

add_executable(part1_list main.cpp
               library1_LIST.cpp
               library1.h
               node_list.h)