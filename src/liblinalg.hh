#pragma once

#if defined(LIBLINALG_BACKEND_SIMPLE_CPU)
    #define LIBLINALG_ALIGNMENT   
#elif defined(LIBLINALG_BACKEND_SIMD_SSE)
    #define LIBLINALG_ALIGNMENT alignas(16) 
#endif

#include <cmath>

#include "vector.hh"
#include "matrix.hh"

// Include the selected backend implementation
#if defined(LIBLINALG_BACKEND_SIMPLE_CPU)
    #include "backends/simple/simple.hh"
#elif defined(LIBLINALG_BACKEND_SIMD_SSE)
    #include "backends/sse/sse.hh"
#endif
