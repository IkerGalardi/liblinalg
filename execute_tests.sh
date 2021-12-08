#!/bin/sh

if [ $1 == "help" ] || [ -z $1 ]
then
    echo "A backend needs to be selected to test."
    echo "Available options are SIMD_SSE and SIMPLE_CPU."
    exit
fi

# Execute the operations test
echo "- Operation correctness tests"
sh test/operations.sh $1
echo ""

# Execute vector size missmatch error test
echo "- Vector size missmatch error test"
sh test/vector_size_missmatch.sh

echo ""
echo "- Matrix size missmatch error test"
sh test/matrix_size_missmatch.sh
