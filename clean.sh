#!/bin/bash

# Exit immediately if a command returns non-zero
set -e
set -o pipefail

# Print commands to terminal (with expanded variables)
set -x

rm -rf build target
