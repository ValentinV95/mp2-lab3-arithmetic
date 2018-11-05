#include "arithmetic.h"
#include <gtest.h>
using namespace std;

const double eps = 1e-7;

TEST(TLexeme, can_create_double)
{
	TLexeme a(31.0);
	EXPECT_NEAR(a.GetValue().elem, 31.0, eps);
	EXPECT_EQ(a.GetType(), number);
}

TEST(TLexeme, can_create_binary_operation)
{
	TLexeme a('*');
	EXPECT_EQ(a.GetValue().oper, '*');
	EXPECT_EQ(a.GetType(), binary_operation);
}

TEST(TLexeme, can_create_opened_bracket)
{
	TLexeme a('(');
	EXPECT_EQ(a.GetValue().oper, '(');
	EXPECT_EQ(a.GetType(), op_bracket);
}

TEST(TLexeme, can_create_closed_bracket)
{
	TLexeme a(')');
	EXPECT_EQ(a.GetValue().oper, ')');
	EXPECT_EQ(a.GetType(), cl_bracket);
}

TEST(TLexeme, can_create_without_parameters)
{
	TLexeme a;
	EXPECT_EQ(a.GetType(), no_type);
}

TEST(Create_lexeme_array, can_create_lexeme_array)
{
	vector<pair<TLexeme, int>> v = Create_lexeme_array("21 + (3 * 8) + 6 / 2 - 1");
	int i = 0;
	EXPECT_EQ(v[i++].first.GetType(), number);
	EXPECT_EQ(v[i++].first.GetType(), binary_operation);
	EXPECT_EQ(v[i++].first.GetType(), op_bracket);
	EXPECT_EQ(v[i++].first.GetType(), number);
	EXPECT_EQ(v[i++].first.GetType(), binary_operation);
	EXPECT_EQ(v[i++].first.GetType(), number);
	EXPECT_EQ(v[i++].first.GetType(), cl_bracket);
	EXPECT_EQ(v[i++].first.GetType(), binary_operation);
	EXPECT_EQ(v[i++].first.GetType(), number);
	EXPECT_EQ(v[i++].first.GetType(), binary_operation);
	EXPECT_EQ(v[i++].first.GetType(), number);
	EXPECT_EQ(v[i++].first.GetType(), binary_operation);
	EXPECT_EQ(v[i].first.GetType(), number);

	i = 0;
	EXPECT_NEAR(v[i++].first.GetValue().elem, 21.0, eps);
	EXPECT_EQ(v[i++].first.GetValue().oper, '+');
	EXPECT_EQ(v[i++].first.GetValue().oper, '(');
	EXPECT_NEAR(v[i++].first.GetValue().elem, 3.0, eps);
	EXPECT_EQ(v[i++].first.GetValue().oper, '*');
	EXPECT_NEAR(v[i++].first.GetValue().elem, 8.0, eps);
	EXPECT_EQ(v[i++].first.GetValue().oper, ')');
	EXPECT_EQ(v[i++].first.GetValue().oper, '+');
	EXPECT_NEAR(v[i++].first.GetValue().elem, 6.0, eps);
	EXPECT_EQ(v[i++].first.GetValue().oper, '/');
	EXPECT_NEAR(v[i++].first.GetValue().elem, 2.0, eps);
	EXPECT_EQ(v[i++].first.GetValue().oper, '-');
	EXPECT_NEAR(v[i].first.GetValue().elem, 1.0, eps);
}

TEST(Create_lexeme_array, can_create_lexeme_array_with_unary_minus_1)
{
	vector<pair<TLexeme, int>> v = Create_lexeme_array("-11 + 3 * (-2 + 1)");
	int i = 0;
	EXPECT_NEAR(v[i++].first.GetValue().elem, -11.0, eps);
	EXPECT_EQ(v[i++].first.GetValue().oper, '+');
	EXPECT_NEAR(v[i++].first.GetValue().elem, 3.0, eps);
	EXPECT_EQ(v[i++].first.GetValue().oper, '*');
	EXPECT_EQ(v[i++].first.GetValue().oper, '(');
	EXPECT_NEAR(v[i++].first.GetValue().elem, -2.0, eps);
	EXPECT_EQ(v[i++].first.GetValue().oper, '+');
	EXPECT_NEAR(v[i++].first.GetValue().elem, 1.0, eps);
	EXPECT_EQ(v[i].first.GetValue().oper, ')');
}

TEST(Create_lexeme_array, can_create_lexeme_array_with_unary_minus_2)
{
	vector<pair<TLexeme, int>> v = Create_lexeme_array("-(3 * 7)");
	int i = 0;
	EXPECT_EQ(v[i++].first.GetValue().oper, '-');
	EXPECT_EQ(v[i - 1].first.GetType(), unary_operation);
	EXPECT_EQ(v[i++].first.GetValue().oper, '(');
	EXPECT_NEAR(v[i++].first.GetValue().elem, 3.0, eps);
	EXPECT_EQ(v[i++].first.GetValue().oper, '*');
	EXPECT_NEAR(v[i++].first.GetValue().elem, 7.0, eps);
	EXPECT_EQ(v[i].first.GetValue().oper, ')');
}

