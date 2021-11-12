#pragma once

template<size_t nrow, size_t ncol>
vecf<nrow> operator*(const matf<nrow, ncol>& mat, const vecf<ncol>& vec) {
    vecf<nrow> result;
    for(int i = 0; i < nrow; i++) {
        constexpr int cant_process = ncol % LIBMATH_PARALLEL_FLOATS;

        __m128 partial_sum = _mm_setzero_ps();
        for(int j = 0; j < ncol - cant_process; j+=4) {
            // sum += vec.data[j] * mat(i, j);
            
            __m128 vec_elems = _mm_load_ps(vec.data + j);
            __m128 mat_elems = _mm_loadu_ps(mat.data + i * nrow + j);
            __m128 multiplied = _mm_mul_ps(vec_elems, mat_elems);
            partial_sum = _mm_add_ps(partial_sum, multiplied);
        }

        alignas(16) float sum_elems[4];
        _mm_store_ps(sum_elems, partial_sum);
        float sum = sum_elems[3] + sum_elems[2] + sum_elems[1] + sum_elems[0];

        for(int j = ncol - cant_process; j < cant_process; j++) {
            sum += vec.data[j] * mat(i, j);
        }

        result.data[i] = sum;
    }

    return result;
}

template<size_t nrow, size_t ncol>
vecf<ncol> operator*(const vecf<ncol>& vec, const matf<nrow, ncol>& mat) {
    vecf<ncol> result;
    for(int i = 0; i < ncol; i++) {
        constexpr int cant_process = nrow & LIBMATH_PARALLEL_FLOATS;

        __m128 vec_elem = _mm_set1_ps(vec.data[i]);
        __m128 partial_sum = _mm_setzero_ps();
        for(int j = 0; j < nrow - cant_process; j+=4) {
            __m128 mat_col_elems = _mm_set_ps(mat(j + 3, i), 
                                              mat(j + 2, i),
                                              mat(j + 1, i),
                                              mat(j + 0, i));
            __m128 multiplied = _mm_mul_ps(vec_elem, mat_col_elems);
            partial_sum = _mm_add_ps(partial_sum, multiplied);
        }

        alignas(16) float sum_elems[4];
        _mm_store_ps(sum_elems, partial_sum);
        float sum = sum_elems[3] + sum_elems[2] + sum_elems[1] + sum_elems[0];

        for(int j = nrow - cant_process; j < nrow; j++) {
            sum += sum += vec.data[i] * mat(j, i);
        }

        result.data[i] = sum;
    }

    return result;
}
