cmake_minimum_required(VERSION 3.10)
project(abstract_factory)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-W -Wall -Wfatal-errors)

add_executable(abstract_factory abstract_factory.cpp)