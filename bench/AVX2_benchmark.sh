#!/bin/sh

COMPILATION_FLAGS="-mavx2 -m64 -std=c++17"
INCLUDE_FLAGS="-Isrc"

echo "- Simple CPU results:"

# Vector benchmark
g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBLINALG_BACKEND_SIMPLE_CPU bench/src/vector_bench.cc -o bin/vector_bench #2> /dev/null
./bin/vector_bench

# Matrix benchmark
g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBLINALG_BACKEND_SIMPLE_CPU bench/src/matrix_bench.cc -o bin/matrix_bench 2> /dev/null
./bin/matrix_bench

# Vector matrix benchmark
g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBLINALG_BACKEND_SIMPLE_CPU bench/src/matrix_vector_bench.cc -o bin/matrix_vector_bench 2> /dev/null
./bin/matrix_vector_bench

echo "- AVX2 results:"

# Vector benchmark
g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBLINALG_BACKEND_SIMD_AVX2 bench/src/vector_bench.cc -o bin/vector_bench 2> /dev/null
./bin/vector_bench

# Matrix benchmark
g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBLINALG_BACKEND_SIMD_AVX2 bench/src/matrix_bench.cc -o bin/matrix_bench 2> /dev/null
./bin/matrix_bench

# Vector matrix benchmark
g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBLINALG_BACKEND_SIMD_AVX2 bench/src/matrix_vector_bench.cc -o bin/matrix_vector_bench 2> /dev/null
./bin/matrix_vector_bench
