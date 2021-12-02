#pragma once

/*
 * Performs the multiplication of two matrices, interpreting the vector as a column matrix.
 * If the vectors element count doesn't match matrices number of columns a compile time error
 * is thrown.
 */
template<size_t nrow, size_t ncol>
vecf<nrow> operator*(const matf<nrow, ncol>& mat, const vecf<ncol>& vec) {
    vecf<nrow> result;
    for(int i = 0; i < nrow; i++) {
        constexpr int cant_process = ncol % LIBLINALG_PARALLEL_FLOATS;

        // Process as much elements with SIMD instructions.
        __m256 partial_sum = _mm256_setzero_ps();
        for(int j = 0; j < ncol - cant_process; j+=LIBLINALG_PARALLEL_FLOATS) {
            __m256 vec_elems = _mm256_load_ps(vec.data + j);
            __m256 mat_elems = _mm256_loadu_ps(mat.data + i * nrow + j);
            __m256 multiplied = _mm256_mul_ps(vec_elems, mat_elems);
            partial_sum = _mm256_add_ps(partial_sum, multiplied);
        }

        LIBLINALG_ALIGNMENT float sum_elems[LIBLINALG_PARALLEL_FLOATS];
        _mm256_store_ps(sum_elems, partial_sum);
        float sum = 0;
        for(int i = 0; i < LIBLINALG_PARALLEL_FLOATS; i++) {
            sum += sum_elems[i];
        }

        // Some elements couldn't be processed in parallel, process them now
        // in serie.
        for(int j = ncol - cant_process; j < cant_process; j++) {
            sum += vec.data[j] * mat(i, j);
        }

        result.data[i] = sum;
    }

    return result;
}

/*
 * Performs the multiplication of two matrices, interpreting the vector as a column matrix.
 * If the vector's element count doesn't match matrix's number of columns a compile time 
 * error is thrown.
 */
template<size_t nrow, size_t ncol>
vecf<ncol> operator*(const vecf<ncol>& vec, const matf<nrow, ncol>& mat) {
    vecf<ncol> result;
    for(int i = 0; i < ncol; i++) {
        constexpr int cant_process = nrow & LIBLINALG_PARALLEL_FLOATS;

        // Process as much elements with SIMD instructions.
        __m256 vec_elem = _mm256_set1_ps(vec.data[i]);
        __m256 partial_sum = _mm256_setzero_ps();
        __m256i vindex = _mm256_set1_epi32(i * ncol);
        for(int j = 0; j < nrow - cant_process; j+=LIBLINALG_PARALLEL_FLOATS) {
            // TODO: check a faster way of doing this with sse.
            //__m256 mat_col_elems = _mm256_set_ps(mat(j + 3, i), 
            //                                  mat(j + 2, i),
            //                                  mat(j + 1, i),
            //                                  mat(j + 0, i));
            __m256 mat_col_elems = _mm256_i32gather_ps(mat.data + j * ncol + i, vindex, 8);

            __m256 multiplied = _mm256_mul_ps(vec_elem, mat_col_elems);
            partial_sum = _mm256_add_ps(partial_sum, multiplied);
        }

        LIBLINALG_ALIGNMENT float sum_elems[LIBLINALG_PARALLEL_FLOATS];
        _mm256_store_ps(sum_elems, partial_sum);
        float sum = 0;
        for(int i = 0; i < LIBLINALG_PARALLEL_FLOATS; i++) {
            sum += sum_elems[i];
        }

        // Some elements couldn't be processed in parallel, process them now
        // in serie.
        for(int j = nrow - cant_process; j < nrow; j++) {
            sum += sum += vec.data[i] * mat(j, i);
        }

        result.data[i] = sum;
    }

    return result;
}
