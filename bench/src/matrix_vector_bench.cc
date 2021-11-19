
#include <iostream>
#include <chrono>
#include <vector>

#include "libmath.hh"

int main(int argc, char** argv) {
    constexpr uint64_t size = 700;

    matf<size, size> a = {2, };
    vecf<size> b = {1, };

    {
        std::cout << "matf<" << size << ", " << size << "> * vecf<" << size << ">... " << std::flush;
        auto start_time = std::chrono::steady_clock::now();
        auto res = a * b;
        (void)res;
        auto end_time = std::chrono::steady_clock::now();
        std::cout << "Took " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count()
                             << "ns" << std::endl;
    }

    {
        std::cout << "vecf<" << size << "> * matf<" << size << ", " << size << ">..." << std::flush;
        auto start_time = std::chrono::steady_clock::now();
        auto res = a * b;
        (void)res;
        auto end_time = std::chrono::steady_clock::now();
        std::cout << "Took " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count()
                             << "ns" << std::endl;
    }
}
