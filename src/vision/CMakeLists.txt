#include_directories()

FILE(GLOB_RECURSE files *.cpp *.c)
message(STATUS "src/vision: ${files}")

add_library(lib_vision ${files})