#!/bin/sh

COMPILATION_FLAGS="-msse4.1 -O2 -m64 -std=c++17"
INCLUDE_FLAGS="-Isrc"

echo "Addition missmatch:---------------------------------------------------------"
g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBMATH_BACKEND_SIMPLE_CPU -DMISSMATCH_ADD test/src/vector_size_missmatch.cc -o bin/vector_size_missmatch
echo "----------------------------------------------------------------------------"

echo "Substraction missmatch:-----------------------------------------------------"
g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBMATH_BACKEND_SIMPLE_CPU -DMISSMATCH_SUB test/src/vector_size_missmatch.cc -o bin/vector_size_missmatch
echo "----------------------------------------------------------------------------"

echo "Dot product missmatch:------------------------------------------------------"
g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBMATH_BACKEND_SIMPLE_CPU -DMISSMATCH_DOT test/src/vector_size_missmatch.cc -o bin/vector_size_missmatch
echo "----------------------------------------------------------------------------"

