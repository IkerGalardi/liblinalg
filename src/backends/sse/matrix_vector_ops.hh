#pragma once

template<size_t nrow, size_t ncol>
vecf<nrow> operator*(const matf<nrow, ncol>& mat, const vecf<ncol>& vec) {
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

template<size_t nrow, size_t ncol>
vecf<ncol> operator*(const vecf<ncol>& vec, const matf<nrow, ncol>& mat) {
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
