#include "arithmetic.h"
#include <string>
#include <gtest.h>
using namespace std;

TEST(TLexeme, can_create_double)
{
	TLexeme a(31.0);
	EXPECT_NEAR(a.GetValue().elem, 31.0, 1e-5);
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
	EXPECT_NEAR(v[i++].GetValue().elem, 21.0, 1e-5);
	EXPECT_EQ(v[i++].GetValue().oper, '+');
	EXPECT_EQ(v[i++].GetValue().oper, '(');
	EXPECT_NEAR(v[i++].GetValue().elem, 3.0, 1e-5);
	EXPECT_EQ(v[i++].GetValue().oper, '*');
	EXPECT_NEAR(v[i++].GetValue().elem, 8.0, 1e-5);
	EXPECT_EQ(v[i++].GetValue().oper, ')');
	EXPECT_EQ(v[i++].GetValue().oper, '+');
	EXPECT_NEAR(v[i++].GetValue().elem, 6.0, 1e-5);
	EXPECT_EQ(v[i++].GetValue().oper, '/');
	EXPECT_NEAR(v[i++].GetValue().elem, 2.0, 1e-5);
	EXPECT_EQ(v[i++].GetValue().oper, '-');
	EXPECT_NEAR(v[i].GetValue().elem, 1.0, 1e-5);
}

TEST(Create_lexeme_array, can_create_lexeme_array_with_unary_minus_1)
{
	vector<TLexeme> v = Create_lexeme_array("-11 + 3 * (-2 + 1)");
	int i = 0;
	EXPECT_NEAR(v[i++].GetValue().elem, -11.0, 1e-5);
	EXPECT_EQ(v[i++].GetValue().oper, '+');
	EXPECT_NEAR(v[i++].GetValue().elem, 3.0, 1e-5);
	EXPECT_EQ(v[i++].GetValue().oper, '*');
	EXPECT_EQ(v[i++].GetValue().oper, '(');
	EXPECT_NEAR(v[i++].GetValue().elem, -2.0, 1e-5);
	EXPECT_EQ(v[i++].GetValue().oper, '+');
	EXPECT_NEAR(v[i++].GetValue().elem, 1.0, 1e-5);
	EXPECT_EQ(v[i].GetValue().oper, ')');
}

TEST(Create_lexeme_array, can_create_lexeme_array_with_unary_minus_2)
{
	vector<TLexeme> v = Create_lexeme_array("-(3 * 7)");
	int i = 0;
	EXPECT_EQ(v[i++].GetValue().oper, '-');
	EXPECT_EQ(v[i - 1].GetType(), unary_operation);
	EXPECT_EQ(v[i++].GetValue().oper, '(');
	EXPECT_NEAR(v[i++].GetValue().elem, 3.0, 1e-5);
	EXPECT_EQ(v[i++].GetValue().oper, '*');
	EXPECT_NEAR(v[i++].GetValue().elem, 7.0, 1e-5);
	EXPECT_EQ(v[i].GetValue().oper, ')');
}

TEST(Create_lexeme_array, can_create_lexeme_array_with_unary_minus_3)
{
	vector<TLexeme> v = Create_lexeme_array("2 + 4 - (0.001 * 15) - 6");
	int i = 0;
	EXPECT_NEAR(v[i++].GetValue().elem, 2.0, 1e-5);
	EXPECT_EQ(v[i++].GetValue().oper, '+');
	EXPECT_NEAR(v[i++].GetValue().elem, 4.0, 1e-5);
	EXPECT_EQ(v[i++].GetValue().oper, '-');
	EXPECT_EQ(v[i - 1].GetType(), unary_operation);
	EXPECT_EQ(v[i++].GetValue().oper, '(');
	EXPECT_NEAR(v[i++].GetValue().elem, 0.001, 1e-5);
	EXPECT_EQ(v[i++].GetValue().oper, '*');
	EXPECT_NEAR(v[i++].GetValue().elem, 15.0, 1e-5);
	EXPECT_EQ(v[i++].GetValue().oper, ')');
	EXPECT_EQ(v[i++].GetValue().oper, '-');
	EXPECT_EQ(v[i - 1].GetType(), binary_operation);
	EXPECT_NEAR(v[i++].GetValue().elem, 6.0, 1e-5);
}

