#include "sf.hpp"
using namespace SF;

static ExitStatus sfUserMain(Argc argc, Vector<Argc, String>&& argv) {
    Int zero;
    auto one = makeFreeInteger(1), two = makeFreeInteger(2);
    SF_TEST(zero + one == one);
    SF_TEST(two + zero == two);
    SF_TEST(one + one == two);

    auto min = makeFreeInteger(INT_MIN), max = makeFreeInteger(INT_MAX);
    SF_EXPECT_FAILURE(one + max);
    SF_TEST(min + max + one == zero);

    cerr << "All tests passed" << endl;
    return 0_es;
}
