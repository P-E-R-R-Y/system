/**
 * @file matrices.hpp
 * @author Perry Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @date 2025-11-04
 */

#pragma once

#include <cmath>

#include <type_traits>
#include <cstddef>
#include <cmath>

template <
    typename T, std::size_t ROWS, std::size_t COLS,
    typename = typename std::enable_if<ROWS >=  1 && COLS >=  1>::type
>
struct Matrix {
    T data[ROWS][COLS]{};

    // Statics
    template <typename = typename std::enable_if<std::is_arithmetic<T>::value && ROWS == COLS>::type>
    static Matrix identity() {
        Matrix mat{};
        for (std::size_t i = 0; i < ROWS; ++i) {
                mat.data[i][i] = T(1);
        }
        return mat;
    }

    static Matrix zero() {
        return Matrix{};
    }

    template<typename = typename std::enable_if<ROWS == COLS>::type>
    static Matrix diagonal(const T (&values)[ROWS]) {
        Matrix mat{};
        for (std::size_t i = 0; i < ROWS; ++i)
            mat.data[i][i] = values[i];
        return mat;
    }

    // Access operator
    T& operator()(std::size_t i, std::size_t j) { return data[i][j]; }
    const T& operator()(std::size_t i, std::size_t j) const { return data[i][j]; }

    // Unary operators
    Matrix operator-() const {
        Matrix result{};
        for (std::size_t i = 0; i < ROWS; ++i)
            for (std::size_t j = 0; j < COLS; ++j)
                result.data[i][j] = -data[i][j];
        return result;
    }

    // Arythmetic operator
    Matrix operator+(const Matrix& other) const {
        Matrix result{};
        for (std::size_t i = 0; i < ROWS; ++i)
            for (std::size_t j = 0; j < COLS; ++j)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

     Matrix operator-(const Matrix& other) const {
        Matrix result{};
        for (std::size_t i = 0; i < ROWS; ++i)
            for (std::size_t j = 0; j < COLS; ++j)
                result.data[i][j] = data[i][j] - other.data[i][j];
        return result;
    }
    
    //
    template <std::size_t OTHER_COLS>
    Matrix<T, ROWS, OTHER_COLS> operator*(const Matrix<T, COLS, OTHER_COLS>& other) const {
        Matrix<T, ROWS, OTHER_COLS> result{};
        for (std::size_t i = 0; i < ROWS; ++i)
            for (std::size_t j = 0; j < OTHER_COLS; ++j)
                for (std::size_t k = 0; k < COLS; ++k)
                    result.data[i][j] += data[i][k] * other.data[k][j];
        return result;
    }


    Matrix& operator+=(const Matrix& other) {
        for (std::size_t i = 0; i < ROWS; ++i)
            for (std::size_t j = 0; j < COLS; ++j)
                data[i][j] += other.data[i][j];
        return *this;
    }

    Matrix operator/(T scalar) const {
        Matrix result{};
        for (std::size_t i = 0; i < ROWS; ++i)
            for (std::size_t j = 0; j < COLS; ++j)
                result.data[i][j] = data[i][j] / scalar;
        return result;
    }

    Matrix& operator*=(T scalar) {
        for (std::size_t i = 0; i < ROWS; ++i)
            for (std::size_t j = 0; j < COLS; ++j)
                data[i][j] *= scalar;
        return *this;
    }

    Matrix& operator/=(T scalar) {
        for (std::size_t i = 0; i < ROWS; ++i)
            for (std::size_t j = 0; j < COLS; ++j)
                data[i][j] /= scalar;
        return *this;
    }

        Matrix& operator-=(const Matrix& other) {
        for (std::size_t i = 0; i < ROWS; ++i)
            for (std::size_t j = 0; j < COLS; ++j)
                data[i][j] -= other.data[i][j];
        return *this;
    }

    Matrix operator*(T scalar) const {
        Matrix result{};
        for (std::size_t i = 0; i < ROWS; ++i)
            for (std::size_t j = 0; j < COLS; ++j)
                result.data[i][j] = data[i][j] * scalar;
        return result;
    }

    Matrix transpose() const {
        Matrix result{};
        for (std::size_t i = 0; i < ROWS; ++i)
            for (std::size_t j = 0; j < COLS; ++j)
                result.data[j][i] = data[i][j];
        return result;
    }

};