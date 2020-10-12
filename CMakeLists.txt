cmake_minimum_required(VERSION 2.6)
project(classes)

add_executable(classes main.cpp)

install(TARGETS classes RUNTIME DESTINATION bin)