TEST(Create_lexeme_array, can_create_lexeme_array_with_unary_minus_3)
{
	vector<pair<TLexeme, int>> v = Create_lexeme_array("2 + 4 - (0.001 * 15) - 6");
	int i = 0;
	EXPECT_NEAR(v[i++].first.GetValue().elem, 2.0, eps);
	EXPECT_EQ(v[i++].first.GetValue().oper, '+');
	EXPECT_NEAR(v[i++].first.GetValue().elem, 4.0, eps);
	EXPECT_EQ(v[i++].first.GetValue().oper, '-');
	EXPECT_EQ(v[i - 1].first.GetType(), unary_operation);
	EXPECT_EQ(v[i++].first.GetValue().oper, '(');
	EXPECT_NEAR(v[i++].first.GetValue().elem, 0.001, eps);
	EXPECT_EQ(v[i++].first.GetValue().oper, '*');
	EXPECT_NEAR(v[i++].first.GetValue().elem, 15.0, eps);
	EXPECT_EQ(v[i++].first.GetValue().oper, ')');
	EXPECT_EQ(v[i++].first.GetValue().oper, '-');
	EXPECT_EQ(v[i - 1].first.GetType(), binary_operation);
	EXPECT_NEAR(v[i++].first.GetValue().elem, 6.0, eps);
}

TEST(Create_lexeme_array, can_create_lexeme_array_with_double_numbers)
{
	vector<pair<TLexeme, int>> v = Create_lexeme_array("5.05 + 0.15 - 0.00001 * (-0.32 + 6.25)");
	int i = 0;
	EXPECT_NEAR(v[i++].first.GetValue().elem, 5.05, eps);
	EXPECT_EQ(v[i++].first.GetValue().oper, '+');
	EXPECT_NEAR(v[i++].first.GetValue().elem, 0.15, eps);
	EXPECT_EQ(v[i++].first.GetValue().oper, '-');
	EXPECT_NEAR(v[i++].first.GetValue().elem, 0.00001, eps);
	EXPECT_EQ(v[i++].first.GetValue().oper, '*');
	EXPECT_EQ(v[i++].first.GetValue().oper, '(');
	EXPECT_NEAR(v[i++].first.GetValue().elem, -0.32, eps);
	EXPECT_EQ(v[i++].first.GetValue().oper, '+');
	EXPECT_NEAR(v[i++].first.GetValue().elem, 6.25, eps);
	EXPECT_EQ(v[i++].first.GetValue().oper, ')');
}

TEST(Create_lexeme_array, can_not_create_lexeme_array_with_wrong_symbols)
{
	ASSERT_ANY_THROW(Create_lexeme_array("15z - 12a * 3"));
}

TEST(Create_lexeme_array, can_not_create_lexeme_array_with_wrong_numbers_1)
{
	ASSERT_ANY_THROW(Create_lexeme_array(".0125 + 4.0 * 2"));
}

TEST(Create_lexeme_array, can_not_create_lexeme_array_with_wrong_numbers_2)
{
	ASSERT_ANY_THROW(Create_lexeme_array("12.15 + 2.0 - 125."));
}

TEST(Create_lexeme_array, can_not_create_lexeme_array_with_wrong_numbers_3)
{
	ASSERT_ANY_THROW(Create_lexeme_array("17 * 25. - 17"));
}

TEST(Create_lexeme_array, can_not_create_lexeme_array_with_wrong_numbers_4)
{
	ASSERT_ANY_THROW(Create_lexeme_array("674 * .15 - 6"));
}

TEST(Create_lexeme_array, can_not_create_lexeme_array_with_wrong_numbers_5)
{
	ASSERT_ANY_THROW(Create_lexeme_array("2 * (.2 - 6)"));
}

TEST(Create_lexeme_array, can_not_create_lexeme_array_with_wrong_numbers_6)
{
	ASSERT_ANY_THROW(Create_lexeme_array("28.15 * (2.2 - 15.) - 1"));
}

TEST(Solver, can_solve_expression_with_binary_operations_1)
{
	// 21 + (3 * 8 + 6) / 2 - 1
	// 21 3 8 * 6 + 2 / + 1 -
	vector<pair<TLexeme, int>> v;
	pair<TLexeme, int>t(21.0, 0);
	v.push_back(t);
	pair<TLexeme, int>t1(3.0, 0);
	v.push_back(t1);
	pair<TLexeme, int>t2(8.0, 0);
	v.push_back(t2);
	pair<TLexeme, int>t3('*', 0);
	v.push_back(t3);
	pair<TLexeme, int>t4(6.0, 0);
	v.push_back(t4);
	pair<TLexeme, int>t5('+', 0);
	v.push_back(t5);
	pair<TLexeme, int>t6(2.0, 0);
	v.push_back(t6);
	pair<TLexeme, int>t7('/', 0);
	v.push_back(t7);
	pair<TLexeme, int>t8('+', 0);
	v.push_back(t8);
	pair<TLexeme, int>t9(1.0, 0);
	v.push_back(t9);
	pair<TLexeme, int>t10('-', 0);
	v.push_back(t10);
	EXPECT_NEAR(35.0, Solver(v), eps);
}

