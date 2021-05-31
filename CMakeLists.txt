cmake_minimum_required(VERSION 3.15)
project(howmuch CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(~/neo/)

add_executable(howmuch main.cpp)
