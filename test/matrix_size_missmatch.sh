#!/bin/sh

COMPILATION_FLAGS="-msse4.1 -O2 -m64 -std=c++17"
INCLUDE_FLAGS="-Isrc"


g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBLINALG_BACKEND_SIMPLE_CPU -DMISSMATCH_ADD test/src/matrix_size_missmatch.cc -o bin/matrix_size_missmatch
echo ""

g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBLINALG_BACKEND_SIMPLE_CPU -DMISSMATCH_SUB test/src/matrix_size_missmatch.cc -o bin/matrix_size_missmatch
echo ""

g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBLINALG_BACKEND_SIMPLE_CPU -DMISSMATCH_MUL test/src/matrix_size_missmatch.cc -o bin/matrix_size_missmatch
echo ""
