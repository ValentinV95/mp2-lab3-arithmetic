// тесты для вычисления арифметических выражений

#include <gtest.h>
#include <string>
#include "arithmetic.h"

using namespace std;

TEST(interpreter, throw_when_expression_is_not_complete_1)
{
	string a = "2+2+";
	ASSERT_ANY_THROW(interpreter(a));
}

TEST(interpreter, throw_when_expression_is_not_complete_2)
{
	string a = "2++2";
	ASSERT_ANY_THROW(interpreter(a));
}

TEST(interpreter, throw_when_expression_is_not_complete_3)
{
	string a = "(2+2)-8)";
	ASSERT_ANY_THROW(interpreter(a));
}

TEST(interpreter, throw_when_expression_is_not_complete_4)
{
	string a = "2.2.2+8";
	ASSERT_ANY_THROW(interpreter(a));
}

TEST(interpreter, throw_when_expression_is_not_complete_5)
{
	string a = "2+8-()";
	ASSERT_ANY_THROW(interpreter(a));
}

TEST(interpreter, throw_when_expression_is_not_complete_6)
{
	string a = ")10+13(";
	ASSERT_ANY_THROW(interpreter(a));
}

TEST(interpreter, throw_when_expression_is_not_complete_7)
{
	string a = "2+2&";
	ASSERT_ANY_THROW(interpreter(a));
}

TEST(interpreter, throw_when_expression_is_not_complete_8)
{
	string a = "(2+2)9";
	ASSERT_ANY_THROW(interpreter(a));
}

TEST(interpreter, throw_when_expression_is_not_complete_9)
{
	string a = "9(2+2)";
	ASSERT_ANY_THROW(interpreter(a));
}

TEST(interpreter, throw_when_expression_is_not_complete_10)
{
	string a = "9(2+2)";
	ASSERT_ANY_THROW(interpreter(a));
}

TEST(interpreter, throw_when_expression_is_not_complete_11)
{
	string a = "(2+2)(2+2)";
	ASSERT_ANY_THROW(interpreter(a));
}

TEST(interpreter, throw_when_expression_is_not_complete_12)
{
	string a = "2/0";
	ASSERT_ANY_THROW(interpreter(a));
}

TEST(interpreter, can_calculate_the_expression_1)
{
	string a = "2+2";
	EXPECT_EQ(4, interpreter(a));
}

TEST(interpreter, can_calculate_the_expression_2)
{
	string a = "2+2*2";
	EXPECT_EQ(6, interpreter(a));
}

TEST(interpreter, can_calculate_the_expression_3)
{
	string a = "(2+2)*2";
	EXPECT_EQ(8, interpreter(a));
}

TEST(interpreter, can_calculate_the_expression_4)
{
	string a = "2--2";
	EXPECT_EQ(4, interpreter(a));
}

TEST(interpreter, can_calculate_the_expression_5)
{
	string a = "-2-2";
	EXPECT_EQ(-4, interpreter(a));
}

TEST(interpreter, can_calculate_the_expression_6)
{
	string a = "2+3";
	string b = "3+2";
	EXPECT_EQ(interpreter(b), interpreter(a));
}

TEST(interpreter, can_calculate_the_expression_7)
{
	string a = "(2+3)*4";
	string b = "4*3+2*4";
	EXPECT_EQ(interpreter(b), interpreter(a));
}

TEST(interpreter, can_calculate_the_expression_8)
{
	string a = "(2+2)*(2+2)";
	EXPECT_EQ(16, interpreter(a));
}