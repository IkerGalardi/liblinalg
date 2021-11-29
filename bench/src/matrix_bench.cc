#include <iostream>
#include <chrono>
#include <vector>

#include "liblinalg.hh"

int main(int argc, char** argv) {
    constexpr uint64_t matrix_size = 700;

    matf<matrix_size, matrix_size> a = {2, };
    matf<matrix_size, matrix_size> b = {1, };

    {
        std::cout << "matf<" << matrix_size << ", " << matrix_size << "> addition... " << std::flush;
        auto start_time = std::chrono::steady_clock::now();
        auto res = a + b;
        (void)res;
        auto end_time = std::chrono::steady_clock::now();
        std::cout << "Took " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count()
                             << "ns" << std::endl;
    }

    {
        std::cout << "matf<" << matrix_size << ", " << matrix_size << "> multiplication... " << std::flush;
        auto start_time = std::chrono::steady_clock::now();
        auto res = a * b;
        (void)res;
        auto end_time = std::chrono::steady_clock::now();
        std::cout << "Took " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count()
                             << "ns" << std::endl;
    }
}
