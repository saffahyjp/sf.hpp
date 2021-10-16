#pragma once
#include "../integer/all.hpp"

namespace SF {

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

}  // namespace SF
