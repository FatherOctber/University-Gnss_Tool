#include "iri_adapter.h"

extern void hello_(int* ii, float* ff);

extern void test_hello(int a, float b)
{
    int this_a = a;
    float this_b = b;
    hello_(&a, &b);
    return 0;
}
