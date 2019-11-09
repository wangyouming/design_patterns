cmake_minimum_required(VERSION 3.10)
project(facade)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-W -Wall -Wfatal-errors)

add_executable(facade facade.cpp)