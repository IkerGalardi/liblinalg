#!/bin/sh

# Execute the operations test
echo "- Operation correctness tests"
sh test/operations.sh
echo ""

# Execute vector size missmatch error test
echo "- Vector size missmatch error test"
sh test/vector_size_missmatch.sh

echo ""
echo "- Matrix size missmatch error test"
sh test/matrix_size_missmatch.sh
