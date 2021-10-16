#include "sf.hpp"
using namespace SF;

static ExitStatus sfUserMain(Argc argc, Vector<Argc, String>&& argv) {
    auto one = makeFreeInteger(1), two = makeFreeInteger(2);
    SF_TEST(one + one == two);
    cerr << "All tests passed" << endl;
    return 0_es;
}
