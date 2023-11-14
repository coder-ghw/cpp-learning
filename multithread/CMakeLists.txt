cmake_minimum_required(VERSION 3.15)
project(cpp-multithread)

add_executable(multithread multithread.cpp)
target_link_libraries(multithread pthread)
