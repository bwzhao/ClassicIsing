cmake_minimum_required(VERSION 3.6)
project(ClassicIsing_Feb10)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Calculation.cpp Calculation.h Config.h Lattice.cpp Lattice.h)
add_executable(ClassicIsing_Feb10 ${SOURCE_FILES})