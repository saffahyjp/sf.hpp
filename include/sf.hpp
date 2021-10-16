#pragma once
#include "include.hpp"
#include "types/all.hpp"

static SF::ExitStatus sfUserMain(SF::Argc, SF::Vector<SF::Argc, SF::String>&&);

#ifndef SF_NO_MAIN
int main(int argcIn, char** argvIn) {
    using namespace SF;
    auto argc = Argc::from(makeFreeInteger(argcIn));
    Vector<Argc, String> argv;
    argv.reserve(argc);
    for (Argc i; i < argc; i++)
        argv.emplace_back(argvIn[i.get2()]);
    return sfUserMain(argc, move(argv)).get2();
}
#endif
