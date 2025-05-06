#!/bin/bash

set -e  # Exit on first error
BUILD_DIR="build"
EXECUTABLE="elevator_control"

echo "Creating build directory..."
mkdir -p "$BUILD_DIR"

echo "Configuring CMake..."
cmake -B "$BUILD_DIR"

echo "Building project..."
cmake --build "$BUILD_DIR" --parallel

echo "Build complete."
echo "Running executable..."
./"$BUILD_DIR"/"$EXECUTABLE"
