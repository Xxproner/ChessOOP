cmake_minimum_required(VERSION 3.23)
project(chess)

set(CMAKE_CXX_STANDARD 11)

add_executable(chess main.cpp pieces.h pieces.cpp desk.h desk.cpp)