TEST(Solver, can_solve_expression_with_binary_operations_2)
{
	// 15 + 31 - (20 / 4) * 3
	// 15 31 + 20 4 / 3 * -
	vector<pair<TLexeme, int>> v;
	pair<TLexeme, int>t(15.0, 0);
	v.push_back(t);
	pair<TLexeme, int>t1(31.0, 0);
	v.push_back(t1);
	pair<TLexeme, int>t2('+', 0);
	v.push_back(t2);
	pair<TLexeme, int>t3(20.0, 0);
	v.push_back(t3);
	pair<TLexeme, int>t4(4.0, 0);
	v.push_back(t4);
	pair<TLexeme, int>t5('/', 0);
	v.push_back(t5);
	pair<TLexeme, int>t6(3.0, 0);
	v.push_back(t6);
	pair<TLexeme, int>t7('*', 0);
	v.push_back(t7);
	pair<TLexeme, int>t8('-', 0);
	v.push_back(t8);
	EXPECT_NEAR(31.0, Solver(v), eps);
}

TEST(Solver, can_solve_expression_with_unary_minus_1)
{
	// -(3 * 7)
	// 3 7 * -
	vector<pair<TLexeme, int>> v;
	pair<TLexeme, int>t(3.0, 0);
	v.push_back(t);
	pair<TLexeme, int>t1(7.0, 0);
	v.push_back(t1);
	pair<TLexeme, int>t2('*', 0);
	v.push_back(t2);
	TLexeme temp('-', unary_operation);
	pair<TLexeme, int>t3(temp, 0);
	v.push_back(t3);
	EXPECT_NEAR(-21.0, Solver(v), eps);
}

TEST(Solver, can_solve_expression_with_unary_minus_2)
{
	// 2 + 4 - (-(0.001 * 15)) - 6
	// 2 4 + 0.001 15 * - - 6 -
	vector<pair<TLexeme, int>> v;
	pair<TLexeme, int>t(2.0, 0);
	v.push_back(t);
	pair<TLexeme, int>t1(4.0, 0);
	v.push_back(t1);
	pair<TLexeme, int>t2('+', 0);
	v.push_back(t2);
	pair<TLexeme, int>t3(0.001, 0);
	v.push_back(t3);
	pair<TLexeme, int>t4(15.0, 0);
	v.push_back(t4);
	pair<TLexeme, int>t5('*', 0);
	v.push_back(t5);
	TLexeme temp('-', unary_operation);
	pair<TLexeme, int>t6(temp, 0);
	v.push_back(t6);
	pair<TLexeme, int>t7('-', 0);
	v.push_back(t7);
	pair<TLexeme, int>t8(6.0, 0);
	v.push_back(t8);
	pair<TLexeme, int>t9('-', 0);
	v.push_back(t9);
	EXPECT_NEAR(0.015, Solver(v), eps);
}

TEST(Solver, can_solve_expression_with_unary_minus_3)
{
	// -((2 * 8) - 8)
	// 2 8 * 8 - -
	vector<pair<TLexeme, int>> v;
	pair<TLexeme, int>t(2.0, 0);
	v.push_back(t);
	pair<TLexeme, int>t1(8.0, 0);
	v.push_back(t1);
	pair<TLexeme, int>t2('*', 0);
	v.push_back(t2);
	pair<TLexeme, int>t3(8.0, 0);
	v.push_back(t3);
	pair<TLexeme, int>t4('-', 0);
	v.push_back(t4);
	TLexeme temp('-', unary_operation);
	pair<TLexeme, int>t5(temp, 0);
	v.push_back(t5);
	EXPECT_NEAR(-8.0, Solver(v), eps);
}

TEST(Solver, can_solve_expression_with_unary_minus_4)
{
	// 6*(-6*(-6*1))
	// 6 6 - 6 - 1 * * *
	vector<pair<TLexeme, int>> v;
	pair<TLexeme, int>t(6.0, 0);
	v.push_back(t);
	pair<TLexeme, int>t1(6.0, 0);
	v.push_back(t1);
	TLexeme temp1('-', unary_operation);
	pair<TLexeme, int>t2(temp1, 0);
	v.push_back(t2);
	pair<TLexeme, int>t3(6.0, 0);
	v.push_back(t3);
	TLexeme temp2('-', unary_operation);
	pair<TLexeme, int>t4(temp2, 0);
	v.push_back(t4);
	pair<TLexeme, int>t5(1.0, 0);
	v.push_back(t5);
	pair<TLexeme, int>t6('*', 0);
	v.push_back(t6);
	pair<TLexeme, int>t7('*', 0);
	v.push_back(t7);
	pair<TLexeme, int>t8('*', 0);
	v.push_back(t8);
	EXPECT_NEAR(216.0, Solver(v), eps);
}

