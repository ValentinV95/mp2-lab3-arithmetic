// тесты для вычисления арифметических выражений
#include "arithmetic.h"
#include <gtest.h>

TEST(TArithmetic, can_create_arithmetic)
{
	ASSERT_NO_THROW(TArithmetic p("a+b"));
}

TEST(TArithmetic, can_get_infix)
{
	TArithmetic p("a+b");
	EXPECT_EQ("a+b", p.GetInfix());
}

TEST(TArithmetic, cant_start_infix_with_operation)
{
	ASSERT_ANY_THROW(TArithmetic p("+a+b"));
}

TEST(TArithmetic, cant_end_infix_with_operation)
{
	ASSERT_ANY_THROW(TArithmetic p("a+b+"));
}

TEST(TArithmetic, cant_create_infix_with_two_operation_next_to_each_other)
{
	ASSERT_ANY_THROW(TArithmetic p("a++b"));
}

TEST(TArithmetic, cant_create_infix_with_two_operands_next_to_each_other)
{
	ASSERT_ANY_THROW(TArithmetic p("ac+b"));
}

TEST(TArithmetic, cant_create_infix_only_with_operands)
{
	ASSERT_ANY_THROW(TArithmetic p("acb"));
}

TEST(TArithmetic, cant_create_infix_only_with_operations)
{
	ASSERT_ANY_THROW(TArithmetic p("+++"));
}

TEST(TArithmetic, cant_create_infix_with_wrong_parentheses)
{
	ASSERT_ANY_THROW(TArithmetic p("(a+b))"));
}

TEST(TArithmetic, can_create_infix_with_right_parentheses)
{
	ASSERT_NO_THROW(TArithmetic p("((a+b))"));
}

TEST(TArithmetic, can_create_right_arithmetic)
{
	TArithmetic p("(a+b)+(f*h+c+d)");
	p.ToArithmetic();
	EXPECT_EQ(" a b + f h * c + d + +", p.GetArithmetic());
}

TEST(TArithmetic, can_calculate_arithmetic)
{
	TArithmetic p("(1+2)+(3*4+1+1)");
	p.ToArithmetic();
	EXPECT_EQ(17, p.Calculate());
}

TEST(TArithmetic, can_calculate_arithmetic_with_parametres)
{
	TArithmetic p("(a+b)+(c*d+e+j)");
	cout << endl << "Enter a=1,b=2,c=3,d=4,e=1,j=1" << endl << endl;
	p.ToArithmetic();
	EXPECT_EQ(17, p.Calculate());
}

TEST(TArithmetic, can_get_right_priority_of_the_operations)
{
	TArithmetic p("a+b");
	EXPECT_TRUE(p.Priority('*') > p.Priority('+'));
}