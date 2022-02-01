#!/bin/python3

import numpy as np
import random

# Settings to generate the tests
OPERATIONS_PER_SIZE = 1
SIZES_TO_TEST = [2, 8, 16, 22, 32]

#
# Generates a random vector of integers.
#
def generate_vector_elements(size):
    return np.random.randint(0, 9, size)

#
# Returns the string that represents that vector in form of cpp array 
# creation: '{e1, e2, e3, ...}'
#
def vector_string_from_array(vector):
    elements_string = np.array2string(vector, separator=',', threshold=1000000)
    elements_string = elements_string.replace('[', '{')
    elements_string = elements_string.replace(']', '}')

    return elements_string

#
# Creates a definition string of cpp given a name and a vector.
#
def vector_definition_from_array(name, vector):
    vector_string = "vecf<{}> {}= ".format(len(vector), name)
    elems = vector_string_from_array(vector)
    vector_string = vector_string + elems + ';'
    return vector_string

def matrix_definition_from_array(name, nrow, ncol, vector):
    matrix_string = "matf<{}, {}> {} = ".format(ncol, nrow, name)
    elems = vector_string_from_array(vector)
    matrix_string = matrix_string + elems + ';'
    return matrix_string

def print_vector_comparison_tests():
    print('void test_vector_comparisons() {')
    var_num = 0
    for i in SIZES_TO_TEST:
        for j in range(OPERATIONS_PER_SIZE):
            a_name = "a{}".format(var_num)
            b_name = "b{}".format(var_num)

            a = generate_vector_elements(i)
            b = a

            print('    ' + vector_definition_from_array(a_name, a))
            print('    ' + vector_definition_from_array(b_name, b))
            print('    assert((a{} == b{}));'.format(var_num, var_num));
            
            var_num = var_num + 1

    print('}')


def print_vector_deep_copies_tests():
    # TODO: investigate if it's necessary to test deep copies for different sizes,
    #       probably not but who knows.
    print('void test_vector_deep_copies() {')
    print('    vecf<2> a = {1, 2};')
    print('    auto b = a;')
    print('    b.data[0] = 7;')
    print('    assert((a.data[0]) == 1);')
    print('}')

def print_vector_addition_tests():
    print('void test_vector_addition() {')
    var_num = 0
    for i in SIZES_TO_TEST:
        for j in range(OPERATIONS_PER_SIZE):
            a_name = "a{}".format(var_num)
            b_name = "b{}".format(var_num)
            e_name = "e{}".format(var_num)

            a = generate_vector_elements(i)
            b = generate_vector_elements(i)
            e = a + b

            print('    ' + vector_definition_from_array(a_name, a))
            print('    ' + vector_definition_from_array(b_name, b))
            print('    ' + vector_definition_from_array(e_name, e))
            print('    auto r{} = a{} + b{};'.format(var_num, var_num, var_num))
            print('    assert((r{} == e{}));'.format(var_num, var_num));
            
            var_num = var_num + 1

    print('}')

def print_vector_substraction_tests():
    print('void test_vector_substraction() {')
    var_num = 0
    for i in SIZES_TO_TEST:
        for j in range(OPERATIONS_PER_SIZE):
            a_name = "a{}".format(var_num)
            b_name = "b{}".format(var_num)
            e_name = "e{}".format(var_num)

            a = generate_vector_elements(i)
            b = generate_vector_elements(i)
            e = a - b

            print('    ' + vector_definition_from_array(a_name, a))
            print('    ' + vector_definition_from_array(b_name, b))
            print('    ' + vector_definition_from_array(e_name, e))
            print('    auto r{} = a{} - b{};'.format(var_num, var_num, var_num))
            print('    assert((r{} == e{}));'.format(var_num, var_num));
            
            var_num = var_num + 1

    print('}')

def print_vector_length_tests():
    print('void test_vector_length() {')
    var_num = 0
    for i in SIZES_TO_TEST:
        for j in range(OPERATIONS_PER_SIZE):
            a_name = "a{}".format(var_num)

            a = generate_vector_elements(i)
            e = sum(i**2 for i in a)

            print('    ' + vector_definition_from_array(a_name, a))
            print('    float e{} = {};'.format(var_num, e))
            print('    auto r{} = length_squared(a{});'.format(var_num, var_num))
            print('    assert((r{} == e{}));'.format(var_num, var_num));
            
            var_num = var_num + 1

    print('}')

