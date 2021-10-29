#pragma once 


template<size_t size>
struct alignas(16) vecf {
    float data[size];
};
