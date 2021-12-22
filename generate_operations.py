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
    elements_string = np.array2string(vector, separator=',')
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

def print_vector_comparison_tests():
    print('void test_vector_comparisons() {')
    var_num = 0
    for i in SIZES_TO_TEST:
        for j in range(OPERATIONS_PER_SIZE):
            a1_name = "a{}".format(var_num)
            b1_name = "b{}".format(var_num)

            a = generate_vector_elements(i)
            b = a

            print('    ' + vector_definition_from_array(a1_name, a))
            print('    ' + vector_definition_from_array(b1_name, b))
            print('    assert((a{} == b{}));'.format(var_num, var_num));
            
            var_num = var_num + 1

    print('}')


def print_vector_deep_copies_tests():
    print('// TODO: vector deep copies test')

def print_vector_addition_tests():
    print('void test_vector_addition() {')
    var_num = 0
    for i in SIZES_TO_TEST:
        for j in range(OPERATIONS_PER_SIZE):
            a1_name = "a{}".format(var_num)
            b1_name = "b{}".format(var_num)
            e1_name = "e{}".format(var_num)

            a = generate_vector_elements(i)
            b = generate_vector_elements(i)
            e = a + b

            print('    ' + vector_definition_from_array(a1_name, a))
            print('    ' + vector_definition_from_array(b1_name, b))
            print('    ' + vector_definition_from_array(e1_name, e))
            print('    auto r{} = a{} + b{};'.format(var_num, var_num, var_num))
            print('    assert((r{} == e{}));'.format(var_num, var_num));
            
            var_num = var_num + 1

    print('}')

def print_vector_substraction_tests():
    print('void test_vector_substraction() {')
    var_num = 0
    for i in SIZES_TO_TEST:
        for j in range(OPERATIONS_PER_SIZE):
            a1_name = "a{}".format(var_num)
            b1_name = "b{}".format(var_num)
            e1_name = "e{}".format(var_num)

            a = generate_vector_elements(i)
            b = generate_vector_elements(i)
            e = a - b

            print('    ' + vector_definition_from_array(a1_name, a))
            print('    ' + vector_definition_from_array(b1_name, b))
            print('    ' + vector_definition_from_array(e1_name, e))
            print('    auto r{} = a{} - b{};'.format(var_num, var_num, var_num))
            print('    assert((r{} == e{}));'.format(var_num, var_num));
            
            var_num = var_num + 1

    print('}')

def print_vector_length_tests():
    print('void test_vector_length() {')
    var_num = 0
    for i in SIZES_TO_TEST:
        for j in range(OPERATIONS_PER_SIZE):
            a1_name = "a{}".format(var_num)

            a = generate_vector_elements(i)
            e = sum(i**2 for i in a)

            print('    ' + vector_definition_from_array(a1_name, a))
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
            a1_name = "a{}".format(var_num)
            b1_name = "b{}".format(var_num)
            e1_name = "e{}".format(var_num)

            a = generate_vector_elements(i)
            b = generate_vector_elements(i)
            e = np.dot(a, b)

            print('    ' + vector_definition_from_array(a1_name, a))
            print('    ' + vector_definition_from_array(b1_name, b))
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
            a1_name = "a{}".format(var_num)
            b1_name = "b{}".format(var_num)
            e1_name = "e{}".format(var_num)

            a = generate_vector_elements(i)
            b = generate_vector_elements(i)
            e = np.multiply(a, b)

            print('    ' + vector_definition_from_array(a1_name, a))
            print('    ' + vector_definition_from_array(b1_name, b))
            print('    ' + vector_definition_from_array(e1_name, e))
            print('    auto r{} = a{} * b{};'.format(var_num, var_num, var_num))
            print('    assert((r{} == e{}));'.format(var_num, var_num));
            
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

# Printing the main function with all the tests
print('')
print('int main() {')
print('    EXECUTE_TEST(test_vector_comparisons);')
#print('    EXECUTE_TEST(test_vector_deep_copies);')
print('    EXECUTE_TEST(test_vector_addition);')
print('    EXECUTE_TEST(test_vector_substraction);')
print('    EXECUTE_TEST(test_vector_length);')
print('    EXECUTE_TEST(test_vector_dotproduct);')
print('    EXECUTE_TEST(test_vector_multiplication);')
#print('    EXECUTE_TEST(test_matrix_indexing);')
#print('    EXECUTE_TEST(test_matrix_deep_copies);')
#print('    EXECUTE_TEST(test_matrix_comparisons);')
#print('    EXECUTE_TEST(test_matrix_addition);')
#print('    EXECUTE_TEST(test_matrix_multiplication);')
#print('    EXECUTE_TEST(test_matrix_vector_multiplication);')
print('}')
