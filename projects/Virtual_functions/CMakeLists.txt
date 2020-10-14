cmake_minimum_required(VERSION 2.6)
project(virtual_functions)

add_executable(virtual_functions main.cpp)

install(TARGETS virtual_functions RUNTIME DESTINATION bin)
