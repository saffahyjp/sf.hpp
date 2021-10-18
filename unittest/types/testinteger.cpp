#include "sf.hpp"
using namespace SF;

static ExitStatus sfUserMain(Argc argc, Vector<Argc, String>&& argv) {
    const Int zero;
    const auto one = makeFreeInteger(1), two = makeFreeInteger(2);
    SF_TEST(zero + one == one);
    SF_TEST(two + zero == two);
    SF_TEST(one + one == two);

    const auto min = makeFreeInteger(INT_MIN), max = makeFreeInteger(INT_MAX);
    SF_EXPECT_FAILURE(one + max);
    SF_TEST(min + max + one == zero);

    Int a;
    SF_TEST(a == zero);
    SF_TEST((a += one) == one);
    SF_TEST((a += one) == two);
    SF_EXPECT_FAILURE(a += max);

    cerr << "All tests passed" << endl;
    return 0_es;
}
