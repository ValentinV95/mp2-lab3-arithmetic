// тесты для вычисления арифметических выражений

#include "arithmetic.h"
#include <gtest.h>

TEST(TFormula, can_do_operation_plus)
{
	TFormula A("3.5+6.5");

	EXPECT_DOUBLE_EQ(A.Calculator(),10);
}

TEST(TFormula, can_do_operation_minus)
{
	TFormula A("7.21-5.11");

	EXPECT_DOUBLE_EQ(A.Calculator(), 2.10);
}

TEST(TFormula, can_do_operation_mult)
{
	TFormula A("2.5*10");

	EXPECT_DOUBLE_EQ(A.Calculator(), 25);
}

TEST(TFormula, can_do_operation_div)
{
	TFormula A("6/4");

	EXPECT_DOUBLE_EQ(A.Calculator(), 1.5);
}

TEST(TFormula, can_do_operation_unarny_minus)
{
	TFormula A("---5");

	EXPECT_DOUBLE_EQ(A.Calculator(), -5);
}

TEST(TFormula, can_do_all_operation_without_braces)
{
	TFormula A("9/-3+2*3-10.5");

	EXPECT_DOUBLE_EQ(A.Calculator(), -7.5);
}

TEST(TFormula, can_do_operation_with_braces)
{
	TFormula A("-(2.5+3.5)/1.2");

	EXPECT_DOUBLE_EQ(A.Calculator(), -5);
}

TEST(TFormula, can_do_operation_unarny_minus_with_operation)
{
	TFormula A("-5*2+-4/-2");

	EXPECT_DOUBLE_EQ(A.Calculator(), -8);
}

TEST(TFormula, can_do_operation_unarny_minus_with_operation_and_braces)
{
	TFormula A("(((1+1)*1+1)*1+1)/-1.5");

	EXPECT_DOUBLE_EQ(A.Calculator(), -8);
}

TEST(TFormula, false_when_first_lecsem_is_closing_brace)
{
	TFormula A(")3*8");

	EXPECT_EQ(A.Checker(), false);
}

TEST(TFormula, false_when_wrong_amounts_of_brace)
{
	TFormula A("(3+8))");

	EXPECT_EQ(A.Checker(), false);
}

TEST(TFormula, false_when_first_lecsem_is_binary_operation)
{
	TFormula A("*8/9");

	EXPECT_EQ(A.Checker(), false);
}

TEST(TFormula, false_when_no_operations_between_closing_and_opening_brace)
{
	TFormula A("(6+5)(5*9)");

	EXPECT_EQ(A.Checker(), false);
}

TEST(TFormula, false_when_binary_operations_after_opening_brace)
{
	TFormula A("(+6+9)");

	EXPECT_EQ(A.Checker(), false);
}

TEST(TFormula, true_when_unarny_minus_after_opening_brace)
{
	TFormula A("(-5*2)");

	EXPECT_EQ(A.Checker(), true);
}

TEST(TFormula, false_when_closing_brace_after_operations)
{
	TFormula A("(6+5)(+)");

	EXPECT_EQ(A.Checker(), false);
}
