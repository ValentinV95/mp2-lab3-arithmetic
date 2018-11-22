// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"
TEST(solve, right_answ1)
{
    string s  = "-1+12+(-12)+cos((9-9)*5)-9/(3*3)+0.25*4";
    EXPECT_EQ(0, solve(s) );
}
TEST(solve, right_answ2)
{
    string s  = "-12+12";
    EXPECT_EQ(0, solve(s) );
}
TEST(solve, right_answ3)
{
    string s  = "(((1+1)*1+1)*1+1)+1";
    EXPECT_EQ(5, solve(s) );
}
TEST(solve, right_answ4)
{
    string s  = "12--12";
    EXPECT_EQ(24, solve(s) );
}
TEST(solve, right_answ5)
{
    string s  = "12*-12";
    EXPECT_EQ(-144, solve(s) );
}
TEST(solve, right_answ6)
{
    string s  = "12---12";
    EXPECT_EQ(0, solve(s) );
}
TEST(solve, right_answ7)
{
    string s  = "1/-5";
    EXPECT_EQ(-0.2, solve(s) );
}
TEST(solve, right_answ8)
{
    string s  = "--12";
    EXPECT_EQ(12, solve(s) );
}
TEST(solve, right_answ9)
{
    string s  = "-12.3";
    EXPECT_EQ(-12.3, solve(s) );
}
TEST(solve, right_answ10)
{
    string s  = "(12/2)+((64/8)-15)";
    EXPECT_EQ(-1, solve(s) );
}
TEST(solve, right_answ11)
{
    string s  = "12/2*5";
    EXPECT_EQ(30, solve(s) );
}
TEST(solve, right_answ12)
{
    string s  = "cos(ln(1))";
    EXPECT_EQ(1, solve(s) );
}
TEST(solve, throws_if_not_correct)
{
    string s  = "(12/2*5";
    ASSERT_ANY_THROW(solve(s));
}
TEST(solve, throws_if_not_correct2)
{
    string s  = "hello";
    ASSERT_ANY_THROW(solve(s));
}
TEST(solve, throws_if_not_correct3)
{
    string s  = "cos()";
    ASSERT_ANY_THROW(solve(s));
}
TEST(solve, throws_if_not_correct4)
{
    string s  = "cos2.1";
    ASSERT_ANY_THROW(solve(s));
}    
TEST(solve, throws_if_not_correct5)
{
    string s  = "1*/8";
    ASSERT_ANY_THROW(solve(s));
}
