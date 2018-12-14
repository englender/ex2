cmake_minimum_required(VERSION 3.9)
project(ex2_part2_github)

set(CMAKE_CXX_STANDARD 11)

add_executable(ex2_part2_github
        ImageTagger.cpp
        ImageTagger.h
        library2.cpp
        library2.h
        main.cpp
        map_tree.h
        node_list.h)
