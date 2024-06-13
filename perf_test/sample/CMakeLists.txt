cmake_minimum_required(VERSION 3.15)
project(sample)

set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};D:\\projects\\minitrace\\minitrace\\share\\minitrace")
find_package(minitrace)
add_executable(sample sample.cpp)

target_link_libraries(sample minitrace::minitrace)
