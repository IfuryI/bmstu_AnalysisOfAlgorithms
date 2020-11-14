cmake_minimum_required(VERSION 3.15)
project(2)

set(CMAKE_CXX_STANDARD 17)

add_executable(2 main.cpp src/util.cpp src/util.h src/matrix_multiplication.cpp src/matrix_multiplication.h tests/main_test.cpp tests/main_test.h)