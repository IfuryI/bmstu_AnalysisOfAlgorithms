cmake_minimum_required(VERSION 3.15)
project(3)

set(CMAKE_CXX_STANDARD 17)


include_directories(../src)


add_executable(3 main.cpp src/main_test.cpp src/sort_algorithms.cpp src/sort_algorithms.h
        src/main_test.h)

target_link_libraries(3 PRIVATE)