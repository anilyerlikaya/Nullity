#include_directories()

FILE(GLOB_RECURSE files *.cpp *.c)
message(STATUS "src/utils: ${files}")

add_library(lib_utils ${files})