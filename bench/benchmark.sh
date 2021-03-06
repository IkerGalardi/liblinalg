#!/bin/sh

if [ $1 = "help" ] || [ -z $1 ]
then
    echo "A backend needs to be selected to test."
    echo "Available options are SIMD_SSE and SIMPLE_CPU"
    exit
fi

COMPILATION_FLAGS="-msse4.1 -mavx2 -m64 -std=c++17"
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

rm -f bin/vector_bench bin/matrix_bench matrix_vector_bench

echo "- $1 results:"

# Vector benchmark
g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBLINALG_BACKEND_$1 bench/src/vector_bench.cc -o bin/vector_bench 2> /dev/null
./bin/vector_bench

# Matrix benchmark
g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBLINALG_BACKEND_$1 bench/src/matrix_bench.cc -o bin/matrix_bench 2> /dev/null
./bin/matrix_bench

# Vector matrix benchmark
g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBLINALG_BACKEND_$1 bench/src/matrix_vector_bench.cc -o bin/matrix_vector_bench 2> /dev/null
./bin/matrix_vector_bench
