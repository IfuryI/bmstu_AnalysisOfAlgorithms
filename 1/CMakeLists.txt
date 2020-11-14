cmake_minimum_required(VERSION 3.15)
project(AA)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(AA
        main.cpp
        src/util.cpp
        src/util.h)
