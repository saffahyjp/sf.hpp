#pragma once
#include "include.hpp"

namespace SF {

static void assertImpl(bool x) {
    if (x)
        return;
#ifdef NDEBUG
    __builtin_unreachable();
#else
    abort();
#endif
}

#define SF_ASSERT SF::assertImpl

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

}  // namespace SF
