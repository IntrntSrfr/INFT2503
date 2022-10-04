cmake_minimum_required(VERSION 3.22)
project(a3)

set(CMAKE_CXX_STANDARD 14 -Wall -Wextra)

add_executable(circle circle/client.cpp circle/circle.hpp)
add_executable(commodity commodity/client.cpp commodity/commodity.hpp)
add_executable(str str/main.cpp)