import numpy as np
import random

OPERATIONS_PER_SIZE = 1

size_references = [2, 8, 16, 22, 32]

def generate_vector_elements_string(size):
    return vector_string_from_np_vector(np.random.randint(0, 9, size))

def vector_string_from_np_vector(vector):
    elements_string = np.array2string(vector, separator=',')
    elements_string = elements_string.replace('[', '{')
    elements_string = elements_string.replace(']', '}')

    return elements_string

def vectordef_string_from_np_vector(name, vector):
    vector_string = "vecf<{}> {}= ".format(len(vector), name)
    elems = vector_string_from_np_vector(vector)
    vector_string = vector_string + elems + ';'
    return vector_string

def random_vector_string(size):
    vector_string = "vecf<{}> = ".format(size)

    elements_string = generate_vector_elements_string(size)

    vector_string = vector_string + elements_string + ';'

    return vector_string

# Generate vector operations
var_num = 0
for i in size_references:
    # Addition operations
    print('void test_vector_addition() {')
    for j in range(OPERATIONS_PER_SIZE):
        v1 = np.random.randint(0, 9, i)
        v2 = np.random.randint(0, 9, i)
        res = v1 + v2

        print(vectordef_string_from_np_vector('a{}'.format(var_num), v1))
        print(vectordef_string_from_np_vector('b{}'.format(var_num), v2))
        print('auto r{} = a{} + b{};'.format(var_num, var_num, var_num))
        print(vectordef_string_from_np_vector('e{}'.format(var_num), res))
        print('assert(r{} == e{});'.format(var_num, var_num))
        print('')

        var_num = var_num + 1
    print('}')
    var_num = 0

    # Substraction operations
    print('void test_vector_substraction() {')
    for j in range(OPERATIONS_PER_SIZE):
        v1 = np.random.randint(0, 9, i)
        v2 = np.random.randint(0, 9, i)
        res = v1 - v2

        print(vectordef_string_from_np_vector('a{}'.format(var_num), v1))
        print(vectordef_string_from_np_vector('b{}'.format(var_num), v2))
        print('auto r{} = a{} - b{};'.format(var_num, var_num, var_num))
        print(vectordef_string_from_np_vector('e{}'.format(var_num), res))
        print('assert(r{} == e{});'.format(var_num, var_num))
        print('')

        var_num = var_num + 1
    var_num = 0

    print('void test_vector_dot() {')
    for j in range(OPERATIONS_PER_SIZE):
        v1 = np.random.randint(0, 9, i)
        v2 = np.random.randint(0, 9, i)
        res = v1 - v2

        print(vectordef_string_from_np_vector('a{}'.format(var_num), v1))
        print(vectordef_string_from_np_vector('b{}'.format(var_num), v2))
        print('auto r{} = dot(a{}, b{});'.format(var_num, var_num, var_num))
        print(vectordef_string_from_np_vector('e{}'.format(var_num), res))
        print('assert(r{} == e{});'.format(var_num, var_num))
        print('')
    var_num = 0

