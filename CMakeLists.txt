cmake_minimum_required(VERSION 3.28)
project(untitled)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

add_executable(untitled main.cpp
        testFunctions.cpp
        testFunctions.h
        PSO.cpp
        PSO.h)