def print_vector_dot_tests():
    print('void test_vector_dotproduct() {')
    var_num = 0
    for i in SIZES_TO_TEST:
        for j in range(OPERATIONS_PER_SIZE):
            a_name = "a{}".format(var_num)
            b_name = "b{}".format(var_num)
            e_name = "e{}".format(var_num)

            a = generate_vector_elements(i)
            b = generate_vector_elements(i)
            e = np.dot(a, b)

            print('    ' + vector_definition_from_array(a_name, a))
            print('    ' + vector_definition_from_array(b_name, b))
            print('    float e{} = {};'.format(var_num, e))
            print('    auto r{} = dot(a{}, b{});'.format(var_num, var_num, var_num))
            print('    assert((r{} == e{}));'.format(var_num, var_num));
            
            var_num = var_num + 1

    print('}')


def print_vector_multiplication_tests():
    print('void test_vector_multiplication() {')
    var_num = 0
    for i in SIZES_TO_TEST:
        for j in range(OPERATIONS_PER_SIZE):
            a_name = "a{}".format(var_num)
            b_name = "b{}".format(var_num)
            e_name = "e{}".format(var_num)

            a = generate_vector_elements(i)
            b = generate_vector_elements(i)
            e = np.multiply(a, b)

            print('    ' + vector_definition_from_array(a_name, a))
            print('    ' + vector_definition_from_array(b_name, b))
            print('    ' + vector_definition_from_array(e_name, e))
            print('    auto r{} = a{} * b{};'.format(var_num, var_num, var_num))
            print('    assert((r{} == e{}));'.format(var_num, var_num));
            
            var_num = var_num + 1

    print('}')

def print_matrix_indexing_tests():
    print('void test_matrix_indexing() {')
    print('    matf<2, 2> a = {1, 2, ')
    print('                3, 4};')
    print('    assert((a(0, 1) == 2));')
    print('    matf<2, 4> b = {1, 2, 3, 4,')
    print('                    5, 6, 7, 8};')
    print('    assert((b(0, 3) == 4));')
    print('}')

def print_matrix_deep_copies_tests():
    print('void test_matrix_deep_copies() {')
    print('    matf<2, 2> a = {1, 2, ')
    print('                    3, 4};')
    print('    matf<2, 2> b = a;')
    print('    b(0, 0) = 7;')
    print('    assert((a(0, 0) == 1));')
    print('}')

def print_matrix_comparisons_tests():
    print('void test_matrix_comparisons() {')
    var_num = 0
    for nrow in SIZES_TO_TEST:
        for ncol in SIZES_TO_TEST:
            for j in range(OPERATIONS_PER_SIZE):
                a_name = "a{}".format(var_num)
                b_name = "b{}".format(var_num)

                a = generate_vector_elements(nrow * ncol)

                print('    ' + matrix_definition_from_array(a_name, nrow, ncol, a))
                print('    ' + matrix_definition_from_array(b_name, nrow, ncol, a))
                print('    assert(({} == {}));'.format(a_name, b_name));
                
                var_num = var_num + 1
    print('}')

def print_matrix_addition_tests():
    print('void test_matrix_addition() {')
    var_num = 0
    for nrow in SIZES_TO_TEST:
        for ncol in SIZES_TO_TEST:
            for j in range(OPERATIONS_PER_SIZE):
                a_name = "a{}".format(var_num)
                b_name = "b{}".format(var_num)
                r_name = "r{}".format(var_num)
                e_name = "e{}".format(var_num)

                a = generate_vector_elements(nrow * ncol)
                b = generate_vector_elements(nrow * ncol)

                mat_a = np.reshape(a, (-1, ncol))
                mat_b = np.reshape(b, (-1, ncol))
                mat_e = np.add(a, b)
                e = mat_e.flatten()

                print('    ' + matrix_definition_from_array(a_name, nrow, ncol, a))
                print('    ' + matrix_definition_from_array(b_name, nrow, ncol, b))
                print('    ' + matrix_definition_from_array(e_name, nrow, ncol, e))
                print('    assert(({} + {} == {}));'.format(a_name, b_name, e_name));
                
                var_num = var_num + 1
    print('}')

