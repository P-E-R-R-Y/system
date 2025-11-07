/**
 * @file vector3.hpp
 * @author Perry Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @date 2025-11-04
 */

#pragma once

#include <cmath>

template <typename T>
struct Vector3 {
    T x{}, y{}, z{};

    // Comparison Operators
    template<typename = typename std::enable_if<std::is_convertible<decltype(std::declval<T>() == std::declval<T>()), bool>::value>::type>
    bool operator==(const Vector3& other) const { return x == other.x && y == other.y && z == other.z; }

    template<typename = typename std::enable_if<std::is_convertible<decltype(std::declval<T>() == std::declval<T>()), bool>::value>::type>
    bool operator!=(const Vector3& other) const { return !(*this == other); }

    // Arithmetic Operators
    template<typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Vector3 operator+(const Vector3& other) const { return Vector3{x + other.x, y + other.y, z + other.z}; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Vector3 operator-(const Vector3& other) const { return Vector3{x - other.x, y - other.y, z - other.z}; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Vector3 operator*(T scalar) const { return Vector3{x * scalar, y * scalar, z * scalar}; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Vector3 operator/(T scalar) const { return Vector3{x / scalar, y / scalar, z / scalar}; }

    // Compound Assignment Operators
    template<typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Vector3& operator+=(const Vector3& other) { x += other.x; y += other.y; z += other.z; return *this; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Vector3& operator-=(const Vector3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Vector3& operator*=(T scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Vector3& operator/=(T scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }

    // Unary Operators
    template<typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Vector3 operator-() { return Vector3{-x, -y, -z}; }

    //methods    
    template<typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    T dot(const Vector3& other) const { return x * other.x + y * other.y + z * other.z; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    Vector3 cross(const Vector3& other) const {
        return {
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        };
    }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    T square_magnitude() const { return x*x + y*y + z*z; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    typename std::conditional<std::is_floating_point<T>::value, T, double>::type 
    magnitude() const { return std::sqrt(square_magnitude()); }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    typename std::conditional<std::is_floating_point<T>::value, T, double>::type
    distance(const Vector3& other) const { return (*this - other).magnitude(); }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    double angle(const Vector3& other) const {
        double dot = double(this->dot(other));
        double cross = double(this->cross(other));

        return std::atan2(cross, dot); // result in radians, can be negative
    }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    Vector3 normalized() const {
        T len = magnitude();

        if (len == 0) return {0, 0, 0};
        return {T(x / len), T(y / len), T(z / len)};
    }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    void normalize() {
        double len = magnitude();

        if (len == 0) return;
        x /= len;
        y /= len;
        z /= len;
    }

};

using Vector3u = Vector3<std::uint32_t>;
using Vector3i = Vector3<std::int32_t>;
using Vector3f = Vector3<double>;