TEST(Solver, can_solve_expression_with_unary_minus_5)
{
	// 877.01 - 98.254 * (456.0 / 741.7) + 97 / 3.02 * 798.42 + (-(-15))
	// 877.01 98.254 456.0 741.7 / * - 97 3.02 / 798.42 * + 15 - - +
	vector<pair<TLexeme, int>> v;
	pair<TLexeme, int>t(877.01, 0);
	v.push_back(t);
	pair<TLexeme, int>t1(98.254, 0);
	v.push_back(t1);
	pair<TLexeme, int>t2(456.0, 0);
	v.push_back(t2);
	pair<TLexeme, int>t3(741.7, 0);
	v.push_back(t3);
	pair<TLexeme, int>t4('/', 0);
	v.push_back(t4);
	pair<TLexeme, int>t5('*', 0);
	v.push_back(t5);
	pair<TLexeme, int>t6('-', 0);
	v.push_back(t6);
	pair<TLexeme, int>t7(97.0, 0);
	v.push_back(t7);
	pair<TLexeme, int>t8(3.02, 0);
	v.push_back(t8);
	pair<TLexeme, int>t9('/', 0);
	v.push_back(t9);
	pair<TLexeme, int>t10(798.42, 0);
	v.push_back(t10);
	pair<TLexeme, int>t11('*', 0);
	v.push_back(t11);
	pair<TLexeme, int>t12('+', 0);
	v.push_back(t12);
	pair<TLexeme, int>t13(15.0, 0);
	v.push_back(t13);
	TLexeme temp1('-', unary_operation);
	pair<TLexeme, int>t14(temp1, 0);
	v.push_back(t14);
	TLexeme temp2('-', unary_operation);
	pair<TLexeme, int>t15(temp2, 0);
	v.push_back(t15);
	pair<TLexeme, int>t16('+', 0);
	v.push_back(t16);
	EXPECT_NEAR(26476.2189586, Solver(v), eps);
}

TEST(Create_RPN_array, can_create_RPN_array_with_binary_operations)
{
	//1 + (2 - 5) * 4
	vector<pair<TLexeme, int>> v;
	pair<TLexeme, int>t(1.0, 0);
	v.push_back(t);
	pair<TLexeme, int>t1('+', 0);
	v.push_back(t1);
	pair<TLexeme, int>t2('(', 0);
	v.push_back(t2);
	pair<TLexeme, int>t3(2.0, 0);
	v.push_back(t3);
	pair<TLexeme, int>t4('-', 0);
	v.push_back(t4);
	pair<TLexeme, int>t5(5.0, 0);
	v.push_back(t5);
	pair<TLexeme, int>t6(')', 0);
	v.push_back(t6);
	pair<TLexeme, int>t7('*', 0);
	v.push_back(t7);
	pair<TLexeme, int>t8(4.0, 0);
	v.push_back(t8);
	vector<pair<TLexeme, int>> ans = Create_RPN_array(v);
	// 1 2 5 - 4 * +
	int i = 0;
	EXPECT_NEAR(ans[i++].first.GetValue().elem, 1.0, eps);
	EXPECT_NEAR(ans[i++].first.GetValue().elem, 2.0, eps);
	EXPECT_NEAR(ans[i++].first.GetValue().elem, 5.0, eps);
	EXPECT_EQ(ans[i++].first.GetValue().oper, '-');
	EXPECT_NEAR(ans[i++].first.GetValue().elem, 4.0, eps);
	EXPECT_EQ(ans[i++].first.GetValue().oper, '*');
	EXPECT_EQ(ans[i].first.GetValue().oper, '+');
}

TEST(Create_RPN_array, can_create_RPN_array_with_unary_minus_1)
{
	//2 + 4 - (-(0.001 * 15)) - 6
	vector<pair<TLexeme, int>> v;
	pair<TLexeme, int>t(2.0, 0);
	v.push_back(t);
	pair<TLexeme, int>t1('+', 0);
	v.push_back(t1);
	pair<TLexeme, int>t2(4.0, 0);
	v.push_back(t2);
	pair<TLexeme, int>t3('-', 0);
	v.push_back(t3);
	pair<TLexeme, int>t4('(', 0);
	v.push_back(t4);
	TLexeme temp('-', unary_operation);
	pair<TLexeme, int>t5(temp, 0);
	v.push_back(t5);
	pair<TLexeme, int>t6('(', 0);
	v.push_back(t6);
	pair<TLexeme, int>t7(0.001, 0);
	v.push_back(t7);
	pair<TLexeme, int>t8('*', 0);
	v.push_back(t8);
	pair<TLexeme, int>t9(15.0, 0);
	v.push_back(t9);
	pair<TLexeme, int>t10(')', 0);
	v.push_back(t10);
	pair<TLexeme, int>t11(')', 0);
	v.push_back(t11);
	pair<TLexeme, int>t12('-', 0);
	v.push_back(t12);
	pair<TLexeme, int>t13(6.0, 0);
	v.push_back(t13);
	vector<pair<TLexeme, int>> ans = Create_RPN_array(v);
	// 2 4 + 0.001 15 * - - 6 -
	int i = 0;
	EXPECT_NEAR(ans[i++].first.GetValue().elem, 2.0, eps);
	EXPECT_NEAR(ans[i++].first.GetValue().elem, 4.0, eps);
	EXPECT_EQ(ans[i++].first.GetValue().oper, '+');
	EXPECT_NEAR(ans[i++].first.GetValue().elem, 0.001, eps);
	EXPECT_NEAR(ans[i++].first.GetValue().elem, 15.0, eps);
	EXPECT_EQ(ans[i++].first.GetValue().oper, '*');
	EXPECT_EQ(ans[i++].first.GetValue().oper, '-');
	EXPECT_EQ(ans[i - 1].first.GetType(), unary_operation);
	EXPECT_EQ(ans[i++].first.GetValue().oper, '-');
	EXPECT_NEAR(ans[i++].first.GetValue().elem, 6.0, eps);
	EXPECT_EQ(ans[i].first.GetValue().oper, '-');
}

