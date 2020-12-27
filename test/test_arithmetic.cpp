// тесты для вычисления арифметических выражений
#include <gtest.h>
#include "arithmetic.h"

#define EPS 1e-7

TEST(arithmetic, simple_sum_1)
{
	Solver a;
	string s;
	s = "12+2";
	a.convert_string_to_lexeme(s);
	a.convert_to_RPN();
	EXPECT_EQ(14.0, a.solve());
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
TEST(arithmetic, unary_minus_with_brackets_1)
{
	Solver a;
	string s;
	s = "2+(-2)";
	a.convert_string_to_lexeme(s);
	a.convert_to_RPN();
	EXPECT_EQ(0, a.solve());
}

TEST(arithmetic, unary_minus_with_brackets_2)
{
	Solver a;
	string s;
	s = "-12.5+(-12.5)";
	a.convert_string_to_lexeme(s);
	a.convert_to_RPN();
	EXPECT_EQ(-25.0, a.solve());
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
TEST(arithmetic, unary_minus_with_brackets_more_complex_2)
{
	Solver a;
	string s;
	s = "(12 / 2) + ((64 / 8) - 15)";
	a.convert_string_to_lexeme(s);
	a.convert_to_RPN();
	EXPECT_EQ(-1.0, a.solve());
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

TEST(arithmetic, throw_when_first_character_is_closing_bracket)
{
	Solver a;
	string s;
	s = ")4*3";
	a.convert_string_to_lexeme(s);
	ASSERT_ANY_THROW(a.convert_to_RPN(););
}

TEST(arithmetic, throw_when_first_character_is_operation)
{
	Solver a;
	string s;
	s = "/4*3";
	a.convert_string_to_lexeme(s);
	ASSERT_ANY_THROW(a.convert_to_RPN(););
}

TEST(arithmetic, throw_when_closing_bracket_goes_after_number)
{
	Solver a;
	string s;
	s = "8(34+3)";
	a.convert_string_to_lexeme(s);
	ASSERT_ANY_THROW(a.convert_to_RPN(););
}

TEST(arithmetic, throw_wrong_amounts_of_brackets)
{
	Solver a;
	string s;
	s = "(8.0))";
	a.convert_string_to_lexeme(s);
	ASSERT_ANY_THROW(a.convert_to_RPN(););
}

TEST(arithmetic, throw_no_operations_or_numbers_between_brackets)
{
	Solver a;
	string s;
	s = "3+1*()";
	a.convert_string_to_lexeme(s);
	ASSERT_ANY_THROW(a.convert_to_RPN(););
}

TEST(arithmetic, throw_no_operations_between_closing_and_opening_brackets)
{
	Solver a;
	string s;
	s = "(4+1)(4/5)";
	a.convert_string_to_lexeme(s);
	ASSERT_ANY_THROW(a.convert_to_RPN(););
}

TEST(arithmetic, throw_operation_after_opening_bracket)
{
	Solver a;
	string s;
	s = "3+1*(/4)";
	a.convert_string_to_lexeme(s);
	ASSERT_ANY_THROW(a.convert_to_RPN(););
}

TEST(arithmetic, no_throw_unary_minus_after_opening_bracket)
{
	Solver a;
	string s;
	s = "3+1*(-4)";
	a.convert_string_to_lexeme(s);
	ASSERT_NO_THROW(a.convert_to_RPN(););
}

TEST(arithmetic, throw_last_character_is_opening_bracket)
{
	Solver a;
	string s;
	s = "3+1*(";
	a.convert_string_to_lexeme(s);
	ASSERT_ANY_THROW(a.convert_to_RPN(););
}
