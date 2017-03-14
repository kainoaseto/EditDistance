cmake_minimum_required(VERSION 3.6)
project(EditDistance)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp EditDistanceAlgo.cpp EditDistanceAlgo.h pch.h)
add_executable(EditDistance ${SOURCE_FILES})