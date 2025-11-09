/**
 * @file triangulation.hpp
 * @author Perry Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @date 2025-11-05
 */

#pragma once

#include "type.hpp"
#include "constants.hpp"

template <typename T>
struct Rect { 
    T x, y, w, h;
};

template <typename T>
struct Line {
    Vector2<T> p1, p2;

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    bool operator==(const Line& other) const {
        // Edges are undirected: (p1,p2) == (p2,p1)
        return (p1 == other.p1 && p2 == other.p2) ||
                (p1 == other.p2 && p2 == other.p1);
    }
};

template <typename T>
struct Triangle {
    Vector3<T> p1, p2, p3;

    template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    bool isInsideCircumcircle(const Vector2<T>& p) {
        //p become the origin (0,0)
        Vector2<T> a = {p1.x - p.x, p1.y - p.y};
        Vector2<T> b = {p2.x - p.x, p2.y - p.y};
        Vector2<T> c = {p3.x - p.x, p3.y - p.y};

        //geometric condition (squared distances from P to each vertex)
        T a2 = a.square_magnitude(); // ||p1'||^2
        T b2 = b.square_magnitude(); // ||p2'||^2
        T c2 = c.square_magnitude(); // ||p3'||^2

        T term1 = a.x * (b.y * c2 - c.y * b2); // contribution de la coordonnée x de A
        T term2 = - a.y * (b.x * c2 - c.x * b2); // contribution de la coordonnée y de A
        T term3 = a2 * b.cross(c); // contribution de la distance au carré de A (z) combinée à B et C // B' × C'
        T det = term1 + term2 + term3; // La somme (det) nous dit si P est au-dessus ou en dessous du plan → donc à l’intérieur ou à l’extérieur du cercle.

        return det < epsilon<T>();
    }


    bool isInside(Vector2<T> P) {
        const double abc = 0.5 * abs(p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));

        const double abp = 0.5 * abs(p1.x * (p2.y - P.y) + p2.x * (P.y - p1.y) + P.x * (p1.y - p2.y));
        const double bcp = 0.5 * abs(p2.x * (p3.y - P.y) + p3.x * (P.y - p2.y) + P.x * (p2.y - p3.y));
        const double cap = 0.5 * abs(p3.x * (p1.y - P.y) + p1.x * (P.y - p3.y) + P.x * (p3.y - p1.y));

        //if sum of abp, bcp, cap is equal to abc, then the point is inside the triangle, otherwise it's outside.
        return std::abs(abc - (abp + bcp + cap)) < epsilon<double>();
    }

};
