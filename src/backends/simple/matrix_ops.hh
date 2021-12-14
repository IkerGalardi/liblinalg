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
template<size_t lnrow, size_t lncol, size_t rnrow, size_t rncol>
matf<lnrow, lncol> operator+(const matf<lnrow, lncol>& left, const matf<rnrow, rncol>& right) {
    static_assert(lnrow == rnrow && lncol == rncol,
                  "Matrix sizes are not equal");

    matf<lnrow, lncol> result;

    for(int i = 0; i < lnrow; i++) {
        for(int j = 0; j < lncol; j++) {
            result(i, j) = left(i, j) + right(i, j);
        }
    }

    return result;
}

/*
 * Returns the substraction of two matrices. If sizes don't match a compile time error is 
 * thrown.
 */
template<size_t lnrow, size_t lncol, size_t rnrow, size_t rncol>
matf<lnrow, lncol> operator-(const matf<lnrow, lncol>& left, const matf<rnrow, rncol>& right) {
    static_assert(lnrow == rnrow && lncol == rncol,
                  "Matrix sizes are not equal");

    matf<lnrow, lncol> result;

    for(int i = 0; i < lnrow; i++) {
        for(int j = 0; j < lncol; j++) {
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

    for(int i = 0; i < nrow; i++) {
        for(int j = 0; j < ncol; j++) {
            result(i, j) = scalar * right(i, j);
        }
    }

    return result;
}

/*
 * Returns the multiplication between two matrices. If the number of columns of the left
 * operand does not equal to the number of rows of the right operand a compile time error
 * is thrown.
 */
template<size_t lnrow, size_t lncol, size_t rnrow, size_t rncol>
matf<lnrow, rncol> operator*(const matf<lnrow, lncol>& left, 
                             const matf<rnrow, rncol>& right) {
    static_assert(rnrow == lncol, 
                  "Left's number of columns does not equal to right's number or rows");

    matf<lnrow, rncol> result;

    for(int i = 0; i < lnrow; i++) {
        for(int j = 0; j < rncol; j++) {
            float sum = 0.0f;
            for(int k = 0; k < lncol; k++) {
                sum += left(i, k) * right(k, j);
            }
            result(i, j) = sum;
        } 
    }

    return result;
}
