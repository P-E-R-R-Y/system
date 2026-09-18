#include <gtest/gtest.h>
#include "Quaternion.hpp"
#include "Constants.hpp"
#include <cmath>

TEST(QuaternionTest, DefaultInitialization) {
    Quaternionf q;
    EXPECT_FLOAT_EQ(q.w, 1.0f);
    EXPECT_FLOAT_EQ(q.x, 0.0f);
    EXPECT_FLOAT_EQ(q.y, 0.0f);
    EXPECT_FLOAT_EQ(q.z, 0.0f);
}

TEST(QuaternionTest, CustomInitialization) {
    Quaternionf q(0.5f, 1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(q.w, 0.5f);
    EXPECT_FLOAT_EQ(q.x, 1.0f);
    EXPECT_FLOAT_EQ(q.y, 2.0f);
    EXPECT_FLOAT_EQ(q.z, 3.0f);
}

TEST(QuaternionTest, IdentityQuaternion) {
    Quaternionf q = Quaternionf::identity();
    EXPECT_FLOAT_EQ(q.w, 1.0f);
    EXPECT_FLOAT_EQ(q.x, 0.0f);
    EXPECT_FLOAT_EQ(q.y, 0.0f);
    EXPECT_FLOAT_EQ(q.z, 0.0f);
}

TEST(QuaternionTest, FromAxisAngle) {
    Vector3f axis{0, 0, 1};
    float angle = static_cast<float>(M_PI) / 2.0f;  // 90 degrees

    Quaternionf q = Quaternionf::fromAxisAngle(angle, axis);
    q.normalize();

    EXPECT_NEAR(q.w, std::cos(angle / 2.0f), epsilonf);
    EXPECT_NEAR(q.x, 0.0f, epsilonf);
    EXPECT_NEAR(q.y, 0.0f, epsilonf);
    EXPECT_NEAR(q.z, std::sin(angle / 2.0f), epsilonf);
}

TEST(QuaternionTest, Normalize) {
    Quaternionf q(0, 3, 0, 4);
    q.normalize();

    float magnitude = std::sqrt(3*3 + 4*4);
    EXPECT_NEAR(q.w, 0.0f, epsilonf);
    EXPECT_NEAR(q.x, 3/magnitude, epsilonf);
    EXPECT_NEAR(q.y, 0.0f, epsilonf);
    EXPECT_NEAR(q.z, 4/magnitude, epsilonf);
}

TEST(QuaternionTest, Conjugate) {
    Quaternionf q(1, 2, 3, 4);
    Quaternionf c = q.conjugate();

    EXPECT_FLOAT_EQ(c.w, 1.0f);
    EXPECT_FLOAT_EQ(c.x, -2.0f);
    EXPECT_FLOAT_EQ(c.y, -3.0f);
    EXPECT_FLOAT_EQ(c.z, -4.0f);
}

TEST(QuaternionTest, Multiply) {
    Quaternionf q1(1, 0, 1, 0);
    Quaternionf q2(1, 0.5f, 0.5f, 0.75f);

    Quaternionf result = q1 * q2;

    EXPECT_NEAR(result.w, 0.5f, epsilonf);
    EXPECT_NEAR(result.x, 1.25f, epsilonf);
    EXPECT_NEAR(result.y, 1.5f, epsilonf);
    EXPECT_NEAR(result.z, 0.25f, epsilonf);
}

TEST(QuaternionTest, RotateVector90DegAroundZ) {
    Quaternionf q = Quaternionf::fromAxisAngle(static_cast<float>(M_PI) / 2.0f, {0, 0, 1});
    Vector3f point(1, 0, 0);

    Vector3f rotated = q.rotate(point);
    EXPECT_NEAR(rotated.x, 0.0f, epsilonf);
    EXPECT_NEAR(rotated.y, 1.0f, epsilonf);
    EXPECT_NEAR(rotated.z, 0.0f, epsilonf);
}

TEST(QuaternionTest, FromVectorsParallel) {
    Vector3f v1(1, 0, 0);
    Vector3f v2(1, 0, 0);

    Quaternionf q = Quaternionf::fromVectors(v1, v2);
    EXPECT_FLOAT_EQ(q.w, 1.0f);
    EXPECT_FLOAT_EQ(q.x, 0.0f);
    EXPECT_FLOAT_EQ(q.y, 0.0f);
    EXPECT_FLOAT_EQ(q.z, 0.0f);
}

TEST(QuaternionTest, FromVectorsOpposite) {
    Vector3f v1(1, 0, 0);
    Vector3f v2(-1, 0, 0);

    Quaternionf q = Quaternionf::fromVectors(v1, v2);
    // For 180° rotation, expect w ≈ 0 and rotation axis perpendicular to v1
    EXPECT_NEAR(q.w, 0.0f, epsilonf);
    EXPECT_NEAR(std::sqrt(q.x*q.x + q.y*q.y + q.z*q.z), 1.0f, epsilonf);
}