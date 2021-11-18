#include <iostream>
#include <chrono>
#include <vector>

#include "libmath.hh"

void synthetic_tests(int64_t op_count) {

    std::cout << "2x2 vector addition... " << std::flush;

    // Generate random vectors
    std::vector<vecf<2>> random;
    for(int i = 0; i < 100; i++) {
        random.push_back({static_cast<float>(rand()), static_cast<float>(rand())});
    }

    vecf<2>* tostore = static_cast<vecf<2>*>(malloc(op_count * sizeof(vecf<2>)));

    auto start_time = std::chrono::steady_clock::now();
    for(int i = 0; i < op_count; i++) {
        auto a = random[i % 100] + random[(i + 1) % 100];
        tostore[i] = a;
    }
    auto end_time = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() 
            << " ns for " << op_count << " operations" << std::endl;
}


int main(int argc, char** argv) {
    constexpr uint64_t operation_count = 1000000000;

    synthetic_tests(operation_count);   
}
