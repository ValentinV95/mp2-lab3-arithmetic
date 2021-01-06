// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.cpp"
#include "arithmetic.h"

TEST(arithmetic, constructor) {
    ASSERT_NO_THROW(arithmetic("1+2"));
    ASSERT_ANY_THROW(arithmetic("1+2 +  + 7"));

    ASSERT_ANY_THROW(arithmetic("(12/2*7"));
    ASSERT_ANY_THROW(arithmetic("cos"));
    ASSERT_ANY_THROW(arithmetic("1*/8"));
}

TEST(arithmetic, isCorrect) {
    ASSERT_TRUE(arithmetic::isCorrect("1+2*(5-16/3)-4"));
    ASSERT_TRUE(arithmetic::isCorrect("-5*9.6+14/(3+56.)-2"));
    ASSERT_TRUE(arithmetic::isCorrect("    5 + 6 + (-2*3)  "));

    ASSERT_FALSE(arithmetic::isCorrect("--1+2 + 8 +  + 7"));
    ASSERT_FALSE(arithmetic::isCorrect("1+2^9.0 + 7"));
    ASSERT_FALSE(arithmetic::isCorrect("1+0.32 / ((7*3)"));
}

TEST(arithmetic, COUNT_transform_deleteSpaces_LeftRightCharacter_isSymbolsCorrect) {
    ASSERT_NEAR(arithmetic("1+2").count(), 3.0, 1e-15);
    ASSERT_NEAR(arithmetic("-5*9.6+14/(2.8+4.2)-2").count(), -48.0, 1e-15);
    ASSERT_NEAR(arithmetic("(((1 + 1) * 1 + 1) * 1 + 1) + 1").count(), 5.0, 1e-15);
    ASSERT_NEAR(arithmetic("-11+11").count(), 0.0, 1e-15);
    ASSERT_NEAR(arithmetic("12-(-12)").count(), 24.0, 1e-15);
    ASSERT_NEAR(arithmetic("10-(-(-10)) + 1/(-5)").count(), -0.2, 1e-15);
    ASSERT_NEAR(arithmetic("-(-5.703)").count(), 5.703, 1e-15);
    ASSERT_NEAR(arithmetic("-11.3").count(), -11.3, 1e-15);
    ASSERT_NEAR(arithmetic("(12/2)+((56/8)-11)").count(), 2, 1e-15);
    ASSERT_NEAR(arithmetic("12/2*5").count(), 30.0, 1e-15);
}
TEST(arithmetic, priority) {
    EXPECT_EQ(priority('*'), priority('/'));
    EXPECT_EQ(priority('+'), priority('-'));
    ASSERT_FALSE(priority('*') < priority('-'));
    ASSERT_TRUE(priority('/') >= priority('+'));
}
