/**
 * @file Quaternion.hpp
 * @author Perry Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @date 2025-11-06
 */

#pragma once

#include "Vector3.hpp"

class Quaternion {
    public:
        Quaternion(): w(1), x(0), y(0), z(0) {}
        
        Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}
        ~Quaternion() {}

        static Quaternion identity() {
            return Quaternion(1, 0, 0, 0);
        }

        static Quaternion fromEulerAngles(float x, float y, float z) {
            Quaternion q;
            Vector3f half = {x / 2, y / 2, z / 2};

            q.w = std::cos(half.x) * std::cos(half.y) * std::cos(half.z) + std::sin(half.x) * std::sin(half.y) * std::sin(half.z);
            q.x = std::sin(half.x) * std::cos(half.y) * std::cos(half.z) - std::cos(half.x) * std::sin(half.y) * std::sin(half.z);
            q.y = std::cos(half.x) * std::sin(half.y) * std::cos(half.z) + std::sin(half.x) * std::cos(half.y) * std::sin(half.z);
            q.z = std::cos(half.x) * std::cos(half.y) * std::sin(half.z) - std::sin(half.x) * std::sin(half.y) * std::cos(half.z);
            return q;
        }

        /**
         * @brief fromAxisAngle will create a quaternion from an axis and an angle
         * 
         * @param angle 
         * @param axis 
         * @return Quaternion 
         */
        static Quaternion fromAxisAngle(float angle, Vector3f axis) {
            Quaternion q;
            float half = angle / 2; 

            q.w = std::cos(half);
            q.x = axis.x * std::sin(half);
            q.y = axis.y * std::sin(half);
            q.z = axis.z * std::sin(half);
            return q;
        }

        /**
         * @brief quaterninon representing the rotation from one vector to another
         * 
         * @param v1
         * @param v2
         * @return Quaternion
         */
        static Quaternion fromVectors(const Vector3f& v1, const Vector3f& v2, const Vector3f referenceUp = {0.0f, 1.0f, 0.0f}) {
            //!NEW
            // Normalize the vectors
            Vector3f u1 = v1.normalized();
            Vector3f u2 = v2.normalized();

            float dot = u1.dot(u2);

            //todo: check if this check is indeed working well with 180° rotation
            if (dot > 0.999999) {
                return Quaternion(1, 0, 0, 0);
            } else if (dot < -0.999999) {
                Vector3f axis = Vector3f{1, 0, 0}.cross(u1);
                if (axis.x == 0 && axis.y == 0 && axis.z == 0) {
                    axis = Vector3f{0, 1, 0}.cross(u1);
                }
                return Quaternion(0, axis.x, axis.y, axis.z);
            }

            Vector3f axis = u1.cross(u2);
            float u1Length = sqrt(u1.x * u1.x + u1.y * u1.y + u1.z * u1.z);
            float u2Length = sqrt(u2.x * u2.x + u2.y * u2.y + u2.z * u2.z);

            float w = sqrt((u1Length * u1Length) * (u2Length * u2Length)) + dot;
            Quaternion q(w, axis.x, axis.y, axis.z);
            return q;
        }

        Quaternion conjugate() const {
            return Quaternion(w, -x, -y, -z);
        }

        void normalize() {
            float magnitude = std::sqrt(w * w + x * x + y * y + z * z);
            if (magnitude == 0) {
                w = 1;
                x = 0;
                y = 0;
                z = 0;
            } else {
                w /= magnitude;
                x /= magnitude;
                y /= magnitude;
                z /= magnitude;
            }
        }

        void normalise() {
            float magnitude = std::sqrt(w * w + x * x + y * y + z * z);
            if (magnitude == 0) {
                w = 1;
                x = 0;
                y = 0;
                z = 0;
            } else {
                w /= magnitude;
                x /= magnitude;
                y /= magnitude;
                z /= magnitude;
            }
        }

        void enforceSign() {
            if (w < 0) {
                w = -w;
                x = -x;
                y = -y;
                z = -z;
            }
        }

        Vector3f rotate(Vector3f point, Vector3f center = {0, 0, 0}) const {
            Quaternion p(0, point.x - center.x, point.y - center.y, point.z - center.z);
            Quaternion q = (*this * p) * conjugate();
            return {q.x + center.x, q.y + center.y, q.z + center.z};
        }

        Quaternion operator*(const Quaternion& other) const {
            Quaternion q(
                w * other.w - x * other.x - y * other.y - z * other.z,
                w * other.x + x * other.w + y * other.z - z * other.y,
                w * other.y - x * other.z + y * other.w + z * other.x,
                w * other.z + x * other.y - y * other.x + z * other.w
            );
            return q;
        }

    float w, x, y, z;
};