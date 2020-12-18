// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"
TEST(translationToRPE, correct_with_an_empty_string)
{
    std::string s = " ";
    ASSERT_NO_THROW(translationToRPE(s));
}
TEST(translationToRPE, correct_with_one_value)
{
    std::string s = "4";
    ASSERT_NO_THROW(translationToRPE(s));
}
TEST(translationToRPE, correct_with_one_value2)
{
    std::string s = "4";
    EXPECT_EQ(4, translationToRPE(s));
}
TEST(translationToRPE, correct_with_one_value2_with_whitespaces)
{
    std::string s = " 4 ";
    EXPECT_EQ(4, translationToRPE(s));
}
TEST(translationToRPE, correct_answer0)
{
    std::string s = "4-15+42*128/(1-2*sin(1))";
    ASSERT_NO_THROW(translationToRPE(s));
}
TEST(translationToRPE, correct_answer1)
{
    std::string s = "-12+12";
    EXPECT_EQ(0, translationToRPE(s));
}
TEST(translationToRPE, correct_answer2)
{
    std::string s = "(((1+1)*1+1)*1+1)+1";
    EXPECT_EQ(5, translationToRPE(s));
}
TEST(translationToRPE, correct_answer3)
{
    std::string s = "12--12";
    EXPECT_EQ(24, translationToRPE(s));
}
TEST(translationToRPE, correct_answer4)
{
    std::string s = "12*-12";
    EXPECT_EQ(-144, translationToRPE(s));
}
TEST(translationToRPE, correct_answer5)
{
    std::string s = "12----12";
    EXPECT_EQ(0, translationToRPE(s));
}
TEST(translationToRPE, correct_answer6)
{
    std::string s = "1/-5";
    EXPECT_EQ(-0.2, translationToRPE(s));
}
TEST(translationToRPE, correct_answer7)
{
    std::string s = "--12";
    EXPECT_EQ(12, translationToRPE(s));
}
TEST(translationToRPE, correct_answer8)
{
    std::string s = "6/3*2";
    EXPECT_EQ(4, translationToRPE(s));
}
TEST(translationToRPE, correct_answer9)
{
    std::string s = "cos(ln(1))";
    EXPECT_NEQ(1, translationToRPE(s));
}
TEST(translationToRPE, throws_if_not_correct0)
{
    std::string s = "(12/2*7";
    ASSERT_ANY_THROW(translationToRPE(s));
}
TEST(translationToRPE, throws_if_not_correct1)
{
    std::string s = "sin()";
    ASSERT_ANY_THROW(translationToRPE(s));
}
TEST(translationToRPE, throws_if_not_correct2)
{
    std::string s = "tg";
    ASSERT_ANY_THROW(translationToRPE(s));
}
TEST(translationToRPE, throws_if_not_correct3)
{
    std::string s = "cos2.1";
    ASSERT_ANY_THROW(translationToRPE(s));
}
TEST(translationToRPE, throws_if_not_correct4)
{
    std::string s = "12+*1";
    ASSERT_ANY_THROW(translationToRPE(s));
}
TEST(translationToRPE, throws_if_not_correct5)
{
    std::string s = "12=11";
    ASSERT_ANY_THROW(translationToRPE(s));
}
TEST(translationToRPE, throws_if_not_correct6)
{
    std::string s = "12_11";
    ASSERT_ANY_THROW(translationToRPE(s));
}
TEST(translationToRPE, throws_if_not_correct7)
{
    std::string s = "12!11";
    ASSERT_ANY_THROW(translationToRPE(s));
}