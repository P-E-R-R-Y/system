#include "Lambdify.hpp"  // or rely on Type.hpp once Lambdify is registered there
#include <gtest/gtest.h>

// ---------- Lambdify test fixtures ----------
namespace {
    int addInts(int a, int b) { return a + b; }
    double scale(double x, double k) { return x * k; }
    bool isEqualInt(int a, int b) { return a == b; }

    int sideEffectCounter = 0;
    void tick() { ++sideEffectCounter; }

    constexpr int addConstexpr(int a, int b) { return a + b; }

    // For perfect-forwarding test
    int sumMoved = 0;
    int consumeRvalue(std::string&& s) { sumMoved += static_cast<int>(s.size()); return sumMoved; }
}

// ---------- Lambdify ----------

TEST(LambdifyTest, WrapsAndCalls) {
    lambdify_t<addInts> add;
    EXPECT_EQ(add(2, 3), 5);
    EXPECT_EQ(add(-1, 1), 0);
}

TEST(LambdifyTest, DefaultConstructible) {
    // The whole point: lets `Graph<T, Equal>` instantiate `Equal{}` internally.
    static_assert(std::is_default_constructible_v<lambdify_t<addInts>>,
                  "lambdify_t must be default-constructible");
    lambdify_t<addInts> a{};
    lambdify_t<addInts> b{};
    EXPECT_EQ(a(10, 5), b(10, 5));
}

TEST(LambdifyTest, Stateless) {
    // No member data → empty type (sizeof == 1 by C++ rule, but EBCO-friendly).
    EXPECT_EQ(sizeof(lambdify_t<addInts>), 1u);
}

TEST(LambdifyTest, DistinctTypesPerFunction) {
    // Critical for template overloading / Graph instantiation uniqueness.
    using AddWrapper   = lambdify_t<addInts>;
    using ScaleWrapper = lambdify_t<scale>;
    static_assert(!std::is_same_v<AddWrapper, ScaleWrapper>,
                  "different functions must produce different wrapper types");
}

TEST(LambdifyTest, BoolReturn) {
    lambdify_t<isEqualInt> eq;
    EXPECT_TRUE(eq(7, 7));
    EXPECT_FALSE(eq(7, 8));
}

TEST(LambdifyTest, FloatingPointReturn) {
    lambdify_t<scale> mul;
    EXPECT_DOUBLE_EQ(mul(2.5, 4.0), 10.0);
    EXPECT_DOUBLE_EQ(mul(0.0, 999.0), 0.0);
}

TEST(LambdifyTest, VoidReturn) {
    sideEffectCounter = 0;
    lambdify_t<tick> trigger;
    trigger();
    trigger();
    trigger();
    EXPECT_EQ(sideEffectCounter, 3);
}

TEST(LambdifyTest, PerfectForwarding) {
    sumMoved = 0;
    lambdify_t<consumeRvalue> consume;
    EXPECT_EQ(consume(std::string("hello")), 5);   // 5 chars
    EXPECT_EQ(consume(std::string("world!")), 11); // 5 + 6
}

TEST(LambdifyTest, Constexpr) {
    constexpr lambdify_t<addConstexpr> add;
    constexpr int result = add(40, 2);
    static_assert(result == 42, "lambdify must be usable in constexpr context");
    EXPECT_EQ(result, 42);
}

TEST(LambdifyTest, UsableAsTemplateArgument) {
    // Mirrors the real-world Graph<Vector2f, lambdify_t<eq>> use case.
    // Sanity check: the wrapper type can be passed where a comparator is expected.
    using Eq = lambdify_t<isEqualInt>;
    Eq eq{};
    EXPECT_TRUE(eq(42, 42));
    EXPECT_FALSE(eq(42, 43));

    // If your Graph header is included in this TU, you can extend with:
    // Graph<int, lambdify_t<isEqualInt>> g;
    // g.addNode(5); g.addNode(5);
    // EXPECT_EQ(g.nodes.size(), 1u);
}