TEST(Create_lexeme_array, can_create_lexeme_array_with_double_numbers)
{
	vector<TLexeme> v = Create_lexeme_array("5.05 + 0.15 - 0.00001 * (-0.32 + 6.25)");
	int i = 0;
	EXPECT_NEAR(v[i++].GetValue().elem, 5.05, 1e-5);
	EXPECT_EQ(v[i++].GetValue().oper, '+');
	EXPECT_NEAR(v[i++].GetValue().elem, 0.15, 1e-5);
	EXPECT_EQ(v[i++].GetValue().oper, '-');
	EXPECT_NEAR(v[i++].GetValue().elem, 0.00001, 1e-5);
	EXPECT_EQ(v[i++].GetValue().oper, '*');
	EXPECT_EQ(v[i++].GetValue().oper, '(');
	EXPECT_NEAR(v[i++].GetValue().elem, -0.32, 1e-5);
	EXPECT_EQ(v[i++].GetValue().oper, '+');
	EXPECT_NEAR(v[i++].GetValue().elem, 6.25, 1e-5);
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
	EXPECT_NEAR(35.0, Solver(v), 1e-5);
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
	EXPECT_NEAR(31.0, Solver(v), 1e-5);
}

TEST(Solver, can_solve_expression_with_unary_minus_1)
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
	EXPECT_NEAR(-21.0, Solver(v), 1e-5);
}

TEST(Solver, can_solve_expression_with_unary_minus_2)
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
	EXPECT_NEAR(0.015, Solver(v), 1e-5);
}

TEST(Solver, can_solve_expression_with_unary_minus_3)
{
	// -((2 * 8) - 8)
	// 2 8 * 8 - -
	vector<TLexeme> v;
	TLexeme t(2.0);
	v.push_back(t);
	TLexeme t1(8.0);
	v.push_back(t1);
	TLexeme t2('*');
	v.push_back(t2);
	TLexeme t3(8.0);
	v.push_back(t3);
	TLexeme t4('-');
	v.push_back(t4);
	TLexeme t5('-', unary_operation);
	v.push_back(t5);
	EXPECT_NEAR(-8.0, Solver(v), 1e-5);
}

TEST(Solver, can_solve_expression_with_unary_minus_4)
{
	// 6*(-6*(-6*1))
	// 6 6 - 6 - 1 * * *
	vector<TLexeme> v;
	TLexeme t(6.0);
	v.push_back(t);
	TLexeme t1(6.0);
	v.push_back(t1);
	TLexeme t2('-', unary_operation);
	v.push_back(t2);
	TLexeme t3(6.0);
	v.push_back(t3);
	TLexeme t4('-', unary_operation);
	v.push_back(t4);
	TLexeme t5(1.0);
	v.push_back(t5);
	TLexeme t6('*');
	v.push_back(t6);
	TLexeme t7('*');
	v.push_back(t7);
	TLexeme t8('*');
	v.push_back(t8);
	EXPECT_NEAR(216.0, Solver(v), 1e-5);
}

TEST(Solver, can_solve_expression_with_unary_minus_5)
{
	// 877.01 - 98.254 * (456.0 / 741.7) + 97 / 3.02 * 798.42 + (-(-15))
	// 877.01 98.254 456.0 741.7 / * - 97 3.02 / 798.42 * + 15 - - +
	vector<TLexeme> v;
	TLexeme t(877.01);
	v.push_back(t);
	TLexeme t1(98.254);
	v.push_back(t1);
	TLexeme t2(456.0);
	v.push_back(t2);
	TLexeme t3(741.7);
	v.push_back(t3);
	TLexeme t4('/');
	v.push_back(t4);
	TLexeme t5('*');
	v.push_back(t5);
	TLexeme t6('-');
	v.push_back(t6);
	TLexeme t7(97.0);
	v.push_back(t7);
	TLexeme t8(3.02);
	v.push_back(t8);
	TLexeme t9('/');
	v.push_back(t9);
	TLexeme t10(798.42);
	v.push_back(t10);
	TLexeme t11('*');
	v.push_back(t11);
	TLexeme t12('+');
	v.push_back(t12);
	TLexeme t13(15.0);
	v.push_back(t13);
	TLexeme t14('-', unary_operation);
	v.push_back(t14);
	TLexeme t15('-', unary_operation);
	v.push_back(t15);
	TLexeme t16('+');
	v.push_back(t16);
	EXPECT_NEAR(26476.2189586, Solver(v), 1e-7);
}

