#pragma once

/*
 * Performs the multiplication of two matrices, interpreting the vector as a column matrix.
 * If the vector's element count doesn't match matrix's number of columns a compile time 
 * error is thrown.
 */
template<size_t nrow, size_t ncol, size_t vlen>
vecf<nrow> operator*(const matf<nrow, ncol>& mat, const vecf<vlen>& vec) {
    static_assert(ncol == vlen,
                  "Vector length is not equal to the number of columns of the matrix");

    vecf<nrow> result;
    for(int i = 0; i < nrow; i++) {
        float sum = 0.0f;
        for(int j = 0; j < ncol; j++) {
            sum += vec.data[j] * mat(i, j);
        }

        result.data[i] = sum;
    }

    return result;
}

/*
 * Performs the multiplication of two matrices, interpreting the vector as a row matrix.
 * If the vector's element count doesn't match matrix's number of columns a compile time
 * error is thrown.
 */
template<size_t nrow, size_t ncol, size_t vlen>
vecf<ncol> operator*(const vecf<vlen>& vec, const matf<nrow, ncol>& mat) {
    static_assert(vlen == ncol,
                  "Vector length is not equal to the number of columns of the matrix");

    vecf<ncol> result;
    for(int i = 0; i < ncol; i++) {
        float sum = 0.0f;
        for(int j = 0; j < nrow; j++) {
            sum += vec.data[i] * mat(j, i);
        }

        result.data[i] = sum;
    }

    return result;
}
