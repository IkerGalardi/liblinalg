#pragma once

#define LIBMATH_BACKEND_SIMD_SSE2

#if defined(LIBMATH_BACKEND_SIMPLE_CPU)
    #define LIBMATH_ALIGNMENT   
#elif defined(LIBMATH_BACKEND_SIMD_SSE2)
    #define LIBMATH_ALIGNMENT alignas(16) 
#endif

#include "vector.hh"

// Include the selected backend implementation
#if defined(LIBMATH_BACKEND_SIMPLE_CPU)
    #include "backends/simple_cpu.hh"
#elif defined(LIBMATH_BACKEND_SIMD_SSE2)
    #include "backends/sse2.hh"
#endif
