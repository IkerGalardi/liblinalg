#pragma once 

template<size_t lnrow, size_t lncol, size_t rnrow, size_t rncol>
bool operator==(const matf<lnrow, lncol>& left, const matf<rnrow, rncol>& right) {
    // If matrices have no equal sizes they aren't equal
    if constexpr(lnrow != rnrow || lncol != rncol) {
        return false;
    }

    for(int i = 0; i < lnrow; i++) {
        for(int j = 0; j < rncol; j++) {
            if(left.data[i][j] != right.data[i][j]) {
                return false;
            }
        }
    }

    return true;
}

template<size_t lnrow, size_t lncol, size_t rnrow, size_t rncol>
bool operator!=(const matf<lnrow, lncol>& left, const matf<rnrow, rncol>& right) {
    return !(left == right);
}

template<size_t nrow, size_t ncol>
matf<nrow, ncol> operator+(const matf<nrow, ncol>& left, const matf<nrow, ncol>& right) {
    matf<nrow, ncol> result;

    for(int i = 0; i < nrow; i++) {
        for(int j = 0; j < ncol; j++) {
            result.data[i][j] = left.data[i][j] + right.data[i][j];
        }
    }

    return result;
}

template<size_t nrow, size_t ncol>
matf<nrow, ncol> operator-(const matf<nrow, ncol>& left, const matf<nrow, ncol>& right) {
    matf<nrow, ncol> result;

    for(int i = 0; i < nrow; i++) {
        for(int j = 0; j < ncol; j++) {
            result.data[i][j] = left.data[i][j] - right.data[i][j];
        }
    }

    return result;
}

template<size_t nrow, size_t ncol>
matf<nrow, ncol> operator*(float scalar, const matf<nrow, ncol>& right) {
    matf<nrow, ncol> result;

    for(int i = 0; i < nrow; i++) {
        for(int j = 0; j < ncol; j++) {
            result.data[i][j] = scalar * right.data[i][j];
        }
    }

    return result;
}

template<size_t lnrow, size_t lncol, size_t rncol>
matf<lnrow, rncol> operator*(const matf<lnrow, lncol>& left, 
                             const matf<lncol, rncol>& right) {
    matf<lnrow, rncol> result;

    for(int i = 0; i < lnrow; i++) {
        for(int j = 0; j < rncol; j++) {
            float elem = 0.0f;
            for(int k = 0; k < lncol; k++) {
                elem += left.data[i][k] * right.data[k][j];
            }

            result.data[i][j] = elem;
        } 
    }

    return result;
}
