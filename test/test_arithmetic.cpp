// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"

TEST(arithmetic, simple_sum_1)
{
	Solver a;
	string s;
	s = "12+2";
	a.convert_string_to_lexeme(s);
	a.convert_to_RPN();
	EXPECT_EQ(14.0,a.solve());
}

TEST(arithmetic, simple_sum_2)
{
	Solver a;
	string s;
	s = "12+8+9-9";
	a.convert_string_to_lexeme(s);
	a.convert_to_RPN();
	EXPECT_EQ(20.0, a.solve());
}

TEST(arithmetic, all_op)
{
	Solver a;
	string s;
	s = "25.6*2.9-9.8+5.0/2.0";
	a.convert_string_to_lexeme(s);
	a.convert_to_RPN();
	EXPECT_EQ(66.94, a.solve());
}

TEST(arithmetic, simple_brackets_sequence)
{
	Solver a;
	string s;
	s = "4.5*(1.+2.)";
	a.convert_string_to_lexeme(s);
	a.convert_to_RPN();
	EXPECT_EQ(13.5, a.solve());
}

TEST(arithmetic, unary_minus_without_brackets)
{
	Solver a;
	string s;
	s = "2+-2";
	a.convert_string_to_lexeme(s);
	a.convert_to_RPN();
	EXPECT_EQ(0, a.solve());
}

TEST(arithmetic, unary_minus_with_brackets)
{
	Solver a;
	string s;
	s = "2+(-2)";
	a.convert_string_to_lexeme(s);
	a.convert_to_RPN();
	EXPECT_EQ(0, a.solve());
}

TEST(arithmetic, unary_minus_with_division)
{
	Solver a;
	string s;
	s = "2/-2";
	a.convert_string_to_lexeme(s);
	a.convert_to_RPN();
	EXPECT_EQ(-1.0, a.solve());
}

TEST(arithmetic, unary_minus_with_division_with_brackets)
{
	Solver a;
	string s;
	s = "2/(-2)";
	a.convert_string_to_lexeme(s);
	a.convert_to_RPN();
	EXPECT_EQ(-1.0, a.solve());
}

TEST(arithmetic, unary_minus_with_brackets_more_complex)
{
	Solver a;
	string s;
	s = "1+(-2+3/4-2)";
	a.convert_string_to_lexeme(s);
	a.convert_to_RPN();
	EXPECT_EQ(-2.25, a.solve());
}

TEST(arithmetic, lots_of_unary_minus)
{
	Solver a;
	string s;
	s = "2+-----2";
	a.convert_string_to_lexeme(s);
	a.convert_to_RPN();
	EXPECT_EQ(0.0, a.solve());
}

TEST(arithmetic, unary_minus_before_brackets)
{
	Solver a;
	string s;
	s = "-(2+1)";
	a.convert_string_to_lexeme(s);
	a.convert_to_RPN();
	EXPECT_EQ(-3.0, a.solve());
}

TEST(arithmetic, spaces_check_1)
{
	Solver a;
	string s;
	s = "8.345 + 4.-9.125 +   9.125";
	a.convert_string_to_lexeme(s);
	a.convert_to_RPN();
	EXPECT_EQ(12.345, a.solve());
}

TEST(arithmetic, spaces_check_2)
{
	Solver a;
	string s;
	s = "8.345 / 8.345 + ( 4.-9.125 ) +   9.125";
	a.convert_string_to_lexeme(s);
	a.convert_to_RPN();
	EXPECT_EQ(5.0, a.solve());
}