TEST(Create_RPN_array, can_create_RPN_array_with_binary_operations)
{
	//1 + (2 - 5) * 4
	vector<TLexeme> v;
	TLexeme t(1.0);
	v.push_back(t);
	TLexeme t1('+');
	v.push_back(t1);
	TLexeme t2('(');
	v.push_back(t2);
	TLexeme t3(2.0);
	v.push_back(t3);
	TLexeme t4('-');
	v.push_back(t4);
	TLexeme t5(5.0);
	v.push_back(t5);
	TLexeme t6(')');
	v.push_back(t6);
	TLexeme t7('*');
	v.push_back(t7);
	TLexeme t8(4.0);
	v.push_back(t8);
	vector<TLexeme> ans = Create_RPN_array(v);
	// 1 2 5 - 4 * +
	int i = 0;
	EXPECT_NEAR(ans[i++].GetValue().elem, 1.0, 1e-5);
	EXPECT_NEAR(ans[i++].GetValue().elem, 2.0, 1e-5);
	EXPECT_NEAR(ans[i++].GetValue().elem, 5.0, 1e-5);
	EXPECT_EQ(ans[i++].GetValue().oper, '-');
	EXPECT_NEAR(ans[i++].GetValue().elem, 4.0, 1e-5);
	EXPECT_EQ(ans[i++].GetValue().oper, '*');
	EXPECT_EQ(ans[i].GetValue().oper, '+');
}

TEST(Create_RPN_array, can_create_RPN_array_with_unary_minus_1)
{
	//2 + 4 - (-(0.001 * 15)) - 6
	vector<TLexeme> v;
	TLexeme t(2.0);
	v.push_back(t);
	TLexeme t1('+');
	v.push_back(t1);
	TLexeme t2(4.0);
	v.push_back(t2);
	TLexeme t3('-');
	v.push_back(t3);
	TLexeme t4('(');
	v.push_back(t4);
	TLexeme t5('-', unary_operation);
	v.push_back(t5);
	TLexeme t6('(');
	v.push_back(t6);
	TLexeme t7(0.001);
	v.push_back(t7);
	TLexeme t8('*');
	v.push_back(t8);
	TLexeme t9(15.0);
	v.push_back(t9);
	TLexeme t10(')');
	v.push_back(t10);
	TLexeme t11(')');
	v.push_back(t11);
	TLexeme t12('-');
	v.push_back(t12);
	TLexeme t13(6.0);
	v.push_back(t13);
	vector<TLexeme> ans = Create_RPN_array(v);
	// 2 4 + 0.001 15 * - - 6 -
	int i = 0;
	EXPECT_NEAR(ans[i++].GetValue().elem, 2.0, 1e-5);
	EXPECT_NEAR(ans[i++].GetValue().elem, 4.0, 1e-5);
	EXPECT_EQ(ans[i++].GetValue().oper, '+');
	EXPECT_NEAR(ans[i++].GetValue().elem, 0.001, 1e-5);
	EXPECT_NEAR(ans[i++].GetValue().elem, 15.0, 1e-5);
	EXPECT_EQ(ans[i++].GetValue().oper, '*');
	EXPECT_EQ(ans[i++].GetValue().oper, '-');
	EXPECT_EQ(ans[i - 1].GetType(), unary_operation);
	EXPECT_EQ(ans[i++].GetValue().oper, '-');
	EXPECT_NEAR(ans[i++].GetValue().elem, 6.0, 1e-5);
	EXPECT_EQ(ans[i].GetValue().oper, '-');
}

