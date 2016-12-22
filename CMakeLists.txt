
cmake_minimum_required(VERSION 2.8)

PROJECT(thread_pool CXX)

set(CMAKE_BUILD_TYPE Debug)

set(CXX_FLAGS
 -g
 # -DVALGRIND
 -D_FILE_OFFSET_BITS=64
 -Wall
# -Wextra
 #-Werror
 -Wconversion
 #-Wno-unused-parameter
 -Wold-style-cast
 -Woverloaded-virtual
 -Wpointer-arith
# -Wshadow
 -Wwrite-strings
 -march=native
 # -MMD
 # -std=c++0x
 -rdynamic
 )
if(CMAKE_BUILD_BITS EQUAL 32)
  list(APPEND CXX_FLAGS "-m32")
endif()
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -finline-limit=1000 -DNDEBUG")


string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
message(STATUS "CXX_FLAGS = " ${CMAKE_CXX_FLAGS} " " ${CMAKE_CXX_FLAGS_${BUILD_TYPE}})

include_directories(.)

aux_source_directory(. SOURCES_DIR)

set(SOURCES_FILE ${SOURCES_DIR})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_library(ptp ${SOURCES_FILE})
#TARGET_LINK_LIBRARIES(${TARGET} pthread rt)



