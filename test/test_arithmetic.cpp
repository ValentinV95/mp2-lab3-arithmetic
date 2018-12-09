// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"
#include <string>
using namespace std;
TEST(Lexem, can_create_double_lexem)
{
	Lexem a(1.1, 2);
	EXPECT_DOUBLE_EQ(a.number(), 1.1);
}

TEST(priority, can_determine_operation_priority) {
	EXPECT_EQ(2, priority('+'));
	EXPECT_EQ(2, priority('-'));
	EXPECT_EQ(3, priority('*'));
	EXPECT_EQ(3, priority('/'));
}

TEST(Lexem, can_create_binary_operation)
{
	Lexem a('+', 1);
	EXPECT_EQ(a.operation(), '+');
	Lexem b('*', 1);
	EXPECT_EQ(b.operation(), '*');
}

TEST(result, throw_if_the_first_symbol_is_closing_bracket)
{
	string stroka = ")1+1";
	EXPECT_EQ(errors(stroka), false);
}


TEST(result, throw_if_there_are_two_operations)
{
	string stroka = "10*/1";
	EXPECT_EQ(errors(stroka), false);
}

TEST(result, throw_if_there_are_wrong_symbols)
{
	string stroka1 = "10/2&1";
	EXPECT_EQ(errors(stroka1), false);
	string stroka2 = "10/s+1";
	EXPECT_EQ(errors(stroka2), false);

}

TEST(result, throw_if_the_expression_ends_with_a_wrong_symbol)
{
	string stroka = "10-2+1-";
	EXPECT_EQ(errors(stroka), false);
}

TEST(result, can_sum)
{
	string stroka = "1+1";
	int k = 0;
	Lexem *a = PolishRecord(stroka, k);
	EXPECT_EQ(result(a, k), 2);
}

TEST(result, can_sum_and_sub)
{
	string stroka = "1+1-1";
	int k = 0;
	Lexem *a = PolishRecord(stroka, k);
	EXPECT_EQ(result(a, k), 1);
}

TEST(result, can_use_brackets)
{
	string stroka = "3.5*(1+1)";
	int k = 0;
	Lexem *a = PolishRecord(stroka, k);
	EXPECT_EQ(result(a, k), 7);
}

TEST(result, can_use_many_brackets)
{
	string stroka = "(((1+1)*1+1)*1+1)+1+1";
	int k = 0;
	Lexem *a = PolishRecord(stroka, k);
	EXPECT_EQ(result(a, k), 6);
}

TEST(result, can_use_unary_minus_with_or_without_brackets)
{
	string stroka1 = "10/(-2)";
	string stroka2 = "10/-2";
	int k = 0;
	Lexem *a = PolishRecord(stroka1, k);
	EXPECT_DOUBLE_EQ(result(a, k), -5);
	Lexem *b = PolishRecord(stroka2, k);
	EXPECT_DOUBLE_EQ(result(b, k), -5);
}

TEST(result, can_use_many_unary_minuses)
{
	string stroka = "1+-------1";
	int k = 0;
	Lexem *a = PolishRecord(stroka, k);
	EXPECT_EQ(result(a, k), 0);
}