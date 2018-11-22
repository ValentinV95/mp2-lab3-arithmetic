// тесты для вычисления арифметических выражений


#include <gtest.h>
#include "arithmetic.h"
#include <gtest.h>
#include <string>
using namespace std;



TEST(Lexeme, can_create_double)
{
	Lexeme l(10.05, 2);
	EXPECT_DOUBLE_EQ(l.Number(), 10.05);
}
TEST(Lexeme, can_create_binary_operation)
{
	Lexeme l('+', 1);
	EXPECT_EQ(l.Op(), '+');
}
TEST(Priority, can_determine_priority_of_operation) {
	EXPECT_EQ(3, prt('*'));
	EXPECT_EQ(3, prt('/'));
	EXPECT_EQ(3, prt(':'));
	EXPECT_EQ(2, prt('+'));
	EXPECT_EQ(2, prt('-'));
}
TEST(Polish_notation, can_create_right_sequence_of_calculations)
{
	string s = "5+(4*7-8)";
	int k = 0;
	Lexeme *c = Polish(s, k);

	int i = 0;
	EXPECT_EQ(c[i++].Number(), 5);
	EXPECT_EQ(c[i++].Number(), 4);
	EXPECT_EQ(c[i++].Number(), 7);
	EXPECT_EQ(c[i++].Op(), '*');
	EXPECT_EQ(c[i++].Number(), 8);
	EXPECT_EQ(c[i++].Op(), '-');
	EXPECT_EQ(c[i++].Op(), '+');

}
TEST(Polish_notation, can_create_right_sequence_of_calculations_with_unary_minus)
{
	string s = "-5+(4*-7-8)";
	int k = 0;
	Lexeme *c = Polish(s, k);

	int i = 0;
	EXPECT_EQ(c[i++].Number(), -5);
	EXPECT_EQ(c[i++].Number(), 4);
	EXPECT_EQ(c[i++].Number(), -7);
	EXPECT_EQ(c[i++].Op(), '*');
	EXPECT_EQ(c[i++].Number(), 8);
	EXPECT_EQ(c[i++].Op(), '-');
	EXPECT_EQ(c[i++].Op(), '+');

}
TEST(Polish_notation, can_create_right_sequence_of_calculations_with_double_numbers)
{
	string s = "5.7+(4*7-8.5)";
	int k = 0;
	Lexeme *c = Polish(s, k);

	int i = 0;
	EXPECT_DOUBLE_EQ(c[i++].Number(), 5.7);
	EXPECT_DOUBLE_EQ(c[i++].Number(), 4);
	EXPECT_DOUBLE_EQ(c[i++].Number(), 7);
	EXPECT_DOUBLE_EQ(c[i++].Op(), '*');
	EXPECT_DOUBLE_EQ(c[i++].Number(), 8.5);
	EXPECT_DOUBLE_EQ(c[i++].Op(), '-');
	EXPECT_DOUBLE_EQ(c[i++].Op(), '+');

}
TEST(Polish_notation, can_not_count_the_wrong_expression)
{
	string s = "5.7+-(4*7-8.5)";
	int k = 0;

	EXPECT_EQ(mistake(s), false);
}
TEST(Polish_notation, can_not_count_the_expression_with_wrong_symbols)
{
	string s = "5.7!+(4*7-8.5)";
	int k = 0;

	EXPECT_EQ(mistake(s), false);
}
TEST(Polish_notation, can_not_count_the_expression_with_wrong_symbols_2)
{
	string s = "5.7A+(4*7-8.5)";
	int k = 0;

	EXPECT_EQ(mistake(s), false);
}
TEST(Polish_notation, can_not_count_the_expression_with_wrong_symbols_3)
{
	string s = "*5.7+(4*7-8.5)";
	int k = 0;

	EXPECT_EQ(mistake(s), false);
}
TEST(Polish_notation, can_not_count_the_expression_with_wrong_symbols_4)
{
	string s = "5.7+(4*7-8.5)-";
	int k = 0;

	EXPECT_EQ(mistake(s), false);
}
TEST(Result, can_solve_expression)
{
	string s = "5+(4*7-8)";
	int k = 0;
	Lexeme *c = Polish(s, k);
	EXPECT_EQ(result(c, k), 25);
}
TEST(Result, can_solve_expression_2)
{
	string s = "-5+(4*-7-8)";
	int k = 0;
	Lexeme *c = Polish(s, k);
	EXPECT_EQ(result(c, k), -41);
}
TEST(Result, can_solve_expression_3)
{
	string s = "5.7+(4*7-8.5)";
	int k = 0;
	Lexeme *c = Polish(s, k);
	EXPECT_DOUBLE_EQ(result(c, k), 25.2);
}
