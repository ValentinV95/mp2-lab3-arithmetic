// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "Arithmetic.h"

TEST(ConvertToArrayLexems, can_convert_string_with_number_to_array_lexems)
{
	string str = "1 2 8 79";
	Lexems exp;

	exp.tokens.push_back(NUMBER);
	exp.values.push(1.0);
	exp.tokens.push_back(NUMBER);
	exp.values.push(2.0);
	exp.tokens.push_back(NUMBER);
	exp.values.push(8.0);
	exp.tokens.push_back(NUMBER);
	exp.values.push(79.0);

	EXPECT_EQ(exp, convertToArrayLexem(str));
}

TEST(ConvertToArrayLexems, can_convert_string_with_double_number_to_array_lexems)
{
	string str = "1.03 .1";
	Lexems exp;

	exp.tokens.push_back(NUMBER);
	exp.values.push(1.03);
	exp.tokens.push_back(NUMBER);
	exp.values.push(0.1);

	EXPECT_EQ(exp, convertToArrayLexem(str));
}

TEST(ConvertToArrayLexems, can_convert_string_with_bracket_to_array_lexems)
{
	string str = "(8)()";
	Lexems exp;

	exp.tokens.push_back(LP);
	exp.tokens.push_back(NUMBER);
	exp.values.push(8.0);
	exp.tokens.push_back(RP);
	exp.tokens.push_back(LP);
	exp.tokens.push_back(RP);

	EXPECT_EQ(exp, convertToArrayLexem(str));
}

TEST(ConvertToArrayLexems, can_convert_srting_with_function_to_array_lexems)
{
	string str = "sin(exp log)cos";
	Lexems exp;

	exp.tokens.push_back(SIN);
	exp.tokens.push_back(LP);
	exp.tokens.push_back(EXP);
	exp.tokens.push_back(LOG);
	exp.tokens.push_back(RP);
	exp.tokens.push_back(COS);

	EXPECT_EQ(exp, convertToArrayLexem(str));
}

TEST(ConvertToArrayLexems, can_convert_string_with_unary_minus_array_lexems)
{
	string str = "-(-";
	Lexems exp;

	exp.tokens.push_back(UNARY_MINUS);
	exp.tokens.push_back(LP);
	exp.tokens.push_back(UNARY_MINUS);

	EXPECT_EQ(exp, convertToArrayLexem(str));
}

TEST(IsCorrect, throw_when_first_character_is_closing_bracket)
{
	string str = ")2*2";
	Lexems expression = convertToArrayLexem(str);

	ASSERT_ANY_THROW(isCorrect(expression));
}

TEST(IsCorrect, throw_when_first_character_is_operation)
{
	string str = "+7*sin(4)";
	Lexems expression = convertToArrayLexem(str);

	ASSERT_ANY_THROW(isCorrect(expression));
}

TEST(IsCorrect, throw_when_number_is_after_number)
{
	string str = "1 1 1 + 1";
	Lexems expression = convertToArrayLexem(str);

	ASSERT_ANY_THROW(isCorrect(expression));
}

TEST(IsCorrect, throw_when_function_is_after_number)
{
	string str = "1+2cos(1)";
	Lexems expression = convertToArrayLexem(str);

	ASSERT_ANY_THROW(isCorrect(expression));
}

TEST(IsCorrect, throw_when_after_function_is_not_opening_bracket)
{
	string str = "sin4";
	Lexems expression = convertToArrayLexem(str);

	ASSERT_ANY_THROW(isCorrect(expression));
}

TEST(IsCorrect, throw_when_unary_minus_is_after_unary_minus)
{
	string str = "(--7)";
	Lexems expression = convertToArrayLexem(str);

	ASSERT_ANY_THROW(isCorrect(expression));
}

TEST(IsCorrect, throw_when_operation_is_after_unary_minus)
{
	string str = "-+8.1";
	Lexems expression = convertToArrayLexem(str);

	ASSERT_ANY_THROW(isCorrect(expression));
}

TEST(IsCorrect, throw_when_closing_bracket_is_after_unary_minus)
{
	string str = "(-)";
	Lexems expression = convertToArrayLexem(str);

	ASSERT_ANY_THROW(isCorrect(expression));
}

TEST(IsCorrect, throw_when_operation_is_after_operation)
{
	string str = "8*/9";
	Lexems expression = convertToArrayLexem(str);

	ASSERT_ANY_THROW(isCorrect(expression));
}

TEST(IsCorrect, throw_when_closing_bracket_is_after_operation)
{
	string str = "(2+2*)";
	Lexems expression = convertToArrayLexem(str);

	ASSERT_ANY_THROW(isCorrect(expression));
}

TEST(IsCorrect, throw_when_number_is_after_closing_bracket)
{
	string str = "(2*2)9";
	Lexems expression = convertToArrayLexem(str);

	ASSERT_ANY_THROW(isCorrect(expression));
}

TEST(IsCorrect, throw_when_function_is_after_closing_bracket)
{
	string str = "(3+5)exp(1)";
	Lexems expression = convertToArrayLexem(str);

	ASSERT_ANY_THROW(isCorrect(expression));
}

TEST(IsCorrect, throw_when_opening_bracket_is_after_closing_bracket)
{
	string str = "(7*8)(2+2)";
	Lexems expression = convertToArrayLexem(str);

	ASSERT_ANY_THROW(isCorrect(expression));
}

TEST(IsCorrect, throw_when_closing_bracket_is_after_opening_bracket)
{
	string str = "2+4*()";
	Lexems expression = convertToArrayLexem(str);

	ASSERT_ANY_THROW(isCorrect(expression));
}

TEST(IsCorrect, throw_when_closing_bracket_more_than_opening_bracket)
{
	string str = "(2*2/(7*8*(7-4))))";
	Lexems expression = convertToArrayLexem(str);

	ASSERT_ANY_THROW(isCorrect(expression));
}

TEST(IsCorrect, throw_when_opening_bracket_more_than_closing_bracket)
{
	string str = "sin(exp(4)";
	Lexems expression = convertToArrayLexem(str);

	ASSERT_ANY_THROW(isCorrect(expression));
}

TEST(IsCorrect, throw_when_last_character_is_unary_minus)
{
	string str = "8*9(-";
	Lexems expression = convertToArrayLexem(str);

	ASSERT_ANY_THROW(isCorrect(expression));
}

TEST(IsCorrect, throw_whem_last_is_character_is_opening_bracket)
{
	string str = "9+6(";
	Lexems expression = convertToArrayLexem(str);

	ASSERT_ANY_THROW(isCorrect(expression));
}

TEST(ComputeResult, can_compute_result_of_expression)
{
	string str = "21 + (3* 8+6 )/2 -1";
	Lexems rpn = convertToRpn(convertToArrayLexem(str));
	double res = computeResult(rpn);
	double exp = 35.0;
	double eps = 0.000001;

	EXPECT_GE(eps, exp - res);
}

TEST(ComputeResult, can_compute_result_of_expression_with_function)
{
	string str = "log(exp(21)) + (8+ sin(37/5) )/2";
	Lexems rpn = convertToRpn(convertToArrayLexem(str));
	double res = computeResult(rpn);
	double exp = 25.4493540;
	double eps = 0.000001;

	EXPECT_GE(eps, exp - res);
}