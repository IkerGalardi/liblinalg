#include <cassert>
#include <iostream>

#include "libmath.hh"

#define EXECUTE_TEST(test_func) \
    std::cout << "Executing " #test_func "... " << std::flush; \
    test_func(); \
    std::cout << "OK" << std::endl

template<size_t nrow, size_t ncol> 
constexpr void print_matrix(const matf<nrow, ncol>& mat) {
    for(int i = 0; i < nrow; i++) {
        for(int j = 0; j < ncol; j++) {
            std::cout << mat(i, j) << ", ";
        }

        std::cout << std::endl;
    }
}

template<size_t n> 
constexpr void print_vector(const vecf<n>& vec) {
    for(int i = 0; i < n; i++) {
        std::cout << vec.data[i] << ", ";
    }
    std::cout << std::endl;
}

void test_vector_comparisons() {
    // Test == comparison operator
    vecf<6> a = {1, 2, 3, 4, 5, 6};
    vecf<6> b = {1, 2, 3, 4, 5, 6};
    assert((a == b));

    // Test != comparison operator
    vecf<3> c = {1, 2, 3};
    vecf<3> d = {1, 5, 3};
    assert((c != d));
}

void test_vector_deep_copies() {
    vecf<2> a = {1, 2};
    auto b = a;

    b.data[0] = 7;
    assert((a.data[0]) == 1);
}

void test_vector_addition() {
    vecf<6> a = {1, 2, 3, 1, 2, 3};
    vecf<6> b = {1, 2, 3, 1, 2, 3};
    assert((a + b == vecf<6>{2, 4, 6, 2, 4, 6}));

    vecf<3> c = {1, 2, 3};
    vecf<3> d = {1, 2, 3};
    assert((c + d == vecf<3>{2, 4, 6}));

    vecf<9> e = {1, 2, 3, 1, 2, 3, 1, 2, 3};
    vecf<9> f = {1, 2, 3, 1, 2, 3, 1, 2, 3};
    assert((e + f == vecf<9>{2, 4, 6, 2, 4, 6, 2, 4, 6}));

    vecf<1> g = {1};
    vecf<1> h = {1};
    assert((g + h == vecf<1>{2}));
}

void test_vector_substraction() {
    vecf<6> a = {1, 2, 3, 1, 2, 3};
    vecf<6> b = {1, 2, 3, 1, 2, 3};
    assert((a - b == vecf<6>{0, 0, 0, 0, 0, 0}));

    vecf<3> c = {1, 2, 3};
    vecf<3> d = {1, 2, 3};
    assert((c - d == vecf<3>{0, 0, 0}));

    vecf<9> e = {1, 2, 3, 1, 2, 3, 1, 2, 3};
    vecf<9> f = {1, 2, 3, 1, 2, 3, 1, 2, 3};
    assert((e - f == vecf<9>{0, 0, 0, 0, 0, 0, 0, 0, 0}));

    vecf<1> g = {1};
    vecf<1> h = {1};
    assert((g - h == vecf<1>{0}));
}

void test_vector_length() {
    vecf<1> a = {1};
    assert((length_squared(a) == 1));
    
    vecf<2> b = {1, 1};
    assert((length_squared(b) == 2));

    vecf<4> c = {1, 1, 1, 1};
    assert((length_squared(c) == 4));

    vecf<9> d = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    assert((length_squared(d) == 9));
}

void test_vector_dotproduct() {
    vecf<1> a = {1};
    vecf<1> b = {1};
    assert((dot(a, b) == 1));

    vecf<2> c = {1, 2};
    vecf<2> d = {1, 2};
    assert((dot(c, d) == 5));

    vecf<4> e = {1, 2, 2, 4};
    vecf<4> f = {1, 3, 2, 7};
    assert((dot(e, f) == 39));

    vecf<6> g = {1, 2, 2, 4, 6, 5};
    vecf<6> h = {1, 3, 2, 7, 1, 3};
    assert((dot(g, h) == 60));

    vecf<9> j = {1, 2, 2, 4, 6, 5, 4, 2, 9};
    vecf<9> k = {1, 3, 2, 7, 1, 3, 4, 1, 3};
    assert((dot(j, k) == 105));
}

void test_vector_multiplication() {
    vecf<1> a = {2};
    vecf<1> b = {2};
    assert((a * b == vecf<1>{4}));

    vecf<2> c = {2, 1};
    vecf<2> d = {2, 4};
    assert((c * d == vecf<2>{4, 4}));

    vecf<4> e = {2, 1, 2, 7};
    vecf<4> f = {2, 4, 3, 1};
    assert((e * f == vecf<4>{4, 4, 6, 7}));

    vecf<6> g = {2, 1, 2, 7, 1, 8};
    vecf<6> h = {2, 4, 3, 1, 8, 1};
    assert((g * h == vecf<6>{4, 4, 6, 7, 8, 8}));
}

