#!/bin/sh

COMPILATION_FLAGS="-msse4.1 -m64 -std=c++17"
INCLUDE_FLAGS="-Isrc"

echo "- Simple CPU results:"

# Vector benchmark
g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBMATH_BACKEND_SIMPLE_CPU bench/src/vector_bench.cc -o bin/vector_bench #2> /dev/null
./bin/vector_bench

# Matrix benchmark
g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBMATH_BACKEND_SIMPLE_CPU bench/src/matrix_bench.cc -o bin/matrix_bench 2> /dev/null
./bin/matrix_bench

# Vector matrix benchmark
g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBMATH_BACKEND_SIMPLE_CPU bench/src/matrix_vector_bench.cc -o bin/matrix_vector_bench 2> /dev/null
./bin/matrix_vector_bench

echo "- SSE results:"

# Vector benchmark
g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBMATH_BACKEND_SIMD_SSE bench/src/vector_bench.cc -o bin/vector_bench 2> /dev/null
./bin/vector_bench

# Matrix benchmark
g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBMATH_BACKEND_SIMD_SSE bench/src/matrix_bench.cc -o bin/matrix_bench 2> /dev/null
./bin/matrix_bench

# Vector matrix benchmark
g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBMATH_BACKEND_SIMD_SSE bench/src/matrix_vector_bench.cc -o bin/matrix_vector_bench 2> /dev/null
./bin/matrix_vector_bench
