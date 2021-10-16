#pragma once
#include "../../include.hpp"
#include "../../traits.hpp"
#include "../../assert.hpp"
#include "../tags.hpp"

namespace SF {

template <integral TIn>
class FreeInteger {
public:
    using T = TIn;
    constexpr FreeInteger() : value_(0) { }
    template <typename U>
    constexpr FreeInteger(ForceConvert, U&& u)
        : value_(assertConvert<T>(forward<U>(u))) { }
    template <CUndecay<FreeInteger> U>
    constexpr FreeInteger(ForceConvert, U&& u)
        : FreeInteger(forward<U>(u)) { }

    template <typename U>
    static constexpr auto forceFrom(U&& u) {
        return FreeInteger(forceConvert, forward<U>(u));
    }
    template <CUndecay<T> U>
    static constexpr auto from(U&& u) {
        return forceFrom(forward<U>(u));
    }
    template <typename U>
    static constexpr auto from(U&&) = delete;
    
    constexpr auto get() const {
        return value_;
    }

    constexpr auto operator<=>(const FreeInteger&) const = default;

    constexpr decltype(auto) operator++() {
        ++value_;
        return *this;
    }
    constexpr auto operator++(int) {
        auto r = *this;
        ++*this;
        return r;
    }

    friend ostream& operator<<(ostream& out, const FreeInteger& rhs) {
        return out << rhs.get();
    }
private:
    T value_;
};
using Int = FreeInteger<int>;

template <integral T>
static auto makeFreeInteger(T t) {
    return FreeInteger<decay_t<T>>::from(t);
}

namespace Detail {
    template <typename T>
    struct CFreeIntegerImpl : false_type { };
    template <integral T>
    struct CFreeIntegerImpl<FreeInteger<T>> : true_type { };
}
template <typename T>
concept CFreeInteger = Detail::CFreeIntegerImpl<T>::value;

}  // namespace SF
