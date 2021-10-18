#pragma once
#include "../../include.hpp"

namespace SF {

template <typename Config>
concept CFreeIntegerConfig = requires {
    { Config::checkUnsignedOverflow() } -> same_as<bool>;
};

struct DefaultFreeIntegerConfig {
    static constexpr auto checkUnsignedOverflow() {
        return false;
    }
};

static_assert(CFreeIntegerConfig<DefaultFreeIntegerConfig>);

}  // namespace SF
