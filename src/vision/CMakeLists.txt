#include_directories("${CMAKE_SOURCE_DIR}/3rdparties/opencv/lib/cmake/opencv4")

FILE(GLOB_RECURSE files *.cpp *.c)
message(STATUS "src/vision: ${files}")

add_library(lib_vision ${files})