#include <gtest/gtest.h>
#include "type.hpp"

// ---------- Vector2 ----------
TEST(Vector2Test, DefaultInitialization) {
    Vector2i v{};
    EXPECT_EQ(v.x, 0);
    EXPECT_EQ(v.y, 0);

    Vector2f vf{};
    EXPECT_DOUBLE_EQ(vf.x, 0.0);
    EXPECT_DOUBLE_EQ(vf.y, 0.0);
}

TEST(Vector2Test, Assignment) {
    Vector2i v{10, 20};
    EXPECT_EQ(v.x, 10);
    EXPECT_EQ(v.y, 20);
}

// ---------- Vector3 ----------
TEST(Vector3Test, DefaultInitialization) {
    Vector3f v{};
    EXPECT_DOUBLE_EQ(v.x, 0.0);
    EXPECT_DOUBLE_EQ(v.y, 0.0);
    EXPECT_DOUBLE_EQ(v.z, 0.0);
}

// ---------- Vector4 ----------
TEST(Vector4Test, Assignment) {
    Vector4i v{1,2,3,4};
    EXPECT_EQ(v.x, 1);
    EXPECT_EQ(v.y, 2);
    EXPECT_EQ(v.w, 3);
    EXPECT_EQ(v.h, 4);
}

// ---------- Color ----------
TEST(ColorTest, DefaultInitialization) {
    Color c{};
    EXPECT_EQ(c.r, 0);
    EXPECT_EQ(c.g, 0);
    EXPECT_EQ(c.b, 0);
    EXPECT_EQ(c.a, 0);
}

TEST(ColorTest, Assignment) {
    Color c{255,128,64,32};
    EXPECT_EQ(c.r, 255);
    EXPECT_EQ(c.g, 128);
    EXPECT_EQ(c.b, 64);
    EXPECT_EQ(c.a, 32);
}

// ---------- Quaternion ----------
TEST(QuaternionTest, DefaultInitialization) {
    Quaternion q{};
    EXPECT_DOUBLE_EQ(q.w, 0.0);
    EXPECT_DOUBLE_EQ(q.x, 0.0);
    EXPECT_DOUBLE_EQ(q.y, 0.0);
    EXPECT_DOUBLE_EQ(q.z, 0.0);
}

TEST(QuaternionTest, Assignment) {
    Quaternion q{1.0, 0.1, 0.2, 0.3};
    EXPECT_DOUBLE_EQ(q.w, 1.0);
    EXPECT_DOUBLE_EQ(q.x, 0.1);
    EXPECT_DOUBLE_EQ(q.y, 0.2);
    EXPECT_DOUBLE_EQ(q.z, 0.3);
}