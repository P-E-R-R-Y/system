/**
 * @file constants.hpp
 * @author Perry Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @date 2025-11-05
 */

#pragma once

template<typename T>
struct Epsilon {};

template<>
struct Epsilon<float> {
    static constexpr float value = 1e-5f;
};

template<>
struct Epsilon<double> {
    static constexpr double value = 1e-9;
};

template<>
struct Epsilon<long double> {
    static constexpr long double value = 1e-12L;
};

template<typename T = float>
constexpr T epsilon_v = Epsilon<T>::value;

constexpr double epsilonf = epsilon_v<float>;
constexpr double epsilond = epsilon_v<double>;
constexpr long double epsilonl = epsilon_v<long double>;
