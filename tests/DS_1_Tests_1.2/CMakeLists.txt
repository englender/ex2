cmake_minimum_required(VERSION 3.10)
project(untitled)

#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
add_executable(untitled main.cpp tests.cpp)