/**
 * @file constants.hpp
 * @author Perry Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @date 2025-11-05
 */

#pragma once
#include <limits>
#include "type_traits"

namespace {

    template <typename T = float, typename = void>
    struct Epsilon;

    template <typename T>
    struct Epsilon<T, typename std::enable_if<!std::is_floating_point<T>::value>::type> {
        static float value() { return 1e-5f; }
    };

    template <> struct Epsilon<float>       { static float value()       { return 1e-5f; } };
    template <> struct Epsilon<double>      { static double value()      { return 1e-9; } };
    template <> struct Epsilon<long double> { static long double value() { return 1e-12L; } };
}

template <typename T = float>
inline T epsilon() { return Epsilon<T>::value(); }