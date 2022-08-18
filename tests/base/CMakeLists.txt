#include_directories()

FILE(GLOB_RECURSE files *.cpp *.c)
message(STATUS "test: ${files}")

add_library(lib_test ${files})