TEST(Create_RPN_array, can_create_RPN_array_with_unary_minus_2)
{
	// -((2 * 8) - 8)
	vector<TLexeme> v;
	TLexeme t('-', unary_operation);
	v.push_back(t);
	TLexeme t1('(');
	v.push_back(t1);
	TLexeme t2('(');
	v.push_back(t2);
	TLexeme t3(2.0);
	v.push_back(t3);
	TLexeme t4('*');
	v.push_back(t4);
	TLexeme t5(8.0);
	v.push_back(t5);
	TLexeme t6(')');
	v.push_back(t6);
	TLexeme t7('-');
	v.push_back(t7);
	TLexeme t8(8.0);
	v.push_back(t8);
	TLexeme t9(')');
	v.push_back(t9);
	vector<TLexeme> ans = Create_RPN_array(v);
	// 2 8 * 8 - -
	int i = 0;
	EXPECT_NEAR(ans[i++].GetValue().elem, 2.0, 1e-5);
	EXPECT_NEAR(ans[i++].GetValue().elem, 8.0, 1e-5);
	EXPECT_EQ(ans[i++].GetValue().oper, '*');
	EXPECT_NEAR(ans[i++].GetValue().elem, 8.0, 1e-5);
	EXPECT_EQ(ans[i++].GetValue().oper, '-');
	EXPECT_EQ(ans[i].GetValue().oper, '-');
	EXPECT_EQ(ans[i].GetType(), unary_operation);
}

TEST(Create_RPN_array, can_create_RPN_array_with_unary_minus_3)
{
	// 6*(-6*(-6*1))
	vector<TLexeme> v;
	TLexeme t(6.0);
	v.push_back(t);
	TLexeme t1('*');
	v.push_back(t1);
	TLexeme t2('(');
	v.push_back(t2);
	TLexeme t3('-', unary_operation);
	v.push_back(t3);
	TLexeme t4(6.0);
	v.push_back(t4);
	TLexeme t5('*');
	v.push_back(t5);
	TLexeme t6('(');
	v.push_back(t6);
	TLexeme t7('-', unary_operation);
	v.push_back(t7);
	TLexeme t8(6.0);
	v.push_back(t8);
	TLexeme t9('*');
	v.push_back(t9);
	TLexeme t10(1.0);
	v.push_back(t10);
	TLexeme t11(')');
	v.push_back(t11);
	TLexeme t12(')');
	v.push_back(t12);
	vector<TLexeme> ans = Create_RPN_array(v);
	// 6 6 - 6 - 1 * * *
	int i = 0;
	EXPECT_NEAR(ans[i++].GetValue().elem, 6.0, 1e-5);
	EXPECT_NEAR(ans[i++].GetValue().elem, 6.0, 1e-5);
	EXPECT_EQ(ans[i++].GetValue().oper, '-');
	EXPECT_EQ(ans[i - 1].GetType(), unary_operation);
	EXPECT_NEAR(ans[i++].GetValue().elem, 6.0, 1e-5);
	EXPECT_EQ(ans[i++].GetValue().oper, '-');
	EXPECT_EQ(ans[i - 1].GetType(), unary_operation);
	EXPECT_NEAR(ans[i++].GetValue().elem, 1.0, 1e-5);
	EXPECT_EQ(ans[i++].GetValue().oper, '*');
	EXPECT_EQ(ans[i++].GetValue().oper, '*');
	EXPECT_EQ(ans[i].GetValue().oper, '*');
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
	EXPECT_NEAR(Сonverting_number("15.1257", 0, positive), 15.1257, 1e-5);
}

TEST(Сonverting_number, can_convert_positive_number_2)
{
	EXPECT_NEAR(Сonverting_number("1255125", 0, positive), 1255125, 1e-5);
}

TEST(Сonverting_number, can_convert_negative_number_1)
{
	EXPECT_NEAR(Сonverting_number("0.133", 0, negative), -0.133, 1e-5);
}

TEST(Сonverting_number, can_convert_negative_number_2)
{
	EXPECT_NEAR(Сonverting_number("-999", 0, positive), -999, 1e-5);
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
	set<char> num;
	for (char i = '0'; i <= '9'; i++)
	{
		num.insert(i);
	}
	int i = 2;
	TLexeme ans = Check_number("-(125.6)", i, num, positive);
	EXPECT_EQ(ans.GetType(), number);
	EXPECT_NEAR(ans.GetValue().elem, 125.6, 1e-5);
}

TEST(Check_number, can_create_negative_number_from_string)
{
	set<char> num;
	for (char i = '0'; i <= '9'; i++)
	{
		num.insert(i);
	}
	int i = 7;
	TLexeme ans = Check_number("2+28*(-3+1)", i, num, negative);
	EXPECT_EQ(ans.GetType(), number);
	EXPECT_NEAR(ans.GetValue().elem, -3, 1e-5);
}

