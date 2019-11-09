cmake_minimum_required(VERSION 3.10)
project(chain_of_responsibility)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-W -Wall -Wfatal-errors)

add_executable(chain_of_responsibility chain_of_responsibility.cpp)