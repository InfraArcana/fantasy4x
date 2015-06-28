#!/bin/bash

# Exit immediately if a command returns non-zero
set -e
set -o pipefail

if [ -z "${CXX}" ]; then
    echo "CXX environment variable not set, using \"clang++\""
    export CXX=clang++
else
    echo "CXX: \"${CXX}\""
fi

echo ""

# Print commands to terminal (with expanded variables)
set -x

mkdir -p build
cd build
cmake ..
make

# Disable command printing
set +x

echo ""
echo "------------------------------------------------------------------------"
echo "Build successful!"
echo ""
echo "From now on you can simply use the makefile in the \"build/\" directory."
echo ""

