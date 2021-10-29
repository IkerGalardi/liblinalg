#pragma once

#define LIBMATH_BACKEND_SIMPLE_CPU

#include "vector.hh"

// Include the selected backend implementation
#ifdef LIBMATH_BACKEND_SIMPLE_CPU
    #include "backends/simple_cpu.hh"
#elif LIBMATH_BACKEND_SIMD_SSE
    #include "backends/sse2.hh"
#endif
