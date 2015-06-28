# ------------------------------------------------------------------------------
# Verification
# ------------------------------------------------------------------------------
# Splitting strings with backslashes is only supported in 3.x.x
# (There may be other dependencies too...)
CMAKE_MINIMUM_REQUIRED (VERSION 3.2.3)

# Require generating build files in a "build" directory (out of source builds)
if (NOT (${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR}/build))
  MESSAGE (STATUS "CMAKE_BINARY_DIR         : ${CMAKE_BINARY_DIR}")
  MESSAGE (STATUS "CMAKE_CURRENT_SOURCE_DIR : ${CMAKE_CURRENT_SOURCE_DIR}")

  MESSAGE (FATAL_ERROR
    " \
    \n Must run cmake from \"build\" directory! \
    \n \
    \n Hint: \
    \n $ mkdir build && cd build && cmake .. \
    \n \
    \n (note the trailing \"..\") \
    \n \
    \n You should probably also delete CMakeCache.txt before trying again. \
    ")
endif ()

# ------------------------------------------------------------------------------
# Project
# ------------------------------------------------------------------------------
PROJECT (fantasy4x)

SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/target)

# ------------------------------------------------------------------------------
# Compiler flags
# ------------------------------------------------------------------------------
SET (CMAKE_CXX_FLAGS
  " \
  ${CMAKE_CXX_FLAGS} \
  -std=c++11 \
  -Wall \
  -Wextra \
  -pedantic \
  -fno-rtti \
  -fno-exceptions \
  ")

# ------------------------------------------------------------------------------
# Source files (.cpp)
# ------------------------------------------------------------------------------
# Load external source file list
FILE (READ ${CMAKE_CURRENT_SOURCE_DIR}/source.txt SRC_FILES)
STRING (REPLACE "\n" ";" SRC_FILES ${SRC_FILES})

# ------------------------------------------------------------------------------
# Executable
# ------------------------------------------------------------------------------
ADD_EXECUTABLE (${PROJECT_NAME} ${SRC_FILES})

# ------------------------------------------------------------------------------
# Libraries
# ------------------------------------------------------------------------------
# Find ncurses lib
SET (CURSES_NEED_NCURSES TRUE)
FIND_PACKAGE (Curses REQUIRED)

SET (LIBS ${LIBS} ${CURSES_LIBRARIES})

TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${LIBS})

# ------------------------------------------------------------------------------
# Include directories
# ------------------------------------------------------------------------------
INCLUDE_DIRECTORIES (${CMAKE_CURRENT_SOURCE_DIR}/include ${CURSES_INCLUDE_DIRS})
