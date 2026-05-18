#include <gtest/gtest.h>
#include "Type.hpp"

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