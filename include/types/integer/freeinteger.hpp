#pragma once
#include "../../include.hpp"
#include "../../traits.hpp"
#include "../../assert.hpp"
#include "../tags.hpp"
#include "freeintegerconfig.hpp"

namespace SF {

template <integral T>
static auto makeFreeInteger(T);

template <integral T, integral U>
static constexpr auto safePlus(T t, U u)
    -> optional<decay_t<decltype(t + u)>>
{
    using R = decay_t<decltype(t + u)>;
    using Return = optional<R>;
    if constexpr (is_same_v<T, U>) {
        if constexpr (is_signed_v<T>) {
            if (t > 0 && u > 0 && t > numeric_limits<T>::max() - u)
                return nullopt;
            if (t < 0 && u < 0 && t < numeric_limits<T>::min() - u)
                return nullopt;
        } else {  // is_unsigned_v<T>
            if (t > numeric_limits<T>::max() - u)
                return nullopt;
        }
    } else {  // !is_same_v<T, U>
        static_assert(DependentFalse<T, U>);
    }
    return t + u;
}

template <integral TIn, CFreeIntegerConfig Config = DefaultFreeIntegerConfig>
class FreeInteger {
public:
    using T = TIn;
    static constexpr bool checkOverflow
        = is_signed_v<TIn> || Config::checkUnsignedOverflow();
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

    // TODO: support operator+(const FreeInteger<U>&) const

    constexpr auto operator+(const FreeInteger& rhs) const {
        auto l = get(), r = rhs.get();
        auto ret = makeFreeInteger(l + r);
        if constexpr (checkOverflow)
            SF_FAST_ASSERT(ret.get() == safePlus(l, r));
        return ret;
    }
    constexpr auto operator-(const FreeInteger& rhs) const {
        auto l = get(), r = rhs.get();
        auto ret = makeFreeInteger(l - r);
        if constexpr (checkOverflow)
            SF_FAST_ASSERT(ret.get() == safeMinus(l, r));
        return ret;
    }
    constexpr auto operator*(const FreeInteger& rhs) const {
        auto l = get(), r = rhs.get();
        auto ret = makeFreeInteger(l * r);
        if constexpr (checkOverflow)
            SF_FAST_ASSERT(ret.get() == safeMultiplies(l, r));
        return ret;
    }
    constexpr auto operator/(const FreeInteger& rhs) const {
        auto l = get(), r = rhs.get();
        auto ret = makeFreeInteger(l / r);
        if constexpr (checkOverflow)
            SF_FAST_ASSERT(ret.get() == safeDivides(l, r));
        return ret;
    }

    template <typename U>
    constexpr decltype(auto) operator+=(U&& u) {
        return *this = *this + forward<U>(u);
    }
    template <typename U>
    constexpr decltype(auto) operator-=(U&& u) {
        return *this = *this - forward<U>(u);
    }
    template <typename U>
    constexpr decltype(auto) operator*=(U&& u) {
        return *this = *this * forward<U>(u);
    }
    template <typename U>
    constexpr decltype(auto) operator/=(U&& u) {
        return *this = *this / forward<U>(u);
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
