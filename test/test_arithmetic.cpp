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