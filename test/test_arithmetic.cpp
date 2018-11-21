// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"

TEST(TPostfix, can_create_postfix)
{
	TPostfix p();
	ASSERT_NO_THROW(p);
}

TEST(TPostfix, can_get_infix)
{
	TPostfix p("2+5");
	EXPECT_EQ("2+5", p.GetInfix());
}

TEST(TCalculator, can_setInfix_void_postfix)
{
	TPostfix p("");
	ASSERT_NO_THROW(p.GetInfix());
}

TEST(TPostfix, cant_create_infix_with_wrong_parentheses)
{
	ASSERT_NO_THROW(TPostfix p("(5+6)"));
}

TEST(TPostfix, can_getinfix_with_equal_count_brackets_postfix)
{
	TPostfix p("((2+(2-3+1)))");
	ASSERT_NO_THROW(p.GetPostfix());
}

TEST(TPostfix, can_create_right_postfix)
{
	TPostfix p("2+5");
	EXPECT_EQ("2 5 +", p.ToPostfix());
}

TEST(TPostfix, can_calculate_postfix)
{
	TPostfix p("2+5");
	p.ToPostfix();
	EXPECT_EQ(7, p.Calculate(p.ToPostfix()));
}

