// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"

TEST(Interpreter, can_convert_string_to_lexeme_array_1)
{
	Lexeme a(VARIABLE, "xx");
	Lexeme b(OPERATION, "+");
	Lexeme c(NUMBER, 2.2);
	string s("xx+2.2");

	vector<Lexeme> x = {a,b,c};
	vector<Lexeme> t = Convert_to_lexeme_array(s);

		EXPECT_EQ(x,t);
}

TEST(Interpreter, can_convert_string_to_lexeme_array_2)
{
	Lexeme a(BRACKET, "(");
	Lexeme b(OPERATION, "unar-");
	Lexeme c(OPERATION, "unar-");
	Lexeme d(NUMBER, 2.1);
	Lexeme e(BRACKET, ")");
	Lexeme f(OPERATION, "-");
	Lexeme g(NUMBER, 2.2);
	string s("(--2.1)-2.2");

	vector<Lexeme> x = { a,b,c,d,e,f,g };
	vector<Lexeme> t = Convert_to_lexeme_array(s);

	EXPECT_EQ(x, t);
}

TEST(Interpreter, can_convert_string_to_lexeme_array_3)
{
	Lexeme a(OPERATION, "unar-");
	Lexeme b(NUMBER, 21.0);
	Lexeme c(OPERATION, "-");
	Lexeme d(OPERATION, "unar-");
	Lexeme e(BRACKET, "(");
	Lexeme f(NUMBER, 3.0);
	Lexeme g(OPERATION, "*");
	Lexeme h(OPERATION, "unar-");
	Lexeme i(NUMBER, 8.0);
	Lexeme j(BRACKET, ")");
	string s("-21--(3*-8)");

	vector<Lexeme> x = { a,b,c,d,e,f,g,h,i,j };
	vector<Lexeme> t = Convert_to_lexeme_array(s);

	EXPECT_EQ(x, t);
}

TEST(Interpreter, throw_when_expression_isnt_correct_1)
{
	string s("a::+2");

	ASSERT_ANY_THROW(Convert_to_lexeme_array(s));
}

TEST(Interpreter, throw_when_expression_isnt_correct_2)
{
	string s("a+*2");
	vector<Lexeme> v;

	v = Convert_to_lexeme_array(s);

	ASSERT_ANY_THROW(Checking_correctness(v));
}

TEST(Interpreter, throw_when_expression_isnt_correct_3)
{
	string s("a2*1.1");
	vector<Lexeme> v;

	v = Convert_to_lexeme_array(s);

	ASSERT_ANY_THROW(Checking_correctness(v));
}

TEST(Interpreter, throw_when_expression_isnt_correct_4)
{
	string s("(a+2)*(3");
	vector<Lexeme> v;

	v = Convert_to_lexeme_array(s);

	ASSERT_ANY_THROW(Checking_correctness(v));
}

TEST(Interpreter, throw_when_expression_isnt_correct_5)
{
	string s(")2+3");
	vector<Lexeme> v;

	v = Convert_to_lexeme_array(s);

	ASSERT_ANY_THROW(Checking_correctness(v));
}

TEST(Interpreter, throw_when_expression_isnt_correct_6)
{
	string s("2+3*");
	vector<Lexeme> v;

	v = Convert_to_lexeme_array(s);

	ASSERT_ANY_THROW(Checking_correctness(v));
}

TEST(Interpreter, throw_when_expression_isnt_correct_7)
{
	string s("2)+(3*");
	vector<Lexeme> v;

	v = Convert_to_lexeme_array(s);

	ASSERT_ANY_THROW(Checking_correctness(v));
}

TEST(Interpreter, throw_when_expression_isnt_correct_8)
{
	string s("24.3.5*2");

	ASSERT_ANY_THROW(Convert_to_lexeme_array(s));
}

TEST(Interpreter, Checking_correctness_returns_true_if_expression_is_correct)
{
	string s("-21--(3*-8)");
	vector<Lexeme> v;

	v = Convert_to_lexeme_array(s);

	ASSERT_NO_THROW(Checking_correctness(v));
}


TEST(Interpreter, can_convert_expression_to_postfix_notation_1)
{
	Lexeme a(VARIABLE, "xx");
	Lexeme b(NUMBER, 2.2);
	Lexeme c(OPERATION, "+");
	
	string s("xx+2.2");

	vector<Lexeme> x = { a,b,c };
	vector<Lexeme> t = Convert_to_lexeme_array(s);
	t = Convert_to_postfix_notation(t);

	EXPECT_EQ(x, t);
}


TEST(Interpreter, can_convert_expression_to_postfix_notation_2)
{
	Lexeme a(NUMBER, 2.1);
	Lexeme b(OPERATION, "unar-");
	Lexeme c(OPERATION, "unar-");
	Lexeme d(NUMBER, 2.2);
	Lexeme e(OPERATION, "-");
	
	string s("(--2.1)-2.2");

	vector<Lexeme> x = { a,b,c,d,e };
	vector<Lexeme> t = Convert_to_lexeme_array(s);
	t = Convert_to_postfix_notation(t);

	EXPECT_EQ(x, t);
}

TEST(Interpreter, can_convert_expression_to_postfix_notation_3)
{
	Lexeme a(NUMBER, 21.0);
	Lexeme b(OPERATION, "unar-");
	Lexeme c(NUMBER, 3.0);
	Lexeme d(NUMBER, 8.0);
	Lexeme e(OPERATION, "unar-");
	Lexeme f(OPERATION, "*");
	Lexeme g(OPERATION, "unar-");
	Lexeme h(OPERATION, "-");

	string s("-21--(3*-8)");

	vector<Lexeme> x = { a,b,c,d,e,f,g,h };
	vector<Lexeme> t = Convert_to_lexeme_array(s);
	t = Convert_to_postfix_notation(t);

	EXPECT_EQ(x, t);
}

TEST(Interpreter, throw_when_divide_by_zero)
{
	string s("21/0");
	vector<Lexeme> v;

	v = Convert_to_lexeme_array(s);
	v = Convert_to_postfix_notation(v);

	ASSERT_ANY_THROW(Expression_result(v));
}

TEST(Interpreter, calculating_the_correct_expression_1)
{
	string s("-21--(3*-8)");
	vector<Lexeme> v;
	double exp = -45;

	v = Convert_to_lexeme_array(s);
	v = Convert_to_postfix_notation(v);

	EXPECT_EQ(exp, Expression_result(v));
}

TEST(Interpreter, calculating_the_correct_expression_2)
{
	string s("(6/3)*(1+---3.3)");
	vector<Lexeme> v;
	double exp = -4.6;

	v = Convert_to_lexeme_array(s);
	v = Convert_to_postfix_notation(v);

	EXPECT_EQ(exp, Expression_result(v));
}

TEST(Interpreter, calculating_the_correct_expression_3)
{
	string s("-40+60+VARIABLE");
	vector<Lexeme> v;
	double exp = 0.0;

	v = Convert_to_lexeme_array(s);
	v[5].SetValue(-20.0) ;
	v = Convert_to_postfix_notation(v);

	EXPECT_EQ(exp, Expression_result(v));
}
