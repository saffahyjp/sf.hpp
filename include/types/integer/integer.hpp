#pragma once
#include "freeinteger.hpp"
#include "integerconfig.hpp"

namespace SF {

template <
    CFreeInteger TIn,
    typename TagIn,
    CIntegerConfig Config = DefaultIntegerConfig
>
class Integer {
public:
    using T = TIn;
    using Tag = TagIn;

    Integer() = default;
    template <typename U>
    constexpr Integer(ForceConvert, U&& u)
        : value_(forceConvert, forward<U>(u)) { }

    template <typename U>
    static constexpr auto forceFrom(U&& u) {
        return Integer(forceConvert, forward<U>(u));
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
    constexpr auto get2() const {
        return get().get();
    }

    constexpr auto operator<=>(const Integer&) const = delete;
    constexpr auto operator<=>(const Integer&) const
        requires (Config::allowSelfCompare()) = default;

    constexpr auto operator++() = delete;
    constexpr decltype(auto) operator++()
        requires (Config::allowPostIncrement())
    {
        ++value_;
        return *this;
    }
    constexpr auto operator++(int) = delete;
    constexpr auto operator++(int) requires (Config::allowPreIncrement()) {
        auto r = *this;
        ++*this;
        return r;
    }

    friend decltype(auto) operator<<(ostream& out, const Integer& rhs) {
        static_assert(Config::allowStreamOutput());
        return out << rhs.get();
    }
private:
    T value_;
};

namespace Detail {
    template <typename T>
    struct CIntegerImpl : false_type { };
    template <CFreeInteger T, typename Tag>
    struct CIntegerImpl<Integer<T, Tag>> : true_type { };
}
template <typename T>
concept CInteger = Detail::CIntegerImpl<T>::value;

#define SF_INT(Type, Underlying, Suffix) \
    struct Type ## Tag { }; \
    using Type = Integer<Underlying, Type ## Tag>; \
    auto operator""_ ## Suffix(unsigned long long int x) { \
        return Type::forceFrom(x); \
    }

}  // namespace SF
