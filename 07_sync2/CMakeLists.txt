cmake_minimum_required(VERSION 3.2)

project(periods)

find_package(Threads REQUIRED)

file(GLOB_RECURSE SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

include_directories(include)

set(CMAKE_CXX_STANDARD 14)

add_executable(periods EXCLUDE_FROM_ALL ${SOURCE_FILES})

target_link_libraries(periods "${CMAKE_THREAD_LIBS_INIT}")