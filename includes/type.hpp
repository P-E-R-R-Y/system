/**
 * @file type.hpp
 * @author Perry Chouteau
 * @brief Define common math and utility types
 * @version 0.3
 * @date 2025-02-19
 */

#pragma once

#include <cstdint>
#include <string>

#if defined(_WIN32)
    #define OS "windows"
#elif defined(__APPLE__)
    #define OS "macos"
#else
    #define OS "linux"
#endif

// ---------- Vectors ----------
template <typename T>
struct Vector2 {
    T x{};
    T y{};
};

template <typename T>
struct Vector3 {
    T x{};
    T y{};
    T z{};
};

template <typename T>
struct Vector4 {
    T x{};
    T y{};
    T w{};
    T h{};
};

// ---------- Aliases ----------
using Vector2u = Vector2<std::uint32_t>;
using Vector2i = Vector2<std::int32_t>;
using Vector2f = Vector2<double>;

using Vector3u = Vector3<std::uint32_t>;
using Vector3i = Vector3<std::int32_t>;
using Vector3f = Vector3<double>;

using Vector4u = Vector4<std::uint32_t>;
using Vector4i = Vector4<std::int32_t>;
using Vector4f = Vector4<double>;

// ---------- Color ----------
struct Color {
    std::uint8_t r{};
    std::uint8_t g{};
    std::uint8_t b{};
    std::uint8_t a{};
};

// ---------- Quaternion ----------
struct Quaternion {
    double w{};
    double x{};
    double y{};
    double z{};
};