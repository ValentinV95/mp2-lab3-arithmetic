#include "arithmetic.h"
#include <string>
#include <gtest.h>
using namespace std;

TEST(TLexeme, can_create_double)
{
	TLexeme a(31.0);
	EXPECT_NEAR(a.GetValue().elem, 31.0, 0.000001);
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
	vector<TLexeme> v = Create_lexeme_array("21 + (3 * 8) + 6 / 2 - 1");
	int i = 0;
	EXPECT_EQ(v[i++].GetType(), number);
	EXPECT_EQ(v[i++].GetType(), binary_operation);
	EXPECT_EQ(v[i++].GetType(), op_bracket);
	EXPECT_EQ(v[i++].GetType(), number);
	EXPECT_EQ(v[i++].GetType(), binary_operation);
	EXPECT_EQ(v[i++].GetType(), number);
	EXPECT_EQ(v[i++].GetType(), cl_bracket);
	EXPECT_EQ(v[i++].GetType(), binary_operation);
	EXPECT_EQ(v[i++].GetType(), number);
	EXPECT_EQ(v[i++].GetType(), binary_operation);
	EXPECT_EQ(v[i++].GetType(), number);
	EXPECT_EQ(v[i++].GetType(), binary_operation);
	EXPECT_EQ(v[i].GetType(), number);

	i = 0;
	EXPECT_NEAR(v[i++].GetValue().elem, 21.0, 0.00001);
	EXPECT_EQ(v[i++].GetValue().oper, '+');
	EXPECT_EQ(v[i++].GetValue().oper, '(');
	EXPECT_NEAR(v[i++].GetValue().elem, 3.0, 0.00001);
	EXPECT_EQ(v[i++].GetValue().oper, '*');
	EXPECT_NEAR(v[i++].GetValue().elem, 8.0, 0.00001);
	EXPECT_EQ(v[i++].GetValue().oper, ')');
	EXPECT_EQ(v[i++].GetValue().oper, '+');
	EXPECT_NEAR(v[i++].GetValue().elem, 6.0, 0.00001);
	EXPECT_EQ(v[i++].GetValue().oper, '/');
	EXPECT_NEAR(v[i++].GetValue().elem, 2.0, 0.00001);
	EXPECT_EQ(v[i++].GetValue().oper, '-');
	EXPECT_NEAR(v[i].GetValue().elem, 1.0, 0.00001);
}

TEST(Create_lexeme_array, can_create_lexeme_array_with_unary_minus_1)
{
	vector<TLexeme> v = Create_lexeme_array("-11 + 3 * (-2 + 1)");
	int i = 0;
	EXPECT_NEAR(v[i++].GetValue().elem, -11.0, 0.00001);
	EXPECT_EQ(v[i++].GetValue().oper, '+');
	EXPECT_NEAR(v[i++].GetValue().elem, 3.0, 0.00001);
	EXPECT_EQ(v[i++].GetValue().oper, '*');
	EXPECT_EQ(v[i++].GetValue().oper, '(');
	EXPECT_NEAR(v[i++].GetValue().elem, -2.0, 0.00001);
	EXPECT_EQ(v[i++].GetValue().oper, '+');
	EXPECT_NEAR(v[i++].GetValue().elem, 1.0, 0.00001);
	EXPECT_EQ(v[i].GetValue().oper, ')');
}

TEST(Create_lexeme_array, can_create_lexeme_array_with_unary_minus_2)
{
	vector<TLexeme> v = Create_lexeme_array("-(3 * 7)");
	int i = 0;
	EXPECT_EQ(v[i++].GetValue().oper, '-');
	EXPECT_EQ(v[i - 1].GetType(), unary_operation);
	EXPECT_EQ(v[i++].GetValue().oper, '(');
	EXPECT_NEAR(v[i++].GetValue().elem, 3.0, 0.00001);
	EXPECT_EQ(v[i++].GetValue().oper, '*');
	EXPECT_NEAR(v[i++].GetValue().elem, 7.0, 0.00001);
	EXPECT_EQ(v[i].GetValue().oper, ')');
}

TEST(Create_lexeme_array, can_create_lexeme_array_with_unary_minus_3)
{
	vector<TLexeme> v = Create_lexeme_array("2 + 4 - (0.001 * 15) - 6");
	int i = 0;
	EXPECT_NEAR(v[i++].GetValue().elem, 2.0, 0.00001);
	EXPECT_EQ(v[i++].GetValue().oper, '+');
	EXPECT_NEAR(v[i++].GetValue().elem, 4.0, 0.00001);
	EXPECT_EQ(v[i++].GetValue().oper, '-');
	EXPECT_EQ(v[i - 1].GetType(), unary_operation);
	EXPECT_EQ(v[i++].GetValue().oper, '(');
	EXPECT_NEAR(v[i++].GetValue().elem, 0.001, 0.00001);
	EXPECT_EQ(v[i++].GetValue().oper, '*');
	EXPECT_NEAR(v[i++].GetValue().elem, 15.0, 0.00001);
	EXPECT_EQ(v[i++].GetValue().oper, ')');
	EXPECT_EQ(v[i++].GetValue().oper, '-');
	EXPECT_EQ(v[i - 1].GetType(), binary_operation);
	EXPECT_NEAR(v[i++].GetValue().elem, 6.0, 0.00001);
}

