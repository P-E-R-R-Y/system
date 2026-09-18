/**
 * @file Quaternion.hpp
 * @author Perry Chouteau (perry.chouteau@outlook.com)
 * @brief Une rotation, sans blocage de cardan.
 * @date 2025-11-06
 *
 * @addtogroup system
 * @{
 */

#pragma once

#include "Vector3.hpp"

/**
 * @class Quaternion
 * @brief Une rotation dans l'espace, parametree par son scalaire.
 *
 * Templatee comme Vector3 et Matrix : le quaternion et le vecteur qu'il
 * tourne partagent le meme T, donc rotate() ne retrecit jamais son point.
 */
template <typename T>
class Quaternion {

    public:
        Quaternion() : w(1), x(0), y(0), z(0) {}
        Quaternion(T w, T x, T y, T z) : w(w), x(x), y(y), z(z) {}

        static Quaternion identity() { return Quaternion(1, 0, 0, 0); }

        static Quaternion fromEulerAngles(T x, T y, T z) {
            Quaternion q;
            const Vector3<T> half = {x / 2, y / 2, z / 2};

            q.w = std::cos(half.x) * std::cos(half.y) * std::cos(half.z) + std::sin(half.x) * std::sin(half.y) * std::sin(half.z);
            q.x = std::sin(half.x) * std::cos(half.y) * std::cos(half.z) - std::cos(half.x) * std::sin(half.y) * std::sin(half.z);
            q.y = std::cos(half.x) * std::sin(half.y) * std::cos(half.z) + std::sin(half.x) * std::cos(half.y) * std::sin(half.z);
            q.z = std::cos(half.x) * std::cos(half.y) * std::sin(half.z) - std::sin(half.x) * std::sin(half.y) * std::cos(half.z);
            return q;
        }

        /**
         * @brief Une rotation d'un angle autour d'un axe.
         *
         * @param angle en radians
         * @param axis  suppose unitaire
         */
        static Quaternion fromAxisAngle(T angle, Vector3<T> axis) {
            Quaternion q;
            const T half = angle / 2;

            q.w = std::cos(half);
            q.x = axis.x * std::sin(half);
            q.y = axis.y * std::sin(half);
            q.z = axis.z * std::sin(half);
            return q;
        }

        /**
         * @brief La rotation qui amene v1 sur v2.
         */
        static Quaternion fromVectors(const Vector3<T> &v1, const Vector3<T> &v2,
                                      const Vector3<T> referenceUp = {0, 1, 0}) {
            (void)referenceUp;

            const Vector3<T> u1 = v1.normalized();
            const Vector3<T> u2 = v2.normalized();
            const T dot = u1.dot(u2);

            //todo: check if this check is indeed working well with 180 rotation
            if (dot > T(0.999999))
                return Quaternion(1, 0, 0, 0);

            if (dot < T(-0.999999)) {
                Vector3<T> axis = Vector3<T>{1, 0, 0}.cross(u1);

                if (axis.x == 0 && axis.y == 0 && axis.z == 0)
                    axis = Vector3<T>{0, 1, 0}.cross(u1);

                Quaternion q(0, axis.x, axis.y, axis.z);

                q.normalize();
                return q;
            }

            const Vector3<T> axis = u1.cross(u2);
            const T u1Length = u1.magnitude();
            const T u2Length = u2.magnitude();
            const T w = std::sqrt((u1Length * u1Length) * (u2Length * u2Length)) + dot;
            Quaternion q(w, axis.x, axis.y, axis.z);

            /* La construction rend un quaternion de norme quelconque. Non
             * normalise, rotate() mettrait le point a l'echelle |q|^2. */
            q.normalize();
            return q;
        }

        Quaternion conjugate() const { return Quaternion(w, -x, -y, -z); }

        /** @brief Le ramene sur la sphere unite. Un quaternion nul devient l'identite. */
        void normalize() {
            const T magnitude = std::sqrt(w * w + x * x + y * y + z * z);

            if (magnitude == 0) {
                w = 1; x = 0; y = 0; z = 0;
                return;
            }
            w /= magnitude; x /= magnitude; y /= magnitude; z /= magnitude;
        }

        /**
         * @brief Choisit la representation a w positif.
         *
         * q et -q designent la MEME rotation. Fixer le signe rend deux
         * orientations comparables composante par composante.
         */
        void enforceSign() {
            if (w < 0) {
                w = -w; x = -x; y = -y; z = -z;
            }
        }

        /** @brief Tourne un point autour d'un centre. */
        Vector3<T> rotate(Vector3<T> point, Vector3<T> center = {0, 0, 0}) const {
            const Quaternion p(0, point.x - center.x, point.y - center.y, point.z - center.z);
            const Quaternion q = (*this * p) * conjugate();

            return {q.x + center.x, q.y + center.y, q.z + center.z};
        }

        /** @brief Compose deux rotations. L'ordre compte. */
        Quaternion operator*(const Quaternion &other) const {
            return Quaternion(
                w * other.w - x * other.x - y * other.y - z * other.z,
                w * other.x + x * other.w + y * other.z - z * other.y,
                w * other.y - x * other.z + y * other.w + z * other.x,
                w * other.z + x * other.y - y * other.x + z * other.w
            );
        }

        T w, x, y, z;
};

using Quaternionf = Quaternion<double>;

/** @} */