TEST(Create_RPN_array, can_create_RPN_array_with_unary_minus_2)
{
	// -((2 * 8) - 8)
	vector<pair<TLexeme, int>> v;
	TLexeme temp('-', unary_operation);
	pair<TLexeme, int>t(temp, 0);
	v.push_back(t);
	pair<TLexeme, int>t1('(', 0);
	v.push_back(t1);
	pair<TLexeme, int>t2('(', 0);
	v.push_back(t2);
	pair<TLexeme, int>t3(2.0, 0);
	v.push_back(t3);
	pair<TLexeme, int>t4('*', 0);
	v.push_back(t4);
	pair<TLexeme, int>t5(8.0, 0);
	v.push_back(t5);
	pair<TLexeme, int>t6(')', 0);
	v.push_back(t6);
	pair<TLexeme, int>t7('-', 0);
	v.push_back(t7);
	pair<TLexeme, int>t8(8.0, 0);
	v.push_back(t8);
	pair<TLexeme, int>t9(')', 0);
	v.push_back(t9);
	vector<pair<TLexeme, int>> ans = Create_RPN_array(v);
	// 2 8 * 8 - -
	int i = 0;
	EXPECT_NEAR(ans[i++].first.GetValue().elem, 2.0, eps);
	EXPECT_NEAR(ans[i++].first.GetValue().elem, 8.0, eps);
	EXPECT_EQ(ans[i++].first.GetValue().oper, '*');
	EXPECT_NEAR(ans[i++].first.GetValue().elem, 8.0, eps);
	EXPECT_EQ(ans[i++].first.GetValue().oper, '-');
	EXPECT_EQ(ans[i].first.GetValue().oper, '-');
	EXPECT_EQ(ans[i].first.GetType(), unary_operation);
}

TEST(Create_RPN_array, can_create_RPN_array_with_unary_minus_3)
{
	// 6*(-6*(-6*1))
	vector<pair<TLexeme, int>> v;
	pair<TLexeme, int>t(6.0, 0);
	v.push_back(t);
	pair<TLexeme, int>t1('*', 0);
	v.push_back(t1);
	pair<TLexeme, int>t2('(', 0);
	v.push_back(t2);
	TLexeme temp1('-', unary_operation);
	pair<TLexeme, int>t3(temp1, 0);
	v.push_back(t3);
	pair<TLexeme, int>t4(6.0, 0);
	v.push_back(t4);
	pair<TLexeme, int>t5('*', 0);
	v.push_back(t5);
	pair<TLexeme, int>t6('(', 0);
	v.push_back(t6);
	TLexeme temp2('-', unary_operation);
	pair<TLexeme, int>t7(temp2, 0);
	v.push_back(t7);
	pair<TLexeme, int>t8(6.0, 0);
	v.push_back(t8);
	pair<TLexeme, int>t9('*', 0);
	v.push_back(t9);
	pair<TLexeme, int>t10(1.0, 0);
	v.push_back(t10);
	pair<TLexeme, int>t11(')', 0);
	v.push_back(t11);
	pair<TLexeme, int>t12(')', 0);
	v.push_back(t12);
	vector<pair<TLexeme, int>> ans = Create_RPN_array(v);
	// 6 6 - 6 - 1 * * *
	int i = 0;
	EXPECT_NEAR(ans[i++].first.GetValue().elem, 6.0, eps);
	EXPECT_NEAR(ans[i++].first.GetValue().elem, 6.0, eps);
	EXPECT_EQ(ans[i++].first.GetValue().oper, '-');
	EXPECT_EQ(ans[i - 1].first.GetType(), unary_operation);
	EXPECT_NEAR(ans[i++].first.GetValue().elem, 6.0, eps);
	EXPECT_EQ(ans[i++].first.GetValue().oper, '-');
	EXPECT_EQ(ans[i - 1].first.GetType(), unary_operation);
	EXPECT_NEAR(ans[i++].first.GetValue().elem, 1.0, eps);
	EXPECT_EQ(ans[i++].first.GetValue().oper, '*');
	EXPECT_EQ(ans[i++].first.GetValue().oper, '*');
	EXPECT_EQ(ans[i].first.GetValue().oper, '*');
}

