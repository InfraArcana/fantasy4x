# ------------------------------------------------------------------------------
# Verification
# ------------------------------------------------------------------------------
# Splitting strings with backslashes is only supported in 3.x.x
# (There may be other dependencies too...)
cmake_minimum_required (VERSION 3.2.3)

# Require generating build files in a "build" directory (out of source builds)
if (NOT (${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR}/build))
  message (STATUS "CMAKE_BINARY_DIR         : ${CMAKE_BINARY_DIR}")
  message (STATUS "CMAKE_CURRENT_SOURCE_DIR : ${CMAKE_CURRENT_SOURCE_DIR}")

  message (FATAL_ERROR
    " \
    \n Must run cmake from \"build\" directory! \
    \n \
    \n Hint: \
    \n $ mkdir build && cd build && cmake .. \
    \n \
    \n (note the trailing \"..\") \
    \n \
    \n You should probably delete CMakeCache.txt etc before trying again. \
    ")
endif ()

# ------------------------------------------------------------------------------
# Project
# ------------------------------------------------------------------------------
project (fantasy4x)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/target)

# ------------------------------------------------------------------------------
# Compiler flags
# ------------------------------------------------------------------------------
# Using c++14 standard
set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS
  " \
  ${CMAKE_CXX_FLAGS} \
  -Wall \
  -Wextra \
  -pedantic \
  -fno-rtti \
  -fno-exceptions \
  ")

# ------------------------------------------------------------------------------
# Source files (*.cpp and *.hpp)
# ------------------------------------------------------------------------------
# Load external source file list
file (READ ${CMAKE_CURRENT_SOURCE_DIR}/source.txt SRC_FILES)
string (REPLACE "\n" ";" SRC_FILES ${SRC_FILES})

# ------------------------------------------------------------------------------
# Executable
# ------------------------------------------------------------------------------
add_executable (${PROJECT_NAME} ${SRC_FILES})

# ------------------------------------------------------------------------------
# Libraries
# ------------------------------------------------------------------------------
# Find ncurses lib
set (CURSES_NEED_NCURSES TRUE)
find_package (Curses REQUIRED)

set (LIBS ${LIBS} ${CURSES_LIBRARIES})

target_link_libraries (${PROJECT_NAME} ${LIBS})

# ------------------------------------------------------------------------------
# Include directories
# ------------------------------------------------------------------------------
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include ${CURSES_INCLUDE_DIRS})
