cmake_minimum_required(VERSION 3.5)
project(pattern)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MAKE_PROGRAM "make")

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

add_executable(pattern main.cpp element.cpp field.cpp player.cpp main.h element.h field.h player.h)
