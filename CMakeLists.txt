cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(NM_EX)

set(CMAKE_CXX_STANDARD 11)

include_directories("${CMAKE_SOURCE_DIR}")

include_directories (include)

add_executable(ex1 src/ex1/ex1.cc)

file(COPY ${CMAKE_SOURCE_DIR}/src/ex1/plot_ex1.py
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})