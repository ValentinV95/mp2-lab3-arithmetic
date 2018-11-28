

#include <gtest.h>
#include "arithmetic.h"
TEST(Oper_or_numb, can_identify_operation)
{
	Oper_or_numb c('+');
	EXPECT_EQ(c.Get_op(), '+');
}
TEST(Oper_or_numb, can_identify_priority)
{
	Oper_or_numb c('+');
	EXPECT_EQ(c.Get_lvl(), 1);
}
TEST(Oper_or_numb, can_set_oper)
{
	Oper_or_numb c;
	c.Set('+');
	EXPECT_EQ(c.Get_op(), '+');
}
TEST(Oper_or_numb, can_set_number)
{
	Oper_or_numb c;
	c.Set(2.0);
	EXPECT_EQ(c.Get_value(), 2.0);
}
TEST(Oper_or_numb, can_equal)
{
	Oper_or_numb c,d;
	c.Set(2.0);
	d = c;
	EXPECT_EQ(c.Get_value(), d.Get_value());
}
TEST(Lexeme, can_not_create_with_other_lexems)
{
	ASSERT_ANY_THROW(Lexeme c("12+2$2"));
}
TEST(Lexeme, can_not_create_with_bad_brackets)
{

	ASSERT_ANY_THROW(Lexeme c("12+2*(2+3"));
}

TEST(Lexeme, can_not_create_with_oper_in_the_end)
{

	ASSERT_ANY_THROW(Lexeme c("12+2*2+3-"));
}
TEST(Lexeme, can_not_create_with_oper_before_closed_brackets)
{

	ASSERT_ANY_THROW(Lexeme c("12+2*)(2+3"));
}
TEST(Lexeme, can_not_create_with_point_outside_number)
{

	ASSERT_ANY_THROW(Lexeme c("12+2*.2+3"));
}
TEST(Lexeme, can_not_create_with_some_points)
{

	ASSERT_ANY_THROW(Lexeme c("12+2*1.2.3+3"));
}
TEST(Lexeme, can_simple_operation)
{
	Lexeme c("1+1");
	
	EXPECT_EQ(c.Answer(c.RPN()), 2);

}

TEST(Lexeme, can_simple_operation_in_brackets)
{
	Lexeme c("(1+1)");

	EXPECT_EQ(c.Answer(c.RPN()), 2);

}
TEST(Lexeme, can_some_simple_operation_in_brackets)
{
	Lexeme c("(1+1*2)");

	EXPECT_EQ(c.Answer(c.RPN()), 3);

}
TEST(Lexeme, can_simple_operation_with_different_numbers)
{
	Lexeme c("12+11.2");
	EXPECT_EQ(c.Answer(c.RPN()),23.2);

}

TEST(Lexeme, can_complex_operation_with_different_numbers)
{
	Lexeme c("(12+11.2)*2");

	EXPECT_EQ(c.Answer(c.RPN()), 46.4);

}
TEST(Lexeme, can_negative_numbers)
{
	Lexeme c("(-12)*2");

	EXPECT_EQ(c.Answer(c.RPN()), -24);

}
TEST(Lexeme, can_unar_minus)
{
	Lexeme c("(-(12+11.2))*2");

	EXPECT_EQ(c.Answer(c.RPN()), -46.4);

}
TEST(Lexeme, can_some_unar_minus)
{
	Lexeme c("(-(12+11.2))*2*(-(1+0))");

	EXPECT_EQ(c.Answer(c.RPN()), 46.4);

}