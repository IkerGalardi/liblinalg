#pragma once

/*
 * A matrix represented in a row major layout. This means that 
 */
template<size_t ncol, size_t nrow>
struct matf {
    float data[nrow][ncol];
}
