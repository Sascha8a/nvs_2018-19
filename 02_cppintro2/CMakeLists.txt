cmake_minimum_required(VERSION 3.2)
project(primes)

find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_executable(primes primes.cpp)
target_link_libraries(primes "${CMAKE_THREAD_LIBS_INIT}")