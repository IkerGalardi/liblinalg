#include <iostream>
#include <chrono>
#include <vector>

#include "libmath.hh"

int main(int argc, char** argv) {
    constexpr uint64_t vector_size = 100000;

    vecf<vector_size> a = {2, };
    vecf<vector_size> b = {1, };

    {
        std::cout << "vecf<" << vector_size << "> addition... " << std::flush;
        auto start_time = std::chrono::steady_clock::now();
        auto res = a + b;
        (void)res;
        auto end_time = std::chrono::steady_clock::now();
        std::cout << "Took " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count()
                             << "ns" << std::endl;
    }

    {
        std::cout << "vecf<" << vector_size << "> dot... " << std::flush;
        auto start_time = std::chrono::steady_clock::now();
        auto res = dot(a, b);
        (void)res;
        auto end_time = std::chrono::steady_clock::now();
        std::cout << "Took " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count()
                             << "ns" << std::endl;
    }

    {
        std::cout << "vecf<" << vector_size << "> multiplication... " << std::flush;
        auto start_time = std::chrono::steady_clock::now();
        auto res = 7 * b;
        (void)res;
        auto end_time = std::chrono::steady_clock::now();
        std::cout << "Took " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count()
                             << "ns" << std::endl;
    }
}
