#pragma once

#define LIBMATH_BACKEND_SIMPLE_CPU

#if defined(LIBMATH_BACKEND_SIMPLE_CPU)
    #define LIBMATH_ALIGNMENT   
#elif defined(LIBMATH_BACKEND_SIMD_SSE)
    #define LIBMATH_ALIGNMENT alignas(16) 
#endif

#include <cmath>

#include "vector.hh"
#include "matrix.hh"

// Include the selected backend implementation
#if defined(LIBMATH_BACKEND_SIMPLE_CPU)
    #include "backends/simple/simple.hh"
#elif defined(LIBMATH_BACKEND_SIMD_SSE)
    #include "backends/sse/sse.hh"
#endif
