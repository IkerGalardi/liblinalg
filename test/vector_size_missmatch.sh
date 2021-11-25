#!/bin/sh

COMPILATION_FLAGS="-msse4.1 -O2 -m64 -std=c++17"
INCLUDE_FLAGS="-Isrc"

g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBLINALG_BACKEND_SIMPLE_CPU -DMISSMATCH_ADD test/src/vector_size_missmatch.cc -o bin/vector_size_missmatch 2> /dev/null || echo "Addition missmatch... OK"

g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBLINALG_BACKEND_SIMPLE_CPU -DMISSMATCH_SUB test/src/vector_size_missmatch.cc -o bin/vector_size_missmatch 2> /dev/null || echo "Substraction missmatch... OK"

g++ $COMPILATION_FLAGS $INCLUDE_FLAGS -DLIBLINALG_BACKEND_SIMPLE_CPU -DMISSMATCH_DOT test/src/vector_size_missmatch.cc -o bin/vector_size_missmatch 2> /dev/null || echo "Dot product missmatch... OK"