TEST(New_line_without_spaces, can_make_string_without_spaces_1)
{
	string a = "12    - 15+       (1 -    11)/      1";
	EXPECT_EQ(New_line_without_spaces(a), "12-15+(1-11)/1");
}

TEST(New_line_without_spaces, can_make_string_without_spaces_2)
{
	string a = "1+2-15*2/(2-3*1)";
	EXPECT_EQ(New_line_without_spaces(a), "1+2-15*2/(2-3*1)");
}

TEST(New_line_without_spaces, can_make_string_without_spaces_3)
{
	string a = "0.    5 - 112         * (-      0.1)";
	EXPECT_EQ(New_line_without_spaces(a), "0.5-112*(-0.1)");
}

TEST(Сonverting_number, can_convert_positive_number_1)
{
	EXPECT_NEAR(Сonverting_number("15.1257", 0, positive), 15.1257, eps);
}

TEST(Сonverting_number, can_convert_positive_number_2)
{
	EXPECT_NEAR(Сonverting_number("1255125", 0, positive), 1255125, eps);
}

TEST(Сonverting_number, can_convert_negative_number_1)
{
	EXPECT_NEAR(Сonverting_number("0.133", 0, negative), -0.133, eps);
}

TEST(Сonverting_number, can_convert_negative_number_2)
{
	EXPECT_NEAR(Сonverting_number("-999", 0, positive), -999, eps);
}

TEST(Сonverting_number, can_not_convert_wrong_number_1)
{
	ASSERT_ANY_THROW(Сonverting_number(".0152", 0, positive));
}

TEST(Сonverting_number, can_not_convert_wrong_number_2)
{
	ASSERT_ANY_THROW(Сonverting_number("125.", 0, negative));
}

TEST(Check_number, can_create_positive_number_from_string)
{
	int i = 2;
	pair<TLexeme, int>ans = make_pair(Check_number("-(125.6)", i, positive), 0);
	EXPECT_EQ(ans.first.GetType(), number);
	EXPECT_NEAR(ans.first.GetValue().elem, 125.6, eps);
}

TEST(Check_number, can_create_negative_number_from_string)
{
	int i = 7;
	pair<TLexeme, int>ans = make_pair(Check_number("2+28*(-3+1)", i, negative), 0);
	EXPECT_EQ(ans.first.GetType(), number);
	EXPECT_NEAR(ans.first.GetValue().elem, -3, eps);
}

TEST(Error_checking, no_exceptions_1)
{
	//2 + 4 - (-(0.001 * 15)) - 6
	vector<pair<TLexeme, int>> v;
	pair<TLexeme, int>t(2.0, 0);
	v.push_back(t);
	pair<TLexeme, int>t1('+', 0);
	v.push_back(t1);
	pair<TLexeme, int>t2(4.0, 0);
	v.push_back(t2);
	pair<TLexeme, int>t3('-', 0);
	v.push_back(t3);
	pair<TLexeme, int>t4('(', 0);
	v.push_back(t4);
	TLexeme temp('-', unary_operation);
	pair<TLexeme, int>t5(temp, 0);
	v.push_back(t5);
	pair<TLexeme, int>t6('(', 0);
	v.push_back(t6);
	pair<TLexeme, int>t7(0.001, 0);
	v.push_back(t7);
	pair<TLexeme, int>t8('*', 0);
	v.push_back(t8);
	pair<TLexeme, int>t9(15.0, 0);
	v.push_back(t9);
	pair<TLexeme, int>t10(')', 0);
	v.push_back(t10);
	pair<TLexeme, int>t11(')', 0);
	v.push_back(t11);
	pair<TLexeme, int>t12('-', 0);
	v.push_back(t12);
	pair<TLexeme, int>t13(6.0, 0);
	v.push_back(t13);
	ASSERT_NO_THROW(Error_checking(v));
}

TEST(Error_checking, no_exceptions_2)
{
	// 6*(-6*(-6*1))
	vector<pair<TLexeme, int>> v;
	pair<TLexeme, int>t(6.0, 0);
	v.push_back(t);
	pair<TLexeme, int>t1('*', 0);
	v.push_back(t1);
	pair<TLexeme, int>t2('(', 0);
	v.push_back(t2);
	TLexeme temp1('-', unary_operation);
	pair<TLexeme, int>t3(temp1, 0);
	v.push_back(t3);
	pair<TLexeme, int>t4(6.0, 0);
	v.push_back(t4);
	pair<TLexeme, int>t5('*', 0);
	v.push_back(t5);
	pair<TLexeme, int>t6('(', 0);
	v.push_back(t6);
	TLexeme temp2('-', unary_operation);
	pair<TLexeme, int>t7(temp2, 0);
	v.push_back(t7);
	pair<TLexeme, int>t8(6.0, 0);
	v.push_back(t8);
	pair<TLexeme, int>t9('*', 0);
	v.push_back(t9);
	pair<TLexeme, int>t10(1.0, 0);
	v.push_back(t10);
	pair<TLexeme, int>t11(')', 0);
	v.push_back(t11);
	pair<TLexeme, int>t12(')', 0);
	v.push_back(t12);
	ASSERT_NO_THROW(Error_checking(v));
}

