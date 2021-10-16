#pragma once
#include "include.hpp"

namespace SF {

enum class PerformanceLevel : int {
    Verbose,
    Debug,
    Release,
    Benchmark,
};

#ifdef SF_VERBOSE
    #ifdef SF_CURRENT_PERFORMANCE_LEVEL
        #error conflicting performance level
    #else
        #define SF_CURRENT_PERFORMANCE_LEVEL Verbose
    #endif
#endif
#ifdef SF_DEBUG
    #ifdef SF_CURRENT_PERFORMANCE_LEVEL
        #error conflicting performance level
    #else
        #define SF_CURRENT_PERFORMANCE_LEVEL Debug
    #endif
#endif
#ifdef SF_RELEASE
    #ifdef SF_CURRENT_PERFORMANCE_LEVEL
        #error conflicting performance level
    #else
        #define SF_CURRENT_PERFORMANCE_LEVEL Release
    #endif
#endif
#ifdef SF_BENCHMARK
    #ifdef SF_CURRENT_PERFORMANCE_LEVEL
        #error conflicting performance level
    #else
        #define SF_CURRENT_PERFORMANCE_LEVEL Benchmark
    #endif
#endif

#if defined(DEBUG) && !defined(SF_CURRENT_PERFORMANCE_LEVEL)
    #warning infer performance level from DEBUG macro
    #define SF_CURRENT_PERFORMANCE_LEVEL Debug
#endif
#if defined(NDEBUG) && !defined(SF_CURRENT_PERFORMANCE_LEVEL)
    #warning infer performance level from NDEBUG macro
    #define SF_CURRENT_PERFORMANCE_LEVEL Release
#endif
#ifndef SF_CURRENT_PERFORMANCE_LEVEL
    #warning performance level default to Release
    #define SF_CURRENT_PERFORMANCE_LEVEL Release
#endif

constexpr auto currentPerformanceLevel =
    PerformanceLevel::SF_CURRENT_PERFORMANCE_LEVEL;

template <PerformanceLevel MaxPerformanceLevel>
static void assertImpl(bool x) {
    if constexpr (currentPerformanceLevel > MaxPerformanceLevel) {
        if (!x)
            __builtin_unreachable();
    } else {
        if (x)
            return;
        abort();
    }
}

#define SF_FAST_ASSERT(x...) SF::assertImpl<SF::PerformanceLevel::Debug>(x)
#define SF_ASSERT(x...) SF::assertImpl<SF::PerformanceLevel::Release>(x)
#define SF_SLOW_ASSERT(x...) SF::assertImpl<SF::PerformanceLevel::Benchmark>(x)

template <typename T, typename UIn>
static auto assertConvert(UIn&& u) {
    using U = decay_t<UIn>;
    if constexpr (integral<T> && integral<U>) {
        T t = u;
        SF_FAST_ASSERT(cmp_equal(t, u));
        return t;
    } else {
        static_assert(DependentFalse<U>);
    }
}

}  // namespace SF
