#pragma once 

#include <array>

template<size_t size> 
using vecf = std::array<float, size>;

/*
 * Performs the addition between two vectors of equal size. If the sizes of the vectors don't
 * match a compilation error is thrown.
 */
template<size_t size>
vecf<size> operator+(const vecf<size>& left, const vecf<size>& right) {
    vecf<size> result;
    for(int i = 0; i < size; i++)
        result[i] = left[i] + right[i];

    return result;
}

/*
 * Performs the substraction between two vectors of equal size. If the sizes of the vectors 
 * don't match a compilation error is thrown.
 */
template<size_t size>
vecf<size> operator-(const vecf<size>& left, const vecf<size>& right) {
    vecf<size> result;
    for(int i = 0; i < size; i++)
        result[i] = left[i] - right[i];

    return result;
}
