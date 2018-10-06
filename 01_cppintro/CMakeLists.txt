cmake_minimum_required(VERSION 3.2)
project(roman2dec)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(roman2dec roman2dec.cpp)