TEST(Error_checking, no_exceptions_1)
{
	//2 + 4 - (-(0.001 * 15)) - 6
	vector<TLexeme> v;
	TLexeme t(2.0);
	v.push_back(t);
	TLexeme t1('+');
	v.push_back(t1);
	TLexeme t2(4.0);
	v.push_back(t2);
	TLexeme t3('-');
	v.push_back(t3);
	TLexeme t4('(');
	v.push_back(t4);
	TLexeme t5('-', unary_operation);
	v.push_back(t5);
	TLexeme t6('(');
	v.push_back(t6);
	TLexeme t7(0.001);
	v.push_back(t7);
	TLexeme t8('*');
	v.push_back(t8);
	TLexeme t9(15.0);
	v.push_back(t9);
	TLexeme t10(')');
	v.push_back(t10);
	TLexeme t11(')');
	v.push_back(t11);
	TLexeme t12('-');
	v.push_back(t12);
	TLexeme t13(6.0);
	v.push_back(t13);
	ASSERT_NO_THROW(Error_checking(v));
}

TEST(Error_checking, no_exceptions_2)
{
	// 6*(-6*(-6*1))
	vector<TLexeme> v;
	TLexeme t(6.0);
	v.push_back(t);
	TLexeme t1('*');
	v.push_back(t1);
	TLexeme t2('(');
	v.push_back(t2);
	TLexeme t3('-', unary_operation);
	v.push_back(t3);
	TLexeme t4(6.0);
	v.push_back(t4);
	TLexeme t5('*');
	v.push_back(t5);
	TLexeme t6('(');
	v.push_back(t6);
	TLexeme t7('-', unary_operation);
	v.push_back(t7);
	TLexeme t8(6.0);
	v.push_back(t8);
	TLexeme t9('*');
	v.push_back(t9);
	TLexeme t10(1.0);
	v.push_back(t10);
	TLexeme t11(')');
	v.push_back(t11);
	TLexeme t12(')');
	v.push_back(t12);
	ASSERT_NO_THROW(Error_checking(v));
}

TEST(Error_checking, no_exceptions_3)
{
	// -((2 * 8) - 8)
	vector<TLexeme> v;
	TLexeme t('-', unary_operation);
	v.push_back(t);
	TLexeme t1('(');
	v.push_back(t1);
	TLexeme t2('(');
	v.push_back(t2);
	TLexeme t3(2.0);
	v.push_back(t3);
	TLexeme t4('*');
	v.push_back(t4);
	TLexeme t5(8.0);
	v.push_back(t5);
	TLexeme t6(')');
	v.push_back(t6);
	TLexeme t7('-');
	v.push_back(t7);
	TLexeme t8(8.0);
	v.push_back(t8);
	TLexeme t9(')');
	v.push_back(t9);
	ASSERT_NO_THROW(Error_checking(v));
}

TEST(Error_checking, no_exceprions_when_there_are_a_lot_of_brackets)
{
	string s = "(((1 * 4) -2))";
	s = New_line_without_spaces(s);
	vector<TLexeme> v = Create_lexeme_array(s);
	ASSERT_NO_THROW(Error_checking(v));
}

TEST(Error_checking, throws_an_exception_when_last_lexeme_is_wrong)
{
	// 1 + (2 - 5) * 4 -
	vector<TLexeme> v;
	TLexeme t(1.0);
	v.push_back(t);
	TLexeme t1('+');
	v.push_back(t1);
	TLexeme t2('(');
	v.push_back(t2);
	TLexeme t3(2.0);
	v.push_back(t3);
	TLexeme t4('-');
	v.push_back(t4);
	TLexeme t5(5.0);
	v.push_back(t5);
	TLexeme t6(')');
	v.push_back(t6);
	TLexeme t7('*');
	v.push_back(t7);
	TLexeme t8(4.0);
	v.push_back(t8);
	TLexeme t9('-');
	v.push_back(t9);
	ASSERT_ANY_THROW(Error_checking(v));
}

