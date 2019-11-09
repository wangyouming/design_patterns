cmake_minimum_required(VERSION 3.10)
project(factory_method)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-W -Wall -Wfatal-errors)

add_executable(factory_method factory_method.cpp)
add_executable(simple_factory simple_factory.cpp)