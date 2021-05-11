cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(NM_EX)

set(CMAKE_CXX_STANDARD 11)

include_directories("${CMAKE_SOURCE_DIR}")

include_directories (include)

add_executable(ex1 src/ex1/ex1.cc)

file(COPY ${CMAKE_SOURCE_DIR}/src/ex1/plot_ex1.py
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(ex2 src/ex2/ex2.cc)

#find_package(GSL REQUIRED)

add_executable(ex3 src/ex3/ex3.cc src/ex3/gsl.cc)

#target_include_directories(ex3 PRIVATE ${PROJECT_SOURCE_DIR} ${GSL_INCLUDE_DIR})
#target_link_libraries(ex3 ${GSL_LIBRARIES})