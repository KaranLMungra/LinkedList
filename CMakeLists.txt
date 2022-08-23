cmake_minimum_required(VERSION 3.23)
project(linkedlist C)

set(CMAKE_C_STANDARD 23)

add_library(linkedlist library.c)
add_executable(test main.c)

target_link_libraries(test PUBLIC linkedlist)