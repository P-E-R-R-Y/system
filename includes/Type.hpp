/**
 * @file type.hpp
 * @author Perry Chouteau
 * @brief Define common math and utility types
 * @version 0.3
 * @date 2025-02-19
 */

#pragma once

#if defined(_WIN32)
    #define OS "windows"
#elif defined(__APPLE__)
    #define OS "macos"
#else
    #define OS "linux"
#endif

// ---------- Vectors ----------
#include "Color.hpp"
#include "Constants.hpp"

#include "Matrix.hpp"

#include "Quaternion.hpp"
#include "Quaternion.hpp"

#include "Shape.hpp"

#include "std.hpp"

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"



