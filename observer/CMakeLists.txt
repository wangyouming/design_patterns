cmake_minimum_required(VERSION 3.10)
project(observer)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-W -Wall -Wfatal-errors)

add_executable(observer_0 observer_0.cpp)
add_executable(observer_1 observer_1.cpp)