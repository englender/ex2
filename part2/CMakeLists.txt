cmake_minimum_required(VERSION 3.9)
project(untitled)

#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
add_executable(untitled main.cpp tests.cpp
        ImageTagger.cpp
        ImageTagger.h
        library2.cpp
        library2.h
        main.cpp
        #        map_tree.cpp
        map_tree.h
        #        node_list.cpp
        node_list.h)