def print_matrix_multiplication_tests():
    print('void test_matrix_multiplication() {')
    print('    // Scalar * Matrix operations')
    var_num = 0
    for nrow in SIZES_TO_TEST:
        for ncol in SIZES_TO_TEST:
            for j in range(OPERATIONS_PER_SIZE):
                a_name = "a{}".format(var_num)
                b_name = "b{}".format(var_num)
                r_name = "r{}".format(var_num)
                e_name = "e{}".format(var_num)

                a = generate_vector_elements(nrow * ncol)
                b = generate_vector_elements(1)[0]

                mat_a = np.reshape(a, (-1, ncol))
                mat_e = np.multiply(a, b)
                e = mat_e.flatten()

                print('    ' + matrix_definition_from_array(a_name, nrow, ncol, a))
                print('    float {} = {};'.format(b_name, b))
                print('    ' + matrix_definition_from_array(e_name, nrow, ncol, e))
                print('    assert(({} * {} == {}));'.format(b_name, a_name, e_name));
                
                var_num = var_num + 1

    print('    // Matrix * Matrix operations')
    for nrow in SIZES_TO_TEST:
        for ncol in SIZES_TO_TEST:
            for rncol in SIZES_TO_TEST:
                for j in range(OPERATIONS_PER_SIZE):
                    a_name = "a{}".format(var_num)
                    b_name = "b{}".format(var_num)
                    e_name = "e{}".format(var_num)

                    a = generate_vector_elements(nrow * ncol)
                    b = generate_vector_elements(ncol * rncol)

                    mat_a = np.reshape(a, (nrow,  ncol))
                    mat_b = np.reshape(b, (ncol, rncol))
                    
                    #print(mat_a, flush=True)
                    #print(mat_b, flush=True)
                    
                    #print(f'{mat_a.shape}, ')
                    mat_e = np.dot(mat_a, mat_b)
                    e = mat_e.flatten()
                    print('    ' + matrix_definition_from_array(a_name, ncol, nrow, a))
                    print('    ' + matrix_definition_from_array(b_name, rncol, ncol, b))
                    print('    ' + matrix_definition_from_array(e_name, rncol, nrow, e))
                    print('    assert(({} * {} == {}));'.format(a_name, b_name, e_name))
                    
                    var_num = var_num + 1
    print('}')

# Printing all the headers and macros
print('#include <cassert>')
print('#include <iostream>')
print('')
print('#include "liblinalg.hh"')
print('')
print('#define EXECUTE_TEST(test_func) \\')
print('    std::cout << "Executing " #test_func "... " << std::flush; \\')
print('    test_func(); \\')
print('    std::cout << "OK" << std::endl')
print('')

# Printing all the tests
print_vector_comparison_tests()
print_vector_deep_copies_tests()
print_vector_addition_tests()
print_vector_substraction_tests()
print_vector_length_tests()
print_vector_dot_tests()
print_vector_multiplication_tests()
print_matrix_indexing_tests()
print_matrix_deep_copies_tests()
print_matrix_comparisons_tests()
print_matrix_addition_tests()
print_matrix_multiplication_tests()

# Printing the main function with all the tests
print('')
print('int main() {')
print('    EXECUTE_TEST(test_vector_comparisons);')
print('    EXECUTE_TEST(test_vector_deep_copies);')
print('    EXECUTE_TEST(test_vector_addition);')
print('    EXECUTE_TEST(test_vector_substraction);')
print('    EXECUTE_TEST(test_vector_length);')
print('    EXECUTE_TEST(test_vector_dotproduct);')
print('    EXECUTE_TEST(test_vector_multiplication);')
print('    EXECUTE_TEST(test_matrix_indexing);')
print('    EXECUTE_TEST(test_matrix_deep_copies);')
print('    EXECUTE_TEST(test_matrix_comparisons);')
print('    EXECUTE_TEST(test_matrix_addition);')
print('    EXECUTE_TEST(test_matrix_multiplication);')
#print('    EXECUTE_TEST(test_matrix_vector_multiplication);')
print('}')
