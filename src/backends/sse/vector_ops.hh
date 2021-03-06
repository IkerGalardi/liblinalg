#include <cmath>

/*
 * Returns the length of the vector squared. Usefull when the exact length is not necessary 
 * or length need to be compared. Using the formula v[1]^2 + v[2]^2 + ...
 */
template<size_t size>
float length_squared(const vecf<size>& vec) {
    // Maybe not all the elements can be executed using SSE2 instructions, so we see 
    // beforehand how many can be executed in parallel and how many serially.
    constexpr int left_after_parallel = size % LIBLINALG_PARALLEL_FLOATS;
    constexpr int parallel_iterations = size - left_after_parallel;

    // TODO: test to see when to start parallel implementation and when simply
    //       use a for loop, maybe using the vector extensions to add two vectors
    //       and add horizontally is slower.
    __m128 partial_sum = _mm_setzero_ps();
    for(int i = 0; i < parallel_iterations; i += 4) {
        __m128 elems = _mm_load_ps(vec.data + i);
        __m128 elems_squared = _mm_mul_ps(elems, elems);
        partial_sum = _mm_add_ps(partial_sum, elems_squared);
    }

    // TODO: try using horizontal adds
    LIBLINALG_ALIGNMENT float sum_elems[LIBLINALG_PARALLEL_FLOATS];
    _mm_store_ps(sum_elems, partial_sum);
    float sum = 0;
    for(int i = 0; i < LIBLINALG_PARALLEL_FLOATS; i++) {
        sum += sum_elems[i];
    }

    // Process all the elements left
    for(int i = parallel_iterations; i < size; i++) {
        sum += vec.data[i] * vec.data[i];
    }

    return sum;
}

/*
 * Returns the length of the vector using the pithagoras formula.
 */
template<size_t size>
float length(const vecf<size>& vec) {
    return std::sqrt(length_squared(vec));
}

/*
 * Returns dot product of two vectors.
 */
template<size_t size>
float dot(const vecf<size>& left, const vecf<size>& right) {
    // Maybe not all the elements can be executed using SSE2 instructions, so we see 
    // beforehand how many can be executed in parallel and how many serially.
    constexpr int left_after_parallel = size % LIBLINALG_PARALLEL_FLOATS;
    constexpr int parallel_iterations = size - left_after_parallel;

    // TODO: test to see when to start parallel implementation and when simply
    //       use a for loop, maybe using the vector extensions to add two vectors
    //       and add horizontally is slower.
    __m128 partial_sum = _mm_setzero_ps();
    for(int i = 0; i < parallel_iterations; i += 4) {
        __m128 left_elems = _mm_load_ps(left.data + i);
        __m128 right_elems = _mm_load_ps(right.data + i);
        __m128 multiplied = _mm_mul_ps(right_elems, left_elems);
        partial_sum = _mm_add_ps(partial_sum, multiplied);
    }

    // TODO: try using horizontal adds
    LIBLINALG_ALIGNMENT float sum_elems[LIBLINALG_PARALLEL_FLOATS];
    _mm_store_ps(sum_elems, partial_sum);
    float sum = 0;
    for(int i = 0; i < LIBLINALG_PARALLEL_FLOATS; i++) {
        sum += sum_elems[i];
    }

    // Process all the elements left
    for(int i = parallel_iterations; i < size; i++) {
        sum += left.data[i] * right.data[i];
    }

    return sum;
}

/*
 * Performs the addition between two vectors of equal size. If the sizes of the vectors don't
 * match a compilation error is thrown.
 */
template<size_t size>
vecf<size> operator+(const vecf<size>& left, const vecf<size>& right) {
    // Maybe not all the elements can be executed using SSE2 instructions, so we see 
    // beforehand how many can be executed in parallel and how many serially.
    constexpr int left_after_parallel = size % LIBLINALG_PARALLEL_FLOATS;
    constexpr int parallel_iterations = size - left_after_parallel;

    vecf<size> result;

    // Process in elements using SSE2 instructions
    for(int i = 0; i < parallel_iterations; i += 4) {
        __m128 left_elem = _mm_load_ps(left.data + i);
        __m128 right_elem = _mm_load_ps(right.data + i);
        __m128 res_elem = _mm_add_ps(left_elem, right_elem);
        _mm_store_ps(result.data + i, res_elem);
    }

    // Process all the elements left
    for(int i = parallel_iterations; i < size; i++) {
        result.data[i] = left.data[i] + right.data[i];
    }

    return result;
}

