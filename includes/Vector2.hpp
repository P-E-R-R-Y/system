/**
 * @file vector2.hpp
 * @author Perry Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @date 2025-11-04
 */

#pragma once

#include <cmath>

template <typename T>
struct Vector2 {
    T x{}, y{};

    // Comparison Operators
    template<typename = typename std::enable_if<std::is_convertible<decltype(std::declval<T>() == std::declval<T>()), bool>::value>::type>
    bool operator==(const Vector2& other) const { return x == other.x && y == other.y; }

    template<typename = typename std::enable_if<std::is_convertible<decltype(std::declval<T>() == std::declval<T>()), bool>::value>::type>
    bool operator!=(const Vector2& other) const { return !(*this == other); }

    // Arithmetic Operators
    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    Vector2 operator+(const Vector2& other) const { return Vector2{x + other.x, y + other.y}; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    Vector2 operator-(const Vector2& other) const { return Vector2{x - other.x, y - other.y}; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    Vector2 operator*(T scalar) const { return Vector2{x * scalar, y * scalar}; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    Vector2 operator/(T scalar) const { return Vector2{x / scalar, y / scalar}; }

    // Compound Assignment Operators
    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    Vector2& operator+=(const Vector2& other) { x += other.x; y += other.y; return *this; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    Vector2& operator-=(const Vector2& other) { x -= other.x; y -= other.y; return *this; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    Vector2& operator*=(T scalar) { x *= scalar; y *= scalar; return *this; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    Vector2& operator/=(T scalar) { x /= scalar; y /= scalar; return *this; }

    // Unary Operators
    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    Vector2 operator-() { return Vector2{-x, -y}; }

    //methods    
    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    T dot(const Vector2& other) const { return x * other.x + y * other.y; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    T cross(const Vector2& other) const { return x * other.y - y * other.x; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    T square_magnitude() const { return x*x + y*y; }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    typename std::conditional<std::is_floating_point<T>::value, T, double>::type 
    magnitude() const { return std::sqrt(square_magnitude()); }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    typename std::conditional<std::is_floating_point<T>::value, T, double>::type
    distance(const Vector2& other) const { return (*this - other).magnitude(); }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    double angle(const Vector2& other) const {
        double dot = double(this->dot(other));
        double cross = double(this->cross(other));

        return std::atan2(cross, dot); // result in radians, can be negative
    }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    Vector2 normalized() const {
        T len = magnitude();
        if (len == 0) return {0, 0};
        return {T(x / len), T(y / len)};
    }

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    void normalize() {
        double len = magnitude();

        if (len == 0) return;
        x /= len;
        y /= len;
    }

};

// ---------- Aliases ----------
using Vector2u = Vector2<std::uint32_t>;
using Vector2i = Vector2<std::int32_t>;
using Vector2f = Vector2<double>;
