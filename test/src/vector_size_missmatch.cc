#include <liblinalg.hh>

int main() {
    vecf<3> a = {1, 2, 3};
    vecf<4> b = {1, 2, 3, 4};

#if defined(MISSMATCH_ADD)
    a + b;
#elif defined(MISSMATCH_SUB)
    a - b;
#elif defined(MISSMATCH_DOT)
    dot(a, b);
#endif 
}
