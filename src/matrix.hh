#pragma once

/*
 * A matrix represented in a row major layout. This means that 
 */
template<size_t ncol, size_t nrow>
struct matf {
    float data[nrow * ncol];

    float& operator()(size_t i, size_t j) {
        return data[i * nrow + j];
    }

    const float& operator()(size_t i, size_t j) const {
        return data[i * nrow + j];
    }
};
