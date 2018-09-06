cmake_minimum_required(VERSION 3.12)
project(stream)

set(CMAKE_CXX_STANDARD 17)

add_library(streams INTERFACE)

set(SRC_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(SRC_DIR "${SRC_ROOT}/streams")

target_include_directories(streams INTERFACE src/)

target_sources(streams INTERFACE
        "${SRC_DIR}/defines.hpp"
        "${SRC_DIR}/streams.hpp"
        "${SRC_DIR}/iterable.hpp"
        "${SRC_DIR}/map.hpp"
        "${SRC_DIR}/filter.hpp")

add_executable(hello main.cpp)

target_link_libraries(hello streams)