void test_matrix_indexing() {
    matf<2, 2> a = {1, 2, 
                    3, 4};
    assert((a(0, 1) == 2));


    matf<2, 4> b = {1, 2, 3, 4,
                    5, 6, 7, 8};
    assert((b(0, 3) == 4));
}

void test_matrix_deep_copies() {
    matf<2, 2> a = {1, 2, 
                    3, 4};
    matf<2, 2> b = a;

    b(0, 0) = 7;
    assert((a(0, 0) == 1));
}

void test_matrix_comparisons() {
    matf<2, 2> a = {1, 2,
                    3, 2};
    matf<2, 2> b = {1, 5,
                    2, 1};
    assert(a != b);
    matf<4, 4> c = {1, 2, 4, 1,
                    3, 2, 2, 7,
                    2, 1, 6, 9,
                    1, 5, 1, 8};
    matf<4, 4> d = {1, 2, 4, 1,
                    3, 2, 2, 7,
                    2, 1, 6, 9,
                    1, 5, 1, 8};
    assert(c == d);
}

void test_matrix_addition() {
    matf<2, 2> a = {1, 2,
                    3, 2};
    matf<2, 2> b = {1, 5,
                    2, 1};
    assert((a + b == matf<2, 2>{2, 7, 
                                5, 3}));

    matf<4, 4> c = {1, 2, 4, 1,
                    3, 2, 2, 7,
                    2, 1, 6, 9,
                    1, 5, 1, 8};
    matf<4, 4> d = {1, 4, 2, 1,
                    3, 2, 7, 1,
                    1, 4, 1, 1,
                    1, 5, 1, 1};
    assert((c + d == matf<4, 4>{2, 6,  6, 2,
                                6, 4,  9, 8,
                                3, 5,  7, 10,
                                2, 10, 2, 9}));

    // TODO: test more sizes
}

void test_matrix_multiplication() {
    matf<2, 2> a = {1, 2,
                    3, 2};
    matf<2, 2> b = {1, 5,
                    2, 1};
    assert((a * b == matf<2, 2>{5, 7, 
                                7, 17}));

    matf<3, 3> c = {1, 4, 2,
                    3, 6, 3,
                    1, 4, 2};
    matf<3, 3> d = {2, 1, 3,
                    5, 2, 1,
                    1, 7, 2};
    assert((c * d == matf<3, 3>{24, 23, 11,
                                39, 36, 21,
                                24, 23, 11}));

    matf<4, 4> e = {1, 2, 3, 4,
                    0, 2, 7, 0,
                    0, 0, 2, 2,
                    2, 5, 0, 1};
    matf<4, 4> f = {1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1};
    assert((e * f == matf<4, 4>{1, 2, 3, 4,
                                0, 2, 7, 0,
                                0, 0, 2, 2,
                                2, 5, 0, 1}));

    matf<2, 4> g = {1, 4, 2, 3,
                    3, 6, 3, 1};
    matf<4, 3> h = {2, 1, 3,
                    5, 2, 1, 
                    1, 7, 2,
                    3, 2, 1};
    assert((g * h == matf<2, 3>{33, 29, 14,
                              42, 38, 22}));
}

void test_matrix_vector_multiplication() {
    matf<2, 3> a = {1, -1, 2,
                    0, -3, 1};
    vecf<3> b = {2, 1, 0};
    auto res = a * b;
    assert((res == vecf<2>{1, -3}));

    matf<3, 3> c = {1, 2, 3, 
                    4, 5, 6, 
                    7, 8, 9};
    vecf<3> d = {2, 1, 3};
    assert((c * d == vecf<3>{13, 31, 49}));
}

int main() {
    EXECUTE_TEST(test_vector_comparisons);
    EXECUTE_TEST(test_vector_deep_copies);
    EXECUTE_TEST(test_vector_addition);
    EXECUTE_TEST(test_vector_substraction);
    EXECUTE_TEST(test_vector_length);
    EXECUTE_TEST(test_vector_dotproduct);
    EXECUTE_TEST(test_vector_multiplication);
    EXECUTE_TEST(test_matrix_indexing);
    EXECUTE_TEST(test_matrix_deep_copies);
    EXECUTE_TEST(test_matrix_comparisons);
    EXECUTE_TEST(test_matrix_addition);
    EXECUTE_TEST(test_matrix_multiplication);
    EXECUTE_TEST(test_matrix_vector_multiplication);
}
