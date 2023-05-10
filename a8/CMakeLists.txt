cmake_minimum_required(VERSION 3.22)
project(a8)

set(CMAKE_CXX_STANDARD 14 -pthread -Wall -Wextra)

add_executable(t1 t1/main.cpp)
add_executable(t2 t2/main.cpp t2/pair.hpp)
