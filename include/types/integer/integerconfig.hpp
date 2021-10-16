#pragma once
#include "../../include.hpp"

namespace SF {

template <typename Config>
concept CIntegerConfig = requires {
    { Config::allowSelfCompare() } -> same_as<bool>;
    { Config::allowPostIncrement() } -> same_as<bool>;
    { Config::allowPreIncrement() } -> same_as<bool>;
    { Config::allowStreamOutput() } -> same_as<bool>;
};

struct DefaultIntegerConfig {
    static constexpr auto allowSelfCompare() {
        return true;
    }
    static constexpr auto allowPostIncrement() {
        return true;
    }
    static constexpr auto allowPreIncrement() {
        return true;
    }
    static constexpr auto allowStreamOutput() {
        return true;
    }
};

static_assert(CIntegerConfig<DefaultIntegerConfig>);

}  // namespace SF