/*
 * Performs the substraction between two vectors of equal size. If the sizes of the vectors 
 * don't match a compilation error is thrown.
 */
template<size_t size>
vecf<size> operator-(const vecf<size>& left, const vecf<size>& right) {
    // Maybe not all the elements can be executed using SSE2 instructions, so we see 
    // beforehand how many can be executed in parallel and how many serially.
    constexpr int left_after_parallel = size % LIBLINALG_PARALLEL_FLOATS;
    constexpr int parallel_iterations = size - left_after_parallel;

    vecf<size> result;

    // Process in elements using SSE2 instructions
    for(int i = 0; i < parallel_iterations; i += 4) {
        __m128 left_elem = _mm_load_ps(left.data + i);
        __m128 right_elem = _mm_load_ps(right.data + i);
        __m128 res_elem = _mm_sub_ps(left_elem, right_elem);
        _mm_store_ps(result.data + i, res_elem);
    }

    // Process all the elements left
    for(int i = parallel_iterations; i < size; i++) {
        result.data[i] = left.data[i] - right.data[i];
    }

    return result;
}

/*
 * Performs the multiplication between two vectors of equal size. If the sizes of the 
 * vectors don't match a compilation error is thrown.
 */
template<size_t size>
vecf<size> operator*(const vecf<size>& left, const vecf<size>& right) {
    // Maybe not all the elements can be executed using SSE2 instructions, so we see 
    // beforehand how many can be executed in parallel and how many serially.
    constexpr int left_after_parallel = size % LIBLINALG_PARALLEL_FLOATS;
    constexpr int parallel_iterations = size - left_after_parallel;

    vecf<size> result;

    // Process in elements using SSE2 instructions
    for(int i = 0; i < parallel_iterations; i += 4) {
        __m128 left_elem = _mm_load_ps(left.data + i);
        __m128 right_elem = _mm_load_ps(right.data + i);
        __m128 res_elem = _mm_mul_ps(left_elem, right_elem);
        _mm_store_ps(result.data + i, res_elem);
    }

    // Process all the elements left
    for(int i = parallel_iterations; i < size; i++) {
        result.data[i] = left.data[i] * right.data[i];
    }

    return result;
}

/*
 * Performs the multiplication between a scalar and a vector of equal size. If the sizes
 * of the vectors don't match a compilation error is thrown.
 */
template<size_t size>
vecf<size> operator*(float scalar, const vecf<size>& right) {
    // Maybe not all the elements can be executed using SSE2 instructions, so we see 
    // beforehand how many can be executed in parallel and how many serially.
    constexpr int left_after_parallel = size % LIBLINALG_PARALLEL_FLOATS;
    constexpr int parallel_iterations = size - left_after_parallel;

    vecf<size> result;

    // Process in elements using SSE2 instructions
    __m128 scalar_vectorized = _mm_set1_ps(scalar);
    for(int i = 0; i < parallel_iterations; i += 4) {
        __m128 right_elem = _mm_load_ps(right.data + i);
        __m128 res_elem = _mm_mul_ps(scalar_vectorized, right_elem);
        _mm_store_ps(result.data + i, res_elem);
    }

    // Process all the elements left
    for(int i = parallel_iterations; i < size; i++) {
        result.data[i] = scalar * right.data[i];
    }

    return result;
}

/*
 * Compares the passed vectors. True is returned if both vectors are equal and false is returned
 * if the vectors are not equal.
 */
template<size_t size>
bool operator==(const vecf<size>& left, const vecf<size>& right) {
    bool is_equal;
    for(int i = 0; i < size; i++) {
        if(left.data[i] != right.data[i]) 
            return false;
    }

    return true;
}

/*
 * Compares the passed vectors. False is returned if both vectors are equal and true is returned
 * if the vectors are not equal.
 */
template<size_t size>
bool operator!=(const vecf<size>& left, const vecf<size>& right) {
    return !(left == right);
}
