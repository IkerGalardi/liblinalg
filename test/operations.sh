#!/bin/sh

if [ $1="help" ] || [ -z $1 ]
then
    echo "A backend needs to be selected to test."
    echo "Available options are SIMD_SSE and SIMPLE_CPU"
    exit
else
    echo "Testing $1"
fi

COMPILATION_FLAGS="-msse4.1 -mavx2 -O2 -m64 -std=c++17"
INCLUDE_FLAGS="-Isrc"

rm -f bin/operations

g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBLINALG_BACKEND_$1 test/src/operations.cc -o bin/operations
./bin/operations