TEST(Error_checking, no_exceptions_3)
{
	// -((2 * 8) - 8)
	vector<pair<TLexeme, int>> v;
	TLexeme temp('-', unary_operation);
	pair<TLexeme, int>t(temp, 0);
	v.push_back(t);
	pair<TLexeme, int>t1('(', 0);
	v.push_back(t1);
	pair<TLexeme, int>t2('(', 0);
	v.push_back(t2);
	pair<TLexeme, int>t3(2.0, 0);
	v.push_back(t3);
	pair<TLexeme, int>t4('*', 0);
	v.push_back(t4);
	pair<TLexeme, int>t5(8.0, 0);
	v.push_back(t5);
	pair<TLexeme, int>t6(')', 0);
	v.push_back(t6);
	pair<TLexeme, int>t7('-', 0);
	v.push_back(t7);
	pair<TLexeme, int>t8(8.0, 0);
	v.push_back(t8);
	pair<TLexeme, int>t9(')', 0);
	v.push_back(t9);
	ASSERT_NO_THROW(Error_checking(v));
}

TEST(Error_checking, no_exceprions_when_there_are_a_lot_of_brackets)
{
	string s = "(((1 * 4) -2))";
	s = New_line_without_spaces(s);
	vector<pair<TLexeme, int>> v = Create_lexeme_array(s);
	ASSERT_NO_THROW(Error_checking(v));
}

TEST(Error_checking, throws_an_exception_when_last_lexeme_is_wrong)
{
	// 1 + (2 - 5) * 4 -
	vector<pair<TLexeme, int>> v;
	pair<TLexeme, int>t(1.0, 0);
	v.push_back(t);
	pair<TLexeme, int>t1('+', 0);
	v.push_back(t1);
	pair<TLexeme, int>t2('(', 0);
	v.push_back(t2);
	pair<TLexeme, int>t3(2.0, 0);
	v.push_back(t3);
	pair<TLexeme, int>t4('-', 0);
	v.push_back(t4);
	pair<TLexeme, int>t5(5.0, 0);
	v.push_back(t5);
	pair<TLexeme, int>t6(')', 0);
	v.push_back(t6);
	pair<TLexeme, int>t7('*', 0);
	v.push_back(t7);
	pair<TLexeme, int>t8(4.0, 0);
	v.push_back(t8);
	pair<TLexeme, int>t9('-', 0);
	v.push_back(t9);
	ASSERT_ANY_THROW(Error_checking(v));
}

TEST(Error_checking, throws_an_exception_when_first_lexeme_is_wrong)
{
	// 2 1 + (2 - 5) * 4
	vector<pair<TLexeme, int>> v;
	pair<TLexeme, int>t(2.0, 0);
	v.push_back(t);
	pair<TLexeme, int>t1(1.0, 0);
	v.push_back(t1);
	pair<TLexeme, int>t2('+', 0);
	v.push_back(t2);
	pair<TLexeme, int>t3('(', 0);
	v.push_back(t3);
	pair<TLexeme, int>t4(2.0, 0);
	v.push_back(t4);
	pair<TLexeme, int>t5('-', 0);
	v.push_back(t5);
	pair<TLexeme, int>t6(5.0, 0);
	v.push_back(t6);
	pair<TLexeme, int>t7(')', 0);
	v.push_back(t7);
	pair<TLexeme, int>t8('*', 0);
	v.push_back(t8);
	pair<TLexeme, int>t9(4.0, 0);
	v.push_back(t9);
	ASSERT_ANY_THROW(Error_checking(v));
}

TEST(Error_checking, throws_an_exception_when_any_lexeme_is_wrong)
{
	// 1 + (2 - 5 +) * 4
	vector<pair<TLexeme, int>> v;
	pair<TLexeme, int>t(1.0, 0);
	v.push_back(t);
	pair<TLexeme, int>t1('+', 0);
	v.push_back(t1);
	pair<TLexeme, int>t2('(', 0);
	v.push_back(t2);
	pair<TLexeme, int>t3(2.0, 0);
	v.push_back(t3);
	pair<TLexeme, int>t4('-', 0);
	v.push_back(t4);
	pair<TLexeme, int>t5(5.0, 0);
	v.push_back(t5);
	pair<TLexeme, int>t6('+', 0);
	v.push_back(t6);
	pair<TLexeme, int>t7(')', 0);
	v.push_back(t7);
	pair<TLexeme, int>t8('*', 0);
	v.push_back(t8);
	pair<TLexeme, int>t9(4.0, 0);
	v.push_back(t9);
	ASSERT_ANY_THROW(Error_checking(v));
}

