message ("CXX: \"$ENV{CXX}\"")

# Create "build" directory
file(MAKE_DIRECTORY build)

# Go to the build directory and run cmake
# TODO: Is there some better way to this than "execute_process"?
#       It's not possible to run "-E" commands straight from CMake scripts?
execute_process (COMMAND cmake -E chdir build cmake ..)
