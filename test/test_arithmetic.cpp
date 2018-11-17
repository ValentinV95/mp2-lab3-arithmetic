// тесты для вычисления арифметических выражений

#include <gtest.h>
#include <arithmetic.h>

TEST(Computer, can_count_simple_expression)
{

	Computer a ;
	a.Check("5+5=", '=' );
	a.Parse("5+5=", '=');
	EXPECT_EQ(10, a.Compute());
}

TEST(Computer, can_count_expression_with_different_operation)
{

	Computer a ;
	a.Check("5+5*5=", '=' );
	a.Parse("5+5*5=", '=');
	EXPECT_EQ(30, a.Compute());
}

TEST(Computer, can_count_expression_wiht_brakets)
{

	Computer a ;
	a.Check("5+5*(5+5)=", '=' );
	a.Parse("5+5*(5+5)=", '=');
	EXPECT_EQ(55, a.Compute());
}

TEST(Computer, throw_when_expression_is_not_complete)
{
	Computer a;
	ASSERT_ANY_THROW( a.Check("5+6+=",'='));
}

TEST(Computer, throw_when_not_enought_closing_brackets)
{
	Computer a;
	ASSERT_ANY_THROW (a.Check("6+(8*7+9=",'='));
}

TEST(Computer, throw_when_not_enought_opening_brackets)
{
	Computer a;
	ASSERT_ANY_THROW (a.Check("6+8*7)+9=",'='));
}

TEST(Computer, throw_when_two_numbers_in_a_row)
{
	Computer a;
	ASSERT_ANY_THROW (a.Check("6 9 + 7 =",'='));
}

TEST(Computer, throw_when_two_operations_in_a_row)
{
	Computer a;
	ASSERT_ANY_THROW (a.Check("6 - + 7 =",'='));
}

TEST(Computer, throw_when_expression_start_with_plus)
{
	Computer a;
	ASSERT_ANY_THROW (a.Check(" + 7 + 8 =",'='));
}

TEST(Computer, throw_when_expression_start_with_multiplicatoin)
{
	Computer a;
	ASSERT_ANY_THROW (a.Check(" * 7 + 8 =",'='));

}TEST(Computer, throw_when_expression_start_with_division)
{
	Computer a;
	ASSERT_ANY_THROW (a.Check(" / 7 + 8 =",'='));

}TEST(Computer, throw_when_expression_start_with_closin_bracket)
{
	Computer a;
	ASSERT_ANY_THROW (a.Check(" + 7 + 8 =",'='));
}

TEST(Computer, throw_when_closing_bracket_before_opening)
{
	Computer a;
	ASSERT_ANY_THROW (a.Check("6-9)(7+8 =",'='));
}

TEST(Computer, expresions_can_start_with_a_minus)
{
	Computer a;
	ASSERT_NO_THROW (a.Check("-7 + 7=",'='));
}

TEST (Computer, throw_when_invalid_character_after_the_opening_bracket)
{
	Computer a;
	ASSERT_ANY_THROW(a.Check("7+(+7)",'='));
}

TEST (Computer, throw_when_invalid_character_after_the_closing_bracket)
{
	Computer a;
	ASSERT_ANY_THROW(a.Check("7+(9+7)7",'='));
}