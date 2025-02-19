/**
 * @file type.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief define types 
 * @version 0.1
 * @date 2025-02-19
 */

#ifndef TYPE_HPP_
    #define TYPE_HPP_

    #ifdef _WIN32
        #define OS "Windows"
    #elif __APPLE__
        #define OS "macOS"
        #include <sys/types.h>
    #else //if __linux__
        #define OS "Linux"
    #endif

#include <string>
#include <iostream>
#include <vector>

namespace type {

    //#define __uint8_t unsigned char
    //#define __int8_t char
    //#define __uint32_t unsigned int
    //#define __int32_t int

    template <typename T>
    struct __v2_t {
        T x;
        T y;
    };

    template <typename T>
    struct __v3_t {
        T x;
        T y;
        T z;
    };

    template <typename T>
    struct __v4_t {
        T x;
        T y;
        T w;
        T h;
    };

    #define __v2u_t __v2_t<__uint32_t>
    #define __v2i_t __v2_t<__int32_t>
    #define __v2f_t __v2_t<float>
    #define __v2d_t __v2_t<double>

    #define __v3u_t __v3_t<__uint32_t>
    #define __v3i_t __v3_t<__int32_t>
    #define __v3f_t __v3_t<float>
    #define __v3d_t __v3_t<double>

    #define __v4u_t __v4_t<__uint32_t>
    #define __v4i_t __v4_t<__int32_t>
    #define __v4f_t __v4_t<float>
    #define __v4d_t __v4_t<double>

    typedef struct __color_s {
        __uint8_t r;
        __uint8_t g;
        __uint8_t b;
        __uint8_t a;
    } __color_t;

    typedef struct _quaternion_s {
        double w;
        double x;
        double y;
        double z;
    } __quaternion_t;

} // namespace type

#endif /* !TYPE_HPP_ */