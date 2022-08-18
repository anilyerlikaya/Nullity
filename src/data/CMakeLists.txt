#include_directories(${CMAKE_SOURCE_DIR}/src/)

FILE(GLOB_RECURSE files *.cpp *.c)
message(STATUS "src/data: ${files}")

add_library(lib_data ${files})