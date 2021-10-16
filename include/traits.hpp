#pragma once
#include "include.hpp"

namespace SF {

template <typename T, typename U>
concept CUndecay = is_same_v<decay_t<T>, U>;

namespace Detail {
    template <typename... Ts>
    struct DependentFalseImpl : false_type { };
}
template <typename... Ts>
constexpr bool DependentFalse = Detail::DependentFalseImpl<Ts...>::value;

}  // namespace SF