# LIBLINALG
`liblinalg` is a lineal algebra library that implements vectors and matrices of variable sizes and operations between them. Uses special instructions like [SSE](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#techs=MMX,SSE,SSE2,SSE3,SSSE3,SSE4_1) to accelerate those operations.

## Project status
The project is now on a stable version with multiple backends and tests but there are things that I want to do:

* Using AVX2 or AVX512 instruction to accelerate even bigger matrix and vector multiplications.

* Using SIMD instructions for arm machines.

There are still many operations that are not supported at all by the library like the determinant of a matrix. 

Apart from that, when vector and matrix operations missmatch sizes, compilation errors are thrown but aren't readable at all. Would be nice to investigate a way to throw custom compiler errors.

Right now each backend implements all the operations, but for error checking to be cleaner it would be nice to abstract away SIMD to unify a bit operation code.

Documentation about implementation decisions and backend implementation are still left to do.

## How to use
Being a header only library, the only thing necessary to use the library is to add all the header files to your project and define the backend. The available backends are the next: 

* `LIBLINALG_BACKEND_SIMPLE_CPU`: backend does not use any special instructions. It's mainly used to compare the performance from what most lineal algebra libraries do.

* `LIBLINALG_BACKEND_SIMD_SSE`: backend uses SSE instructions to accelerate operations. It's important to use the `-msse4.2` flag when compiling. SSE instructions are supported on 98% of the x86 processors.

## Contributions
Contributions helping to solve bugs or implementing special matrices or vectors such as those used in computer graphics are welcome! But pull requests implementing backends are going to be ignored as this project is mainly used to learn about SIMD.
