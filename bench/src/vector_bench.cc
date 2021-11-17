#include <iostream>
#include <chrono>

#include "libmath.hh"

void test_addition(int64_t op_count) {

    std::cout << "2x2 vector addition... ";

    auto start_time = std::chrono::steady_clock::now();
    for(int i = 0; i < op_count; i++) {
        // TODO: generate vectors outside the loop
        vecf<2> a = {rand(), rand()};
        vecf<2> b = {rand(), rand()};

        auto res = a + b;
        (void)res;
    }
    auto end_time = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() 
            << " ns for " << op_count << " operations" << std::endl;
}


int main(int argc, char** argv) {
    constexpr uint64_t operation_count = 10;

    test_addition(operation_count);   
}
