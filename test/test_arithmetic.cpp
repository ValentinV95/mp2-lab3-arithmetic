// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"
TEST(work, correct_answer0)
{
    std::string s = "-1+12+(-12)+cos((9-9)*5)-9/(3*3)+0.25*4";
    EXPECT_EQ(0, work(s));
}
TEST(work, correct_answer1)
{
    std::string s = "-12+12";
    EXPECT_EQ(0, work(s));
}
TEST(work, correct_answer2)
{
    std::string s = "(((1+1)*1+1)*1+1)+1";
    EXPECT_EQ(5, work(s));
}
TEST(work, correct_answer3)
{
    std::string s = "12--12";
    EXPECT_EQ(24, work(s));
}
TEST(work, correct_answer4)
{
    std::string s = "12*-12";
    EXPECT_EQ(-144, work(s));
}
TEST(work, correct_answer5)
{
    std::string s = "12---12";
    EXPECT_EQ(0, work(s));
}
TEST(work, correct_answer6)
{
    std::string s = "1/-5";
    EXPECT_EQ(-0.2, work(s));
}
TEST(work, correct_answer7)
{
    std::string s = "--12";
    EXPECT_EQ(12, work(s));
}
TEST(work, correct_answer8)
{
    std::string s = "-12.3";
    EXPECT_EQ(-12.3, work(s));
}
TEST(work, correct_answer9)
{
    std::string s = "(12/2)+((64/8)-15)";
    EXPECT_EQ(-1, work(s));
}
TEST(work, correct_answer10)
{
    std::string s = "12/2*5";
    EXPECT_EQ(30, work(s));
}
TEST(work, correct_answer11)
{
    std::string s = "cos(ln(1))";
    EXPECT_EQ(1, work(s));
}
TEST(work, throws_if_not_correct0)
{
    std::string s = "(12/2*7";
    ASSERT_ANY_THROW(work(s));
}
TEST(work, throws_if_not_correct1)
{
    std::string s = "Poly";
    ASSERT_ANY_THROW(work(s));
}
TEST(work, throws_if_not_correct2)
{
    std::string s = "cos()";
    ASSERT_ANY_THROW(work(s));
}
TEST(work, throws_if_not_correct3)
{
    std::string s = "cos2.1";
    ASSERT_ANY_THROW(work(s));
}
TEST(work, throws_if_not_correct4)
{
    std::string s = "1*/8";
    ASSERT_ANY_THROW(work(s));
}
