/**
 * @file vector3.hpp
 * @author Perry Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @date 2025-11-04
 */

#pragma once

#include <cmath>

template <typename T>
struct Vector4 {
    T w{}, x{}, y{}, z{};

    // Comparison Operators
    template<typename = typename std::enable_if<std::is_convertible<decltype(std::declval<T>() == std::declval<T>()), bool>::value>::type>
    bool operator==(const Vector4& other) const { return w == other.w && x == other.x && y == other.y && z == other.z; }

    template<typename = typename std::enable_if<std::is_convertible<decltype(std::declval<T>() == std::declval<T>()), bool>::value>::type>
    bool operator!=(const Vector4& other) const { return !(*this == other); }

    // Arithmetic Operators
    template<typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Vector4 operator+(const Vector4& other) const { return Vector4{w + other.w, x + other.x, y + other.y, z + other.z}; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Vector4 operator-(const Vector4& other) const { return Vector4{w - other.w, x - other.x, y - other.y, z - other.z}; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Vector4 operator*(T scalar) const { return Vector4{w * scalar, x * scalar, y * scalar, z * scalar}; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Vector4 operator/(T scalar) const { return Vector4{w / scalar, x / scalar, y / scalar, z / scalar}; }

    // Compound Assignment Operators
    template<typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Vector4& operator+=(const Vector4& other) { w += other.w; x += other.x; y += other.y; z += other.z; return *this; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Vector4& operator-=(const Vector4& other) { w += other.w; x -= other.x; y -= other.y; z -= other.z; return *this; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Vector4& operator*=(T scalar) { w *= scalar; x *= scalar; y *= scalar; z *= scalar; return *this; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Vector4& operator/=(T scalar) { w /= scalar; x /= scalar; y /= scalar; z /= scalar; return *this; }

    // Unary Operators
    template<typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Vector4 operator-() { return Vector4{-w, -x, -y, -z}; }

    //methods
    template<typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    T dot(const Vector4& other) const { return w * other.w + x * other.x + y * other.y + z * other.z; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    T square_magnitude() const { return w*w + x*x + y*y + z*z; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    typename std::conditional<std::is_floating_point<T>::value, T, double>::type
    magnitude() const { return std::sqrt(square_magnitude()); }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    typename std::conditional<std::is_floating_point<T>::value, T, double>::type
    distance(const Vector4& other) const { return (*this - other).magnitude(); }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    Vector4 normalized() const {
        auto len = magnitude();

        if (len == 0) return {0, 0};
        return {T(w / len), T(x / len), T(y / len), T(z / len)};
    }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    void normalize() {
        double len = magnitude();

        if (len == 0) return;
        w /= len;
        x /= len;
        y /= len;
        z /= len;
    }

};

using Vector4u = Vector4<std::uint32_t>;
using Vector4i = Vector4<std::int32_t>;
using Vector4f = Vector4<double>;
