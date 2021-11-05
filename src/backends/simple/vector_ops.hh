#include <cmath>

/*
 * Returns the length of the vector squared. Usefull when the exact length is not necessary 
 * or length need to be compared. Using the formula v[1]^2 + v[2]^2 + ...
 */
template<size_t size>
float length_squared(const vecf<size>& vec) {
    float sum = 0.0;
    for(int i = 0; i < size; i++) {
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
    float sum = 0.0;
    for(int i = 0; i < size; i++) {
        sum += right.data[i] * left.data[i];
    }

    return sum;
}

/*
 * Performs the addition between two vectors of equal size. If the sizes of the vectors don't
 * match a compilation error is thrown.
 */
template<size_t size>
vecf<size> operator+(const vecf<size>& left, const vecf<size>& right) {
    vecf<size> result;
    for(int i = 0; i < size; i++)
        result.data[i] = left.data[i] + right.data[i];

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
        result.data[i] = left.data[i] - right.data[i];

    return result;
}

/*
 * Performs the multiplication between two vectors of equal size. If the sizes of the 
 * vectors don't match a compilation error is thrown.
 */
template<size_t size>
vecf<size> operator*(const vecf<size>& left, const vecf<size>& right) {
    vecf<size> result;
    for(int i = 0; i < size; i++)
        result.data[i] = left.data[i] * right.data[i];

    return result;
}

/*
 * Performs the multiplication between a scalar and a vector of equal size. If the sizes
 * of the vectors don't match a compilation error is thrown.
 */
template<size_t size>
vecf<size> operator*(float scalar, const vecf<size>& right) {
    vecf<size> result;
    for(int i = 0; i < size; i++)
        result.data[i] = scalar * right.data[i];

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
