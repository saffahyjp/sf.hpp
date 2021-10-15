#include "sf.hpp"

using namespace SF;

static ExitStatus sfUserMain(Argc argc, Vector<Argc, String>&& argv) {
    cout << "hello sf.hpp!" << endl;
    cout << "argc = " << argc << endl;
    for (Argc i; i < argc; i++)
        cout << "argv[" << i << "] = " << argv[i] << endl;
    return 0_es;
}
