// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"
using namespace std;
TEST(work, test_arifmetic_1)
{
   string s = "-5+10+(-10)+cos((10-10)*5)-16/(4*4)+0.5*10";
    EXPECT_EQ(-2, work(s));
}
TEST(work, test_arifmetic_2)
{
    string s = "-5+5";
    EXPECT_EQ(0, work(s));
}
TEST(work, test_arifmetic_3)
{
   string s = "5--5";
    EXPECT_EQ(10, work(s));
}
TEST(work, test_arifmetic_4)
{
    string s = "5*-5";
    EXPECT_EQ(-25, work(s));
}
TEST(work, test_arifmetic_5)
{
    string s = "--5";
    EXPECT_EQ(5, work(s));
}
TEST(work, test_arifmetic_6)
{
    string s = "cos(ln(1))";
    EXPECT_EQ(1, work(s));
}
TEST(work,  test_arifmetic_7)
{
    string s = "1*/5";
    ASSERT_ANY_THROW(work(s));
}
TEST(work, test_arifmetic_8)
{
    string s = "(8+6/9";
    ASSERT_ANY_THROW(work(s));
}
TEST(work, test_arifmetic_9)
{
    string s = "hello";
    ASSERT_ANY_THROW(work(s));
}