TEST(Create_lexeme_array, can_create_lexeme_array_with_double_numbers)
{
	vector<TLexeme> v = Create_lexeme_array("5.05 + 0.15 - 0.00001 * (-0.32 + 6.25)");
	int i = 0;
	EXPECT_NEAR(v[i++].GetValue().elem, 5.05, 0.00001);
	EXPECT_EQ(v[i++].GetValue().oper, '+');
	EXPECT_NEAR(v[i++].GetValue().elem, 0.15, 0.00001);
	EXPECT_EQ(v[i++].GetValue().oper, '-');
	EXPECT_NEAR(v[i++].GetValue().elem, 0.00001, 0.0000001);
	EXPECT_EQ(v[i++].GetValue().oper, '*');
	EXPECT_EQ(v[i++].GetValue().oper, '(');
	EXPECT_NEAR(v[i++].GetValue().elem, -0.32, 0.00001);
	EXPECT_EQ(v[i++].GetValue().oper, '+');
	EXPECT_NEAR(v[i++].GetValue().elem, 6.25, 0.00001);
	EXPECT_EQ(v[i++].GetValue().oper, ')');
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
	vector<TLexeme> v;
	TLexeme t(21.0);
	v.push_back(t);
	TLexeme t1(3.0);
	v.push_back(t1);
	TLexeme t2(8.0);
	v.push_back(t2);
	TLexeme t3('*');
	v.push_back(t3);
	TLexeme t4(6.0);
	v.push_back(t4);
	TLexeme t5('+');
	v.push_back(t5);
	TLexeme t6(2.0);
	v.push_back(t6);
	TLexeme t7('/');
	v.push_back(t7);
	TLexeme t8('+');
	v.push_back(t8);
	TLexeme t9(1.0);
	v.push_back(t9);
	TLexeme t10('-');
	v.push_back(t10);
	EXPECT_NEAR(35.0, Solver(v), 0.00000001);
}

TEST(Solver, can_solve_expression_with_binary_operations_2)
{
	// 15 + 31 - (20 / 4) * 3
	// 15 31 + 20 4 / 3 * -
	vector<TLexeme> v;
	TLexeme t(15.0);
	v.push_back(t);
	TLexeme t1(31.0);
	v.push_back(t1);
	TLexeme t2('+');
	v.push_back(t2);
	TLexeme t3(20.0);
	v.push_back(t3);
	TLexeme t4(4.0);
	v.push_back(t4);
	TLexeme t5('/');
	v.push_back(t5);
	TLexeme t6(3.0);
	v.push_back(t6);
	TLexeme t7('*');
	v.push_back(t7);
	TLexeme t8('-');
	v.push_back(t8);
	EXPECT_NEAR(31.0, Solver(v), 0.00000001);
}

TEST(Solver, can_solve_expression_with_unary_operations_1)
{
	// -(3 * 7)
	// 3 7 * -
	vector<TLexeme> v;
	TLexeme t(3.0);
	v.push_back(t);
	TLexeme t1(7.0);
	v.push_back(t1);
	TLexeme t2('*');
	v.push_back(t2);
	TLexeme t3('-', unary_operation);
	v.push_back(t3);
	EXPECT_NEAR(-21.0, Solver(v), 0.00000001);
}

TEST(Solver, can_solve_expression_with_unary_operations_2)
{
	// 2 + 4 - (-(0.001 * 15)) - 6
	// 2 4 + 0.001 15 * - - 6 -
	vector<TLexeme> v;
	TLexeme t(2.0);
	v.push_back(t);
	TLexeme t1(4.0);
	v.push_back(t1);
	TLexeme t2('+');
	v.push_back(t2);
	TLexeme t3(0.001);
	v.push_back(t3);
	TLexeme t4(15.0);
	v.push_back(t4);
	TLexeme t5('*');
	v.push_back(t5);
	TLexeme t6('-', unary_operation);
	v.push_back(t6);
	TLexeme t7('-');
	v.push_back(t7);
	TLexeme t8(6.0);
	v.push_back(t8);
	TLexeme t9('-');
	v.push_back(t9);
	EXPECT_NEAR(0.015, Solver(v), 0.00000001);
}