#pragma once 

/*
 * Returns true if both matrix are equal. If sizes or some element inside doesn't match
 * false is returned.
 */
template<size_t lnrow, size_t lncol, size_t rnrow, size_t rncol>
bool operator==(const matf<lnrow, lncol>& left, const matf<rnrow, rncol>& right) {
    // If matrices have no equal sizes they aren't equal
    if constexpr(lnrow != rnrow || lncol != rncol) {
        return false;
    }

    for(int i = 0; i < lnrow; i++) {
        for(int j = 0; j < rncol; j++) {
            if(left(i, j) != right(i, j)) {
                return false;
            }
        }
    }

    return true;
}

/*
 * Opposite of the == operator. If sizes missmatch or an element doesn't match true is
 * returned, else false is returned.
 */
template<size_t lnrow, size_t lncol, size_t rnrow, size_t rncol>
bool operator!=(const matf<lnrow, lncol>& left, const matf<rnrow, rncol>& right) {
    return !(left == right);
}

/*
 * Returns the addition of two matrices. If sizes don't match a compile time error is 
 * thrown.
 */
template<size_t nrow, size_t ncol>
matf<nrow, ncol> operator+(const matf<nrow, ncol>& left, const matf<nrow, ncol>& right) {
    matf<nrow, ncol> result;

    // Not all elements can be processed in parallel, so we calculate how much
    // we need to do in serie.
    constexpr int cant_process = ncol % LIBMATH_PARALLEL_FLOATS;

    // Process as much elements with SIMD instructions.
    for(int i = 0; i < nrow; i++) {
        for(int j = 0; j < ncol - cant_process; j+=4) {
            __m128 elems_left = _mm_loadu_ps(left.data + i * ncol + j);
            __m128 elems_right = _mm_loadu_ps(right.data + i * ncol + j);
            __m128 summed = _mm_add_ps(elems_left, elems_right);
            _mm_storeu_ps(result.data + i * ncol + j, summed);
        }
        
        // Some elements couldn't be processed in parallel, process them now
        // in serie.
        for(int j = ncol - cant_process; j < ncol; j++) {
            result(i, j) = left(i, j) + right(i, j);
        }
    }

    return result;
}

/*
 * Returns the substraction of two matrices. If sizes don't match a compile time error is 
 * thrown.
 */
template<size_t nrow, size_t ncol>
matf<nrow, ncol> operator-(const matf<nrow, ncol>& left, const matf<nrow, ncol>& right) {
    matf<nrow, ncol> result;

    // Not all elements can be processed in parallel, so we calculate how much
    // we need to do in serie.
    constexpr int cant_process = ncol % LIBMATH_PARALLEL_FLOATS;

    // Process as much elements with SIMD instructions.
    for(int i = 0; i < nrow; i++) {
        for(int j = 0; j < ncol - cant_process; j+=4) {
            __m128 elems_left = _mm_loadu_ps(left.data + i * ncol + j);
            __m128 elems_right = _mm_loadu_ps(right.data + i * ncol + j);
            __m128 subed = _mm_sub_ps(elems_left, elems_right);
            _mm_storeu_ps(result.data + i * ncol + j, subed);
        }
        
        // Some elements couldn't be processed in parallel, process them now
        // in serie.
        for(int j = ncol - cant_process; j < ncol; j++) {
            result(i, j) = left(i, j) - right(i, j);
        }
    }

    return result;
}

/*
 * Returns the multiplication between a scalar and a matrix.
 */
template<size_t nrow, size_t ncol>
matf<nrow, ncol> operator*(float scalar, const matf<nrow, ncol>& right) {
    matf<nrow, ncol> result;

    // Not all elements can be processed in parallel, so we calculate how much
    // we need to do in serie.
    constexpr int cant_process = ncol % LIBMATH_PARALLEL_FLOATS;

    // Process as much elements with SIMD instructions.
    __m128 vec_scalar = _mm_set1_ps(scalar);
    for(int i = 0; i < nrow; i++) {
        for(int j = 0; j < ncol - cant_process; j+=4) {
            __m128 elems_right = _mm_loadu_ps(right.data + i * ncol + j);
            __m128 muled = _mm_mul_ps(vec_scalar, elems_right);
            _mm_storeu_ps(result.data + i * ncol + j, muled);
        }
        
        // Some elements couldn't be processed in parallel, process them now
        // in serie.
        for(int j = ncol - cant_process; j < ncol; j++) {
            result(i, j) *= scalar;
        }
    }

    return result;
}

/*
 * Returns the multiplication between two matrices. If the number of columns of the left
 * operand does not equal to the number of rows of the right operand a compile time error
 * is thrown.
 */
template<size_t lnrow, size_t lncol, size_t rncol>
matf<lnrow, rncol> operator*(const matf<lnrow, lncol>& left, 
                             const matf<lncol, rncol>& right) {
    matf<lnrow, rncol> result {0,};

    for(int i = 0; i < lnrow; i++) {
        for(int j = 0; j < rncol; j++) {
            constexpr int cant_process = lncol % LIBMATH_PARALLEL_FLOATS;
            
            // Process as much elements as possible using SIMD instructions.
            __m128 partial_sum = _mm_setzero_ps();
            for(int k = 0; k < lncol - cant_process; k+=4) {
                __m128 left_elems = _mm_loadu_ps(left.data + i * lncol + k);

                // TODO: fix this workaround if it's possible
                __m128 right_col_elems = _mm_set_ps(right(k + 3, j), 
                                                    right(k + 2, j),
                                                    right(k + 1, j),
                                                    right(k + 0, j));
                __m128 multiplied = _mm_mul_ps(left_elems, right_col_elems);
                partial_sum = _mm_add_ps(partial_sum, multiplied);
            }

            // TODO: maybe a more efficient way of doing an hadd??
            alignas(16) float sum_elems[4];
            _mm_store_ps(sum_elems, partial_sum);
            
            // Some elements couldn't be processed in parallel, process them now
            // in serie.
            float sum = sum_elems[3] + sum_elems[2] + sum_elems[1] + sum_elems[0];
            for(int k = lncol - cant_process; k < lncol; k++){
                sum += left(i, k) * right(k, j);
            }

            result(i, j) = sum;
        } 
    }

    return result;
}
