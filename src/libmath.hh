#pragma once

#define LIBMATH_BACKEND_SIMPLE_CPU

// Some backends such as SIMD based implementations have specific
// alignment requirements.
#ifdef LIBMATH_BACKEND_SIMPLE_CPU
    #define LIBMATH_VECTOR_ALIGN 
#elif LIBMATH_BACKEND_SIMD_SSE
    #define LIBMATH_VECTOR_ALIGN alignas(8)
#endif

#include "vector.hh"

// Include the selected backend implementation
#ifdef LIBMATH_BACKEND_SIMPLE_CPU
    #include "backends/simple_cpu.hh"
#elif LIBMATH_BACKEND_SIMD_SSE
    #include "backends/sse2.hh"
#endif
