cmake_minimum_required(VERSION 3.22)
project(a6)

set(CMAKE_CXX_STANDARD 14 -pthread -Wall -Wextra)

find_package(Boost 1.74.0 COMPONENTS system REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(t1 t1/chess.cpp t1/chessboard.hpp t1/chessboardprint.hpp)

add_executable(t2 t2/main.cpp)
target_link_libraries(t2 ${Boost_LIBRARIES})
