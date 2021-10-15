#include <bits/stdc++.h>
using namespace std;

namespace SF {

class Unit {
public:
    Unit() = default;
};

struct ForceConvert { };
constexpr auto forceConvert = ForceConvert { };

namespace Detail {
    template <typename... Ts>
    struct DependentFalseImpl : false_type { };
}
template <typename... Ts>
constexpr bool DependentFalse = Detail::DependentFalseImpl<Ts...>::value;

static void assertImpl(bool x) {
    if (x)
        return;
#ifdef NDEBUG
    __builtin_unreachable();
#else
    abort();
#endif
}

#define SF_ASSERT assertImpl

template <typename T, typename UIn>
static auto assertConvert(UIn&& u) {
    using U = decay_t<UIn>;
    if constexpr (integral<T> && integral<U>) {
        T t = u;
        SF_ASSERT(cmp_equal(t, u));
        return t;
    } else {
        static_assert(DependentFalse<U>);
    }
}

template <integral TIn>
class FreeInteger {
public:
    using T = TIn;
    constexpr FreeInteger() : value_(0) { }
    template <typename U>
    constexpr FreeInteger(ForceConvert, U&& u)
        : value_(assertConvert<T>(forward<U>(u))) { }

    template <typename U>
    static constexpr auto from(U&& u) {
        return FreeInteger(forceConvert, forward<U>(u));
    }
    
    constexpr auto get() const {
        return value_;
    }

    constexpr auto operator<=>(const FreeInteger&) const = default;

    constexpr FreeInteger& operator++() {
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
    return FreeInteger<T>::from(t);
}

using Char = char;  // TODO
using String = string;  // TODO

namespace Detail {
    template <typename T>
    struct CFreeIntegerImpl : false_type { };
    template <integral T>
    struct CFreeIntegerImpl<FreeInteger<T>> : true_type { };
}
template <typename T>
concept CFreeInteger = Detail::CFreeIntegerImpl<T>::value;

template <CFreeInteger TIn, typename TagIn>
class Integer {
public:
    using T = TIn;
    using Tag = TagIn;

    Integer() = default;
    template <typename U>
    constexpr Integer(ForceConvert, U&& u)
        : value_(forceConvert, forward<U>(u)) { }

    template <typename U>
    static constexpr auto from(U&& u) {
        return Integer(forceConvert, forward<U>(u));
    }

    constexpr auto get() const {
        return value_;
    }
    constexpr auto get2() const {
        return get().get();
    }

    constexpr auto operator<=>(const Integer&) const = default;

    constexpr Integer& operator++() {
        ++value_;
        return *this;
    }
    constexpr auto operator++(int) {
        auto r = *this;
        ++*this;
        return r;
    }

    friend ostream& operator<<(ostream& out, const Integer& rhs) {
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
    Type operator""_ ## Suffix(unsigned long long int x) { \
        return Type::from(x); \
    }

template <typename... Ts>
class Vector {
    static_assert(DependentFalse<Ts...>);
};
template <typename T>
class Vector<T> : public vector<T> {
public:
    using Base = vector<T>;
    template <typename... Args>
    Vector(Args&&... args) : Base(forward<Args>(args)...) { }
};
template <CFreeInteger Index, typename T>
class Vector<Index, T> : public Vector<T> {
public:
    using Base = Vector<T>;
    template <typename... Args>
    Vector(Args&&... args) : Base(forward<Args>(args)...) { }
    template <typename... Args>
    Vector(Index n, Args&&... args) : Base(n.get(), forward<Args>(args)...) { }

    decltype(auto) operator[](Index i) const {
        return Base::operator[](i.get());
    }
    decltype(auto) operator[](Index i) {
        return Base::operator[](i.get());
    }

    void reserve(Index i) {
        Base::reserve(i.get());
    }
};
template <CInteger Index, typename T>
class Vector<Index, T> : public Vector<typename Index::T, T> {
public:
    using Base = Vector<typename Index::T, T>;
    template <typename... Args>
    Vector(Args&&... args) : Base(forward<Args>(args)...) { }
    template <typename... Args>
    Vector(Index n, Args&&... args) : Base(n.get(), forward<Args>(args)...) { }

    decltype(auto) operator[](Index i) const {
        return Base::operator[](i.get());
    }
    decltype(auto) operator[](Index i) {
        return Base::operator[](i.get());
    }

    void reserve(Index i) {
        Base::reserve(i.get());
    }
};

SF_INT(ExitStatus, Int, es);
SF_INT(Argc, Int, argc);

}  // namespace SF

static SF::ExitStatus sfUserMain(SF::Argc, SF::Vector<SF::Argc, SF::String>&&);

int main(int argcIn, char** argvIn) {
    using namespace SF;
    auto argc = Argc::from(argcIn);
    Vector<Argc, String> argv;
    argv.reserve(argc);
    for (Argc i; i < argc; i++)
        argv.emplace_back(argvIn[i.get2()]);
    return sfUserMain(argc, move(argv)).get2();
}
