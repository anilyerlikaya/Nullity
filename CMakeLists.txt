cmake_minimum_required(VERSION 3.20) 

# project name
project(Nullity)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# opencv
set(OpenCV_DIR "${CMAKE_SOURCE_DIR}/3rdParties/opencv/lib/cmake/opencv4")
find_package(OpenCV REQUIRED)

#message(STATUS "OpenCV_Include: ${OpenCV_INCLUDE_DIRS}")
#message(STATUS "OpenCV_Libs: ${OpenCV_LIBS}")

# include directories
include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src/  
    ${CMAKE_SOURCE_DIR}/src/data/
    ${CMAKE_SOURCE_DIR}/src/vision/
)

########################################################################################################################################################################
############################################################# BEGIN MACROS #############################################################################################
########################################################################################################################################################################
macro(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
        SET(dirlist ${dirlist} ${curdir}/${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
endmacro()
########################################################################################################################################################################
############################################################# END MACROS ###############################################################################################
########################################################################################################################################################################

# get sub dirs in the given dir
#SUBDIRLIST(m_subdirs ${CMAKE_SOURCE_DIR}/src)
#message(STATUS "m_subdirs in src: ${m_subdirs}")

# add other projects
add_subdirectory(src/data)
add_subdirectory(src/vision)
add_subdirectory(src/algo)
add_subdirectory(src/utils)

# get build target option
option(BUILD_TEST "Use Test Build instead of Nullity" OFF) #OFF by default => "cmake -DUSE_MY_LIB=ON" to activate test build

# executable
if(BUILD_TEST)
    # test
    message(STATUS "Build Target => Test")
    include_directories(
        ${CMAKE_SOURCE_DIR}/tests/base/
    )

    add_subdirectory(tests/base)
    add_executable(Test tests/test_main.cpp)

    target_include_directories(Test PUBLIC ${OpenCV_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/tests/base ${CMAKE_SOURCE_DIR}/src/data ${CMAKE_SOURCE_DIR}/src/vision ${CMAKE_SOURCE_DIR}/src/utils)
    target_link_libraries(Test lib_data lib_vision lib_algo lib_test lib_utils ${OpenCV_LIBS})
else()
    #nullity
    message(STATUS "Build Target => Nullity")    
    add_executable(Nullity main.cpp)
    target_include_directories(Nullity PUBLIC ${OpenCV_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src/data ${CMAKE_SOURCE_DIR}/src/vision)
    target_link_libraries(Nullity lib_data lib_vision lib_algo ${OpenCV_LIBS})
endif(BUILD_TEST)
unset(BUILD_TEST CACHE)
