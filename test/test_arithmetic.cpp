// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"

TEST(TPostfix, can_create_postfix) {
	ASSERT_NO_THROW(TPostfix a);
}
TEST(TPostfix, can_add_infix) {
	TPostfix a;
	a.SetInfix("4 + 5");
	EXPECT_EQ("4+5", a.GetInfix());
}
TEST(TPostfix, can_get_postfix) {
	TPostfix a("2 + 5");
	EXPECT_EQ("2 5+", a.GetPostfix());
}
TEST(TPostfix, can_get_postfix_from_expression_with_two_characters_of_the_same_order) {
	TPostfix a("1 + 2 * 3 / 4 - 5");
	EXPECT_EQ("1 2 3 4/* -5++", a.GetPostfix());
}
TEST(TPostfix, can_create_postfix_from_postfix) {
	TPostfix a("2 + 5");
	a.GetPostfix();
	TPostfix b(a);
	EXPECT_EQ("2+5", b.GetInfix());
	EXPECT_EQ("2 5+", b.GetPostfix());
}
TEST(TPostfix, can_assign_postfix) {
	TPostfix a("2 + 5");
	TPostfix b;
	b = a;
	EXPECT_EQ("2+5", b.GetInfix());
	EXPECT_EQ("2 5+", b.GetPostfix());
}
TEST(TPostfix, can_calculate_double) {
	TPostfix a("1.11 + 10.89");
	double g = a.Calculate();
	EXPECT_EQ(12, g);
}
TEST(TPostfix, can_calculate_simple_expression) {
	TPostfix p("11 - 4");
	EXPECT_EQ(7, p.Calculate());
}
TEST(TPostfix, can_calculate_expression_with_brackets) {
	TPostfix a("20 / (4 + 1)");
	EXPECT_EQ(4, a.Calculate());
}
TEST(TPostfix, can_calculate_expression_with_two_characters_of_the_same_order) {
	TPostfix a("1 + 2 * 3 / 4 - 5");
	EXPECT_EQ(-2.5, a.Calculate());
}
TEST(TPostfix, can_not_divide_by_zero) {
	TPostfix a("20 / 0");
	ASSERT_ANY_THROW(a.Calculate());
}
TEST(TPostfix, can_reset_expression) {
	TPostfix a("4 - 5");
	a.SetInfix("1 - 3");
	EXPECT_EQ(-2, a.Calculate());
}
TEST(TPostfix, throw_if_expression_has_non_number_member) {
	ASSERT_ANY_THROW(TPostfix a("5 + 4 - 3 + a"));
}
TEST(TPostfix, can_transform_multi_dividing) {
	TPostfix a("1+2/4/5-5");
	EXPECT_EQ("1 2 4/ 5/ -5++", a.GetPostfix());
	EXPECT_EQ(-3.9000000000000004, a.Calculate());// ???? ????????? ???????????
}
TEST(TPostfix, can_transform_multi_dividing_add) {
	TPostfix a("100/2/2/5/5");
	EXPECT_EQ(1, a.Calculate());
}
TEST(TPostfix, can_transform_combo) {
	TPostfix a("1+2/4*5-5");
	EXPECT_EQ("1 2 4/ 5* -5++", a.GetPostfix());
}