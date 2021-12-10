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
    constexpr int cant_process = ncol % LIBLINALG_PARALLEL_FLOATS;

    // Process as much elements with SIMD instructions.
    for(int i = 0; i < nrow; i++) {
        for(int j = 0; j < ncol - cant_process; j+=LIBLINALG_PARALLEL_FLOATS) {
            __m256 elems_left = _mm256_loadu_ps(left.data + i * ncol + j);
            __m256 elems_right = _mm256_loadu_ps(right.data + i * ncol + j);
            __m256 summed = _mm256_add_ps(elems_left, elems_right);
            _mm256_storeu_ps(result.data + i * ncol + j, summed);
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
    constexpr int cant_process = ncol % LIBLINALG_PARALLEL_FLOATS;

    // Process as much elements with SIMD instructions.
    for(int i = 0; i < nrow; i++) {
        for(int j = 0; j < ncol - cant_process; j+=LIBLINALG_PARALLEL_FLOATS) {
            __m256 elems_left = _mm256_loadu_ps(left.data + i * ncol + j);
            __m256 elems_right = _mm256_loadu_ps(right.data + i * ncol + j);
            __m256 subed = _mm256_sub_ps(elems_left, elems_right);
            _mm256_storeu_ps(result.data + i * ncol + j, subed);
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
    constexpr int cant_process = ncol % LIBLINALG_PARALLEL_FLOATS;

    // Process as much elements with SIMD instructions.
    __m256 vec_scalar = _mm256_set1_ps(scalar);
    for(int i = 0; i < nrow; i++) {
        for(int j = 0; j < ncol - cant_process; j+=LIBLINALG_PARALLEL_FLOATS) {
            __m256 elems_right = _mm256_loadu_ps(right.data + i * ncol + j);
            __m256 muled = _mm256_mul_ps(vec_scalar, elems_right);
            _mm256_storeu_ps(result.data + i * ncol + j, muled);
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
            constexpr int cant_process = lncol % LIBLINALG_PARALLEL_FLOATS;
            
            // Process as much elements as possible using SIMD instructions.
            __m256 partial_sum = _mm256_setzero_ps();
            __m256i vindex = _mm256_set1_epi32(j * rncol);
            for(int k = 0; k < lncol - cant_process; k+=LIBLINALG_PARALLEL_FLOATS) {
                __m256 left_elems = _mm256_loadu_ps(left.data + i * lncol + k);

                __m256 right_col_elems = _mm256_i32gather_ps(right.data + k * rncol + j, vindex, 1);
                __m256 multiplied = _mm256_mul_ps(left_elems, right_col_elems);
                partial_sum = _mm256_add_ps(partial_sum, multiplied);
            }

            // TODO: maybe a more efficient way of doing an hadd??
            LIBLINALG_ALIGNMENT float sum_elems[8] = {0, };
            _mm256_store_ps(sum_elems, partial_sum);

            // Some elements couldn't be processed in parallel, process them now
            // in serie.
            float sum = 0;
            for(int i = 0; i < 8; i++) {
                sum += sum_elems[i];
            } 
            
            for(int k = lncol - cant_process; k < lncol; k++){
                sum += left(i, k) * right(k, j);
            }

            result(i, j) = sum;
        } 
    }

    return result;
}
