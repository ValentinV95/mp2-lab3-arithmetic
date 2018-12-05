// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"


TEST(Lexem, can_get_value)
{
	Lexem l("12.45", Token::NUM);
	EXPECT_EQ(l.value(), "12.45");
	l = Lexem("x", Token::VAR);
	EXPECT_EQ(l.value(), "x");
	l = Lexem("-", Token::OP);
	EXPECT_EQ(l.value(), "-");
	l = Lexem("*", Token::OP);
	EXPECT_EQ(l.value(), "*");

}

TEST(Lexem, can_get_token)
{
	Lexem l("12.45", Token::NUM);
	EXPECT_EQ(l.token(), Token::NUM);
	l = Lexem("x", Token::VAR);
	EXPECT_EQ(l.token(), Token::VAR);
	l = Lexem("-", Token::OP);
	EXPECT_EQ(l.token(), Token::OP);
	l = Lexem("*", Token::OP);
	EXPECT_EQ(l.token(), Token::OP);
}

TEST(Expression, can_check_priority)
{
	EXPECT_EQ(Expression::priority('4'), 0);
	EXPECT_EQ(Expression::priority('+'), 2);
	EXPECT_EQ(Expression::priority(')'), 0);
	EXPECT_EQ(Expression::priority('('), 1);
	EXPECT_EQ(Expression::priority('*'), 3);
	EXPECT_EQ(Expression::priority('/'), 3);
	EXPECT_EQ(Expression::priority('^'), 0);
	EXPECT_EQ(Expression::priority('-'), 2);
	EXPECT_EQ(Expression::priority('b'), 0);
}

TEST(Expression, can_check_expressions)
{
	Expression e;
	EXPECT_EQ(e.parse("a^9"), false);
	EXPECT_EQ(e.parse("0.003"), true);
	EXPECT_EQ(e.parse("a.25"), false);
	EXPECT_EQ(e.parse("a + 9"), true);
	EXPECT_EQ(e.parse("=(a+b)"), false);
	EXPECT_EQ(e.parse("-(a+b)"), true);
	EXPECT_EQ(e.parse("0acj"), false);
	EXPECT_EQ(e.parse("ac056j"), true);
	EXPECT_EQ(e.parse("a*b+-(c+d)"), true);
}

TEST(Expression, can_check_brackets)
{
	Expression e;
	EXPECT_EQ(e.parse("(0)"), true);
	EXPECT_EQ(e.parse(")"), false);
	EXPECT_EQ(e.parse("(a + 0.56) - 2.4 + )"), false);
	EXPECT_EQ(e.parse("(a + 0.56) - 2.4 * (3 + x)"), true);
	EXPECT_EQ(e.parse("-((((-1+1)*1-1)*1+-1)*1+1)/2.5"), true);
}

TEST(Expression, can_check_invalid_symbols)
{
	Expression e;
	EXPECT_EQ(e.parse("a"), true);
	EXPECT_EQ(e.parse("a  %  b"), false);
	EXPECT_EQ(e.parse("a + b - 5.56"), true);
	EXPECT_EQ(e.parse("a + b @ 5.56"), false);
	EXPECT_EQ(e.parse(""), true);
}

TEST(Expression, can_check_expected_operands)
{
	Expression e;
	EXPECT_EQ(e.parse("5 b"), false);
	EXPECT_EQ(e.parse("5 7.5 a"), false);
	EXPECT_EQ(e.parse("(a 6.7)"), false);
	EXPECT_EQ(e.parse("(a + 6.7)"), true);
}

TEST(Expression, can_get_polish_inverse_notation)
{
	Expression e;
	e.parse("x");
	EXPECT_EQ(e.toRPN(), "x");
	e.parse("2+3");
	EXPECT_EQ(e.toRPN(), "2 3 +");
	e.parse("8--3.45");
	EXPECT_EQ(e.toRPN(), "8 -3.45 -");
	e.parse("(1 + 2.5) * (3 + 4)");
	EXPECT_EQ(e.toRPN(), "1 2.5 + 3 4 + *");
	e.parse("-((((-1+1)*1-1)*1+-1)*1+1)/2.5");
	EXPECT_EQ(e.toRPN(), "-1 -1 1 + 1 * 1 - 1 * -1 + 1 * 1 + * 2.5 /");
}

TEST(Expression, can_get_eval)
{
	Expression e;
	e.parse(".35");
	EXPECT_EQ(e.eval(e.toRPN()), 0.35);
	e.parse("10000");
	EXPECT_EQ(e.eval(e.toRPN()), 10000);
	e.parse("2+3");
	EXPECT_EQ(e.eval(e.toRPN()), 5);
	e.parse("8--3.45");
	EXPECT_EQ(e.eval(e.toRPN()), 11.45);
	e.parse("(1 + 2.5) * (3 + 4)");
	EXPECT_EQ(e.eval(e.toRPN()), 24.5);
	e.parse("-((((-1+1)*1-1)*1+-1)*1+1)/2.5");
	EXPECT_EQ(e.eval(e.toRPN()), 0.4);
	e.parse("8/-1");
	EXPECT_EQ(e.eval(e.toRPN()), -8);
	e.parse("1/-(4+6)");
	EXPECT_EQ(e.eval(e.toRPN()), -0.1);
	e.parse("2*-(48-56)");
	EXPECT_EQ(e.eval(e.toRPN()), 16);
}