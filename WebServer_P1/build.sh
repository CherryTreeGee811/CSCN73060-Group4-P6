#! /bin/bash
set -xe

# Default to debug build if no argument is provided
#BUILD_TYPE=${1:-debug}

# Set CMake build type variable based on input
#if [[ "$BUILD_TYPE" == "debug" ]]; then
#    CMAKE_BUILD_TYPE="Debug"
#    BUILD_DIR="build"
#
#    find . -type f -name "*.h" | xargs sed -i 's/#define RELEASE_BUILD/#define DEBUG_BUILD/'
#elif [[ "$BUILD_TYPE" == "release" ]]; then
#    CMAKE_BUILD_TYPE="Release"
#    BUILD_DIR="$BUILD_TYPE"
#
#    find . -type f -name "*.h" | xargs sed -i 's/#define DEBUG_BUILD/#define RELEASE_BUILD/'
#else
#    echo "Invalid build type: $BUILD_TYPE"
#    echo "Usage: $0 [debug|release]"
#    exit 1
#fi

BUILD_DIR="build"
mkdir -p "$BUILD_DIR"

#cmake CMakeLists.txt -B $BUILD_DIR -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE
cmake CMakeLists.txt -B $BUILD_DIR -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cd "$BUILD_DIR"
ninja
