# ------------------------------------------------------------------------------
# Project
# ------------------------------------------------------------------------------
project (fantasy4x)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/target)

# Exported compile commands can be used by Emacs Irony-Mode auto completion
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------------------------------------------------------
# Verification
# ------------------------------------------------------------------------------
# Splitting strings with backslashes is only supported in 3.x.x
# (There may be other dependencies too...)
cmake_minimum_required (VERSION 3.2.3)

# Require generating build files in a "build" directory (out of source builds)
if (NOT (${CMAKE_BINARY_DIR} STREQUAL ${PROJECT_SOURCE_DIR}/build))
  message (STATUS "CMAKE_BINARY_DIR   : ${CMAKE_BINARY_DIR}")
  message (STATUS "PROJECT_SOURCE_DIR : ${PROJECT_SOURCE_DIR}")

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
# Compiler flags
# ------------------------------------------------------------------------------
# Using c++14 standard
set(CMAKE_CXX_STANDARD 14)

# TODO "CONSOLE_MODE" should not be hard coded here, it should depend on target
set (CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS} \
  -Wall \
  -Wextra \
  -pedantic \
  -fno-rtti \
  -fno-exceptions \
  -DCONSOLE_MODE \
  ")

# ------------------------------------------------------------------------------
# Source files (*.cpp and *.hpp)
# ------------------------------------------------------------------------------
# Load external source file list
file (READ ${PROJECT_SOURCE_DIR}/source.txt SRC_FILES)
string (REPLACE "\n" ";" SRC_FILES ${SRC_FILES})

include_directories (${PROJECT_SOURCE_DIR}/include)

# ------------------------------------------------------------------------------
# Executable
# ------------------------------------------------------------------------------
add_executable (${PROJECT_NAME} ${SRC_FILES})

# ------------------------------------------------------------------------------
# Libraries
# ------------------------------------------------------------------------------
if (WIN32)
	# Windows platform - use the pdcurses lib distributed with the project
	set (PDCURSES_DIR ${PROJECT_SOURCE_DIR}/libs/pdcurses)
	
	set (LIBS ${LIBS} ${PDCURSES_DIR}/pdcurses.lib)
	
	include_directories (${PDCURSES_DIR}/include)
	
	# Copy dll file to target directory
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"${PDCURSES_DIR}/pdcurses.dll"
			${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

else() # Not Windows platform
	
	# Find ncurses lib
	set (CURSES_NEED_NCURSES TRUE)
	
	find_package (Curses REQUIRED)

	set (LIBS ${LIBS} ${CURSES_LIBRARIES})
	
	include_directories (${CURSES_INCLUDE_DIRS})
endif()

target_link_libraries (${PROJECT_NAME} ${LIBS})

# ------------------------------------------------------------------------------
# Copy resources to target directory
# ------------------------------------------------------------------------------
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/resources"
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
