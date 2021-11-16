#include <libmath.hh>

int main() {
    matf<2, 2> a = {1, 2, 
                    3, 4};
    matf<3, 3> b = {1, 2, 3,
                    4, 5, 6,
                    7, 8, 9};

#if defined(MISSMATCH_ADD)
    a + b;
#elif defined(MISSMATCH_SUB)
    a - b;
#elif defined(MISSMATCH_MUL)
    a * b;
#endif 
}