TEST(Error_checking, throws_an_exception_when_first_lexeme_is_wrong)
{
	// 2 1 + (2 - 5) * 4
	vector<TLexeme> v;
	TLexeme t(2.0);
	v.push_back(t);
	TLexeme t1(1.0);
	v.push_back(t1);
	TLexeme t2('+');
	v.push_back(t2);
	TLexeme t3('(');
	v.push_back(t3);
	TLexeme t4(2.0);
	v.push_back(t4);
	TLexeme t5('-');
	v.push_back(t5);
	TLexeme t6(5.0);
	v.push_back(t6);
	TLexeme t7(')');
	v.push_back(t7);
	TLexeme t8('*');
	v.push_back(t8);
	TLexeme t9(4.0);
	v.push_back(t9);
	ASSERT_ANY_THROW(Error_checking(v));
}

TEST(Error_checking, throws_an_exception_when_any_lexeme_is_wrong)
{
	// 1 + (2 - 5 +) * 4
	vector<TLexeme> v;
	TLexeme t(1.0);
	v.push_back(t);
	TLexeme t1('+');
	v.push_back(t1);
	TLexeme t2('(');
	v.push_back(t2);
	TLexeme t3(2.0);
	v.push_back(t3);
	TLexeme t4('-');
	v.push_back(t4);
	TLexeme t5(5.0);
	v.push_back(t5);
	TLexeme t6('+');
	v.push_back(t6);
	TLexeme t7(')');
	v.push_back(t7);
	TLexeme t8('*');
	v.push_back(t8);
	TLexeme t9(4.0);
	v.push_back(t9);
	ASSERT_ANY_THROW(Error_checking(v));
}

TEST(Error_checking, throws_an_exception_when_there_is_an_extra_opening_bracket)
{
	// 1 + ((2 - 5) * 4
	vector<TLexeme> v;
	TLexeme t(1.0);
	v.push_back(t);
	TLexeme t1('+');
	v.push_back(t1);
	TLexeme t2('(');
	v.push_back(t2);
	TLexeme t3('(');
	v.push_back(t3);
	TLexeme t4(2.0);
	v.push_back(t4);
	TLexeme t5('-');
	v.push_back(t5);
	TLexeme t6(5.0);
	v.push_back(t6);
	TLexeme t7(')');
	v.push_back(t7);
	TLexeme t8('*');
	v.push_back(t8);
	TLexeme t9(4.0);
	v.push_back(t9);
	ASSERT_ANY_THROW(Error_checking(v));
}

TEST(Error_checking, throws_an_exception_when_there_is_an_extra_closing_bracket)
{
	// 1 + (2) - 5) * 4
	vector<TLexeme> v;
	TLexeme t(1.0);
	v.push_back(t);
	TLexeme t1('+');
	v.push_back(t1);
	TLexeme t2('(');
	v.push_back(t2);
	TLexeme t3(2.0);
	v.push_back(t3);
	TLexeme t4(')');
	v.push_back(t4);
	TLexeme t5('-');
	v.push_back(t5);
	TLexeme t6(5.0);
	v.push_back(t6);
	TLexeme t7(')');
	v.push_back(t7);
	TLexeme t8('*');
	v.push_back(t8);
	TLexeme t9(4.0);
	v.push_back(t9);
	ASSERT_ANY_THROW(Error_checking(v));
}

TEST(Error_checking, throws_an_exception_when_the_brackets_are_swapped_1)
{
	// 1 + )2 - 5( * 4
	vector<TLexeme> v;
	TLexeme t(1.0);
	v.push_back(t);
	TLexeme t1('+');
	v.push_back(t1);
	TLexeme t2(')');
	v.push_back(t2);
	TLexeme t3(2.0);
	v.push_back(t3);
	TLexeme t4('-');
	v.push_back(t4);
	TLexeme t5(5.0);
	v.push_back(t5);
	TLexeme t6('(');
	v.push_back(t6);
	TLexeme t7('*');
	v.push_back(t7);
	TLexeme t8(4.0);
	v.push_back(t8);
	ASSERT_ANY_THROW(Error_checking(v));
}

TEST(Error_checking, throws_an_exception_when_the_brackets_are_swapped_2)
{
	string s = "(()1 * 4) -2()";
	s = New_line_without_spaces(s);
	vector<TLexeme> v = Create_lexeme_array(s);
	ASSERT_ANY_THROW(Error_checking(v));
}

//TEST(Error_checking, temp)
//{
//	string s = "3.9.0.4";
//	s = New_line_without_spaces(s);
//	ASSERT_ANY_THROW(Error_checking(Create_lexeme_array(s)));
//}