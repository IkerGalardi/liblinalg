#!/bin/sh


COMPILATION_FLAGS="-msse4.1 -O2 -m64 -std=c++17"
INCLUDE_FLAGS="-Isrc"

echo "Simple CPU backend:"
g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBMATH_BACKEND_SIMPLE_CPU test/src/operations.cc -o bin/operations
./bin/operations

echo "SSE backend:"
g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBMATH_BACKEND_SIMD_SSE test/src/operations.cc -o bin/operations
./bin/operations
