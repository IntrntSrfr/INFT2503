cmake_minimum_required(VERSION 3.22)
project(a5)

set(CMAKE_CXX_STANDARD 14 -Wall -Wextra)

add_executable(chess chess.cpp chessboard.hpp)