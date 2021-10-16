#pragma once
#include "integer/all.hpp"
#include "container/all.hpp"

namespace SF {

class Unit {
public:
    Unit() = default;
};

using Char = char;  // TODO
using String = string;  // TODO

SF_INT(ExitStatus, Int, es);
SF_INT(Argc, Int, argc);

}  // namespace SF
