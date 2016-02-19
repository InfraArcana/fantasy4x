PostApoc-Strategy
============
# Building from a fresh clone
1. Create a folder called "build" in the root of the project directory
2. Go to the build folder (e.g. in the Windows command line or a Unix shell), and run either
  * `cmake ..` for the default generator on your platform (e.g. Unix Makefiles), OR
  * `cmake .. -G "<generator-name>"` for a specific generator (see `cmake --help`)
3. Build the project using the generated Makefile/Visual Studio project/whatever

Steps 1 and 2 are typically only ever needed once.
