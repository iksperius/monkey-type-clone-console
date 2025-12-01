cmake_minimum_required(VERSION 4.0)
project(ncurses)

set(CMAKE_CXX_STANDARD 26)

add_executable(ncurses main.cpp
        functions.cpp
        functions.h)

set(CMAKE_CXX_FLAGS "-lncurses")
