// тесты для вычисления арифметических выражений

#include <gtest.h>
#include <../include/arithmetic.h>

#define EPS 1e-5

TEST(arithmetic, can_create_arithmetic)
{
	ASSERT_NO_THROW(Arithmetic a);
}

TEST(arithmetic, simple_sum_1)
{
	Arithmetic a;
	string s;
	s = "12+2";
	a.stringToTerm(s);
	a.termToPostfix();
	EXPECT_EQ(14.0, a.calculate());
}
TEST(arithmetic, simple_sum_2)
{
	Arithmetic a;
	string s;
	s = "12+8+9-9";
	a.stringToTerm(s);
	a.termToPostfix();
	EXPECT_EQ(20.0, a.calculate());
}
TEST(arithmetic, all_op)
{
	Arithmetic a;
	string s;
	s = "25.6*2.9-9.8+5.0/2.0";
	a.stringToTerm(s);
	a.termToPostfix();
	EXPECT_NEAR(66.94, a.calculate(), EPS);
}
TEST(arithmetic, simple_brackets_sequence)
{
	Arithmetic a;
	string s;
	s = "4.5*(1.+2.)";
	a.stringToTerm(s);
	a.termToPostfix();
	EXPECT_EQ(13.5, a.calculate());
}
TEST(arithmetic, unary_minus_without_brackets)
{
	Arithmetic a;
	string s;
	s = "2+-2";
	a.stringToTerm(s);
	a.termToPostfix();
	EXPECT_EQ(0, a.calculate());
}
TEST(arithmetic, unary_minus_with_brackets_1)
{
	Arithmetic a;
	string s;
	s = "2+(-2)";
	a.stringToTerm(s);
	a.termToPostfix();
	EXPECT_EQ(0, a.calculate());
}
TEST(arithmetic, unary_minus_with_brackets_2)
{
	Arithmetic a;
	string s;
	s = "-12.5+(-12.5)";
	a.stringToTerm(s);
	a.termToPostfix();
	EXPECT_EQ(-25.0, a.calculate());
}
TEST(arithmetic, unary_minus_with_division)
{
	Arithmetic a;
	string s;
	s = "2/-2";
	a.stringToTerm(s);
	a.termToPostfix();
	EXPECT_EQ(-1.0, a.calculate());
}
TEST(arithmetic, unary_minus_with_division_with_brackets_1)
{
	Arithmetic a;
	string s;
	s = "2/(-2)";
	a.stringToTerm(s);
	a.termToPostfix();
	EXPECT_EQ(-1.0, a.calculate());
}
TEST(arithmetic, unary_minus_with_division_with_brackets_2)
{
	Arithmetic a;
	string s;
	s = "1/-(4+6)";
	a.stringToTerm(s);
	a.termToPostfix();
	EXPECT_EQ(-0.1, a.calculate());
}
TEST(arithmetic, unary_minus_with_brackets_more_complex)
{
	Arithmetic a;
	string s;
	s = "1+(-2+3/4-2)";
	a.stringToTerm(s);
	a.termToPostfix();
	EXPECT_EQ(-2.25, a.calculate());
}

TEST(arithmetic, lots_of_unary_minus)
{
	Arithmetic a;
	string s;
	s = "2-------2";
	a.stringToTerm(s);
	a.termToPostfix();
	EXPECT_EQ(0.0, a.calculate());
}

TEST(arithmetic, unary_minus_before_brackets)
{
	Arithmetic a;
	string s;
	s = "-(2+1)";
	a.stringToTerm(s);
	a.termToPostfix();
	EXPECT_EQ(-3.0, a.calculate());
}
TEST(arithmetic, spaces_check_1)
{
	Arithmetic a;
	string s;
	s = "8.345 + 4.-9.125 +   9.125";
	a.stringToTerm(s);
	a.termToPostfix();
	EXPECT_NEAR(12.345, a.calculate(), EPS);
}
TEST(arithmetic, spaces_check_2)
{
	Arithmetic a;
	string s;
	s = "8.345 / 8.345 + ( 4.-9.125 ) +   9.125";
	a.stringToTerm(s);
	a.termToPostfix();
	EXPECT_NEAR(5.0, a.calculate(), EPS);
}
TEST(arithmetic, throw_when_first_character_is_closing_bracket)
{
	Arithmetic a;
	string s;
	s = ")4*3";
	a.stringToTerm(s);
	ASSERT_ANY_THROW(a.termToPostfix());
}
TEST(arithmetic, throw_when_first_character_is_operation)
{
	string s = "/4*3";
	ASSERT_ANY_THROW(isCorrect(s));
}
TEST(arithmetic, throw_when_opening_bracket_goes_after_number)
{
	string s = "8(34+3)";
	ASSERT_ANY_THROW(isCorrect(s));
}
TEST(arithmetic, throw_wrong_amounts_of_brackets)
{
	Arithmetic a;
	string s;
	s = "(8.0))";
	a.stringToTerm(s);
	ASSERT_ANY_THROW(isCorrect(s));
}
TEST(arithmetic, throw_operation_after_opening_bracket)
{
	Arithmetic a;
	string s;
	s = "3+1*(/4)";
	a.stringToTerm(s);
	ASSERT_ANY_THROW(isCorrect(s));
}
TEST(arithmetic, no_throw_unary_minus_after_opening_bracket)
{
	Arithmetic a;
	string s;
	s = "3+1*(-4)";
	a.stringToTerm(s);
	ASSERT_NO_THROW(a.termToPostfix());
}
TEST(arithmetic, throw_last_character_is_operation)
{
	string s = "3+1*";
	ASSERT_ANY_THROW(isCorrect(s));
}
TEST(arithmetic, throw_last_character_is_opening_bracket)
{
	string s = "3+1*(";
	ASSERT_ANY_THROW(isCorrect(s));
}
TEST(arithmetic, division_by_zero)
{
	Arithmetic a;
	string s;
	s = "5.1234/0.0 + 6*(-9+3)";
	a.stringToTerm(s);
	a.termToPostfix();
	ASSERT_ANY_THROW(a.calculate());
}
TEST(arithmetic, too_many_dots)
{
	Arithmetic a;
	string s;
	s = "6 / 3.2.1 + 4.98";
	ASSERT_ANY_THROW(a.stringToTerm(s));
}