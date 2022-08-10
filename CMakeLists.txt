cmake_minimum_required(VERSION 3.22)
project(Assignment_3)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES src/main.cc src/Graph3.cc src/Utils3.cc)
add_executable(main ${SOURCES})
target_include_directories(main PUBLIC include)