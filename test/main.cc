#include <cassert>
#include <iostream>

#include "libmath.hh"

#define EXECUTE_TEST(test_func) \
    std::cout << "Executing " #test_func "... "; \
    test_func(); \
    std::cout << "OK" << std::endl

void test_vector_comparisons() {
    // Test == comparison operator
    vecf<3> a = {1, 2, 3};
    vecf<3> b = {1, 2, 3};
    assert((a == b));

    // Test != comparison operator
    vecf<3> c = {1, 2, 3};
    vecf<3> d = {1, 5, 3};
    assert((c != d));
}

void test_vector_addition() {
    vecf<3> a = {1, 2, 3};
    vecf<3> b = {1, 2, 3};
    assert((a + b == vecf<3>{2, 4, 6}));
}

void test_vector_substraction() {
    vecf<3> a = {1, 2, 3};
    vecf<3> b = {1, 2, 3};
    assert((a - b == vecf<3>{0, 0, 0}));
    
}

int main() {
    EXECUTE_TEST(test_vector_comparisons);
    EXECUTE_TEST(test_vector_addition);
    EXECUTE_TEST(test_vector_substraction);
}
