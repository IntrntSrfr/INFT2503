cmake_minimum_required(VERSION 3.22)
project(a7)

set(CMAKE_CXX_STANDARD 14 -pthread -Wall -Wextra)

add_executable(t1 t1/main.cpp t1/fraction.hpp t1/fraction.cpp)
add_executable(t2 t2/main.cpp t2/set.hpp t2/set.cpp)