TEST(Error_checking, throws_an_exception_when_there_is_an_extra_opening_bracket)
{
	// 1 + ((2 - 5) * 4
	vector<pair<TLexeme, int>> v;
	pair<TLexeme, int>t(1.0, 0);
	v.push_back(t);
	pair<TLexeme, int>t1('+', 0);
	v.push_back(t1);
	pair<TLexeme, int>t2('(', 0);
	v.push_back(t2);
	pair<TLexeme, int>t3('(', 0);
	v.push_back(t3);
	pair<TLexeme, int>t4(2.0, 0);
	v.push_back(t4);
	pair<TLexeme, int>t5('-', 0);
	v.push_back(t5);
	pair<TLexeme, int>t6(5.0, 0);
	v.push_back(t6);
	pair<TLexeme, int>t7(')', 0);
	v.push_back(t7);
	pair<TLexeme, int>t8('*', 0);
	v.push_back(t8);
	pair<TLexeme, int>t9(4.0, 0);
	v.push_back(t9);
	ASSERT_ANY_THROW(Error_checking(v));
}

TEST(Error_checking, throws_an_exception_when_there_is_an_extra_closing_bracket)
{
	// 1 + (2) - 5) * 4
	vector<pair<TLexeme, int>> v;
	pair<TLexeme, int>t(1.0, 0);
	v.push_back(t);
	pair<TLexeme, int>t1('+', 0);
	v.push_back(t1);
	pair<TLexeme, int>t2('(', 0);
	v.push_back(t2);
	pair<TLexeme, int>t3(2.0, 0);
	v.push_back(t3);
	pair<TLexeme, int>t4(')', 0);
	v.push_back(t4);
	pair<TLexeme, int>t5('-', 0);
	v.push_back(t5);
	pair<TLexeme, int>t6(5.0, 0);
	v.push_back(t6);
	pair<TLexeme, int>t7(')', 0);
	v.push_back(t7);
	pair<TLexeme, int>t8('*', 0);
	v.push_back(t8);
	pair<TLexeme, int>t9(4.0, 0);
	v.push_back(t9);
	ASSERT_ANY_THROW(Error_checking(v));
}

TEST(Error_checking, throws_an_exception_when_the_brackets_are_swapped_1)
{
	// 1 + )2 - 5( * 4
	vector<pair<TLexeme, int>> v;
	pair<TLexeme, int>t(1.0, 0);
	v.push_back(t);
	pair<TLexeme, int>t1('+', 0);
	v.push_back(t1);
	pair<TLexeme, int>t2(')', 0);
	v.push_back(t2);
	pair<TLexeme, int>t3(2.0, 0);
	v.push_back(t3);
	pair<TLexeme, int>t4('-', 0);
	v.push_back(t4);
	pair<TLexeme, int>t5(5.0, 0);
	v.push_back(t5);
	pair<TLexeme, int>t6('(', 0);
	v.push_back(t6);
	pair<TLexeme, int>t7('*', 0);
	v.push_back(t7);
	pair<TLexeme, int>t8(4.0, 0);
	v.push_back(t8);
	ASSERT_ANY_THROW(Error_checking(v));
}

TEST(Error_checking, throws_an_exception_when_the_brackets_are_swapped_2)
{
	string s = "(()1 * 4) -2()";
	s = New_line_without_spaces(s);
	vector<pair<TLexeme, int>> v = Create_lexeme_array(s);
	ASSERT_ANY_THROW(Error_checking(v));
}

TEST(Calculate, can_calculate_1)
{
	ASSERT_NEAR(Calculate("1 - 12 * (27 - 6 + 0.1) / 12"), -20.1, eps);
}

TEST(Calculate, can_calculate_2)
{
	ASSERT_NEAR(Calculate("2 * (-4) + 15 / (6 - 5) * 13"), 187.0, eps);
}

TEST(Calculate, can_calculate_3)
{
	ASSERT_NEAR(Calculate("1.215235 -6.124 * 124.566 / 12.16"), -61.5184972368421, eps);
}

TEST(Calculate, can_not_calculate_wrong_expression_1)
{
	ASSERT_ANY_THROW(Calculate("1 - 14 * 2 / (14 - 2 * 7)"));
}

TEST(Calculate, can_not_calculate_wrong_expression_2)
{
	ASSERT_ANY_THROW(Calculate("2 + 6 * (-1 -)"));
}

TEST(Calculate, can_not_calculate_wrong_expression_3)
{
	ASSERT_ANY_THROW(Calculate("1^14 - 14 * 2"));
}

TEST(Calculate, can_not_calculate_wrong_expression_4)
{
	ASSERT_ANY_THROW(Calculate("(1 - (5 * 2()"));
}

TEST(Calculate, can_not_calculate_wrong_expression_5)
{
	ASSERT_ANY_THROW(Calculate("100 + (0 * (1 - (6 * 2))"));
}

