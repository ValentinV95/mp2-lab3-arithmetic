// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"

TEST( Split, can_create_positive_number)
{
	string a = "1.0";

	ASSERT_NO_THROW(Split(a));
}


TEST(Split, can_create_negative_number)
{
	string a = "-1.0";

	ASSERT_NO_THROW(Split(a));
}

TEST(Split, can_create_null_number)
{
	string a = "0.0";

	ASSERT_NO_THROW(Split(a));
}

TEST(Split, Get_Lexem_when_create_positive_number)
{
	string a = "1.0";
	Split num(a);

	EXPECT_EQ(num.GetLex(), "1.0");
}

TEST(Split, compare_type_Lexem_when_create_negative_number)
{
	string a = "-1.0";
	Split num(a);

	EXPECT_EQ(num.GetLex(), "-1.0");
}

TEST(Split, compare_type_Lexem_when_create_null_number)
{
	string  a = "0.0";
	Split num(a);

	EXPECT_EQ(num.GetLex(), "0.0");
}

TEST(Split, can_create_operation_plus)
{
	ASSERT_NO_THROW(Split("+"));
}

TEST(Split, can_create_operation_minus)
{
	ASSERT_NO_THROW(Split("-"));
}



TEST(Split, can_create_operation_milti)
{
	ASSERT_NO_THROW(Split("*"));
}

TEST(Split, can_create_operation_div)
{
	ASSERT_NO_THROW(Split("/"));
}

TEST(Split, can_create_operation_open_bracket)
{
	ASSERT_NO_THROW(Split("("));
}

TEST(Split, can_create_operation_close_bracket)
{
	ASSERT_NO_THROW(Split(")"));
}

TEST(Split, compare_type_Lexem_when_create_operation_plus)
{
	string a = "+";
	Split num(a);

	EXPECT_EQ(num.GetLex(), "+");
	
}

TEST(Split, compare_type_Lexem_when_create_operation_minus)
{
	string a = "-";
	Split num(a);

	EXPECT_EQ(num.GetLex(), "-");
}



TEST(Split, compare_type_Lexem_when_create_operation_multi)
{
	string a = "*";
	Split num(a);

	EXPECT_EQ(num.GetLex(), "*");
}

TEST(Split, compare_type_Lexem_when_create_operation_div)
{
	string a = "/";
	Split num(a);

	EXPECT_EQ(num.GetLex(), "/");
}

TEST(Split, compare_type_Lexem_when_create_operation_open_bracket)
{
	string a = "(";
	Split num(a);

	EXPECT_EQ(num.GetLex(), "(");
}

TEST(Split, compare_type_Lexem_when_create_close_bracket)
{
	string a = ")";
	Split num(a);

	EXPECT_EQ(num.GetLex(), ")");
}



TEST(Split, can_create_alternating)
{
	ASSERT_NO_THROW(Split("xyz"));
}

TEST(Term, compare_type_Lexem_when_create_alternating)
{
	Split alternating("xyz");

	EXPECT_EQ(alternating.GetLex(), "xyz");
}



TEST(arithmetic, throw_when_transle_str_to_term_when_str_hadnt_open_bracket_but_has_close_bracket)
{
	arithmetic a("1+3)");

	ASSERT_ANY_THROW(a.Process());
}

TEST(arithmetic, throw_when_transle_str_to_term_when_str_had_open_bracket_but_hadnt_close_bracket)
{
	arithmetic a("(1+3");

	ASSERT_ANY_THROW(a.Process());
}

TEST(arithmetic, throw_when_transle_str_to_term_when_str_had_close_bracket_and_after_open_bracket)
{
	arithmetic a(")(1+3");

	ASSERT_ANY_THROW(a.Process());
}





TEST(arithmetic, can_translate_str_without_spaces_to_term)
{
	arithmetic a("5+3");

	ASSERT_NO_THROW(a.Process());
}





TEST(arithmetic, throw_when_str_has_not_allowing_symbols_on_translating_to_term)
{
	arithmetic a("(!+3");

	ASSERT_ANY_THROW(a.Process());
}





TEST(arithmetic, throw_when_calculate_polishNote_with_only_space)
{
	arithmetic a(" ");

	a.Process();
	

	ASSERT_ANY_THROW(a.calculat());
}

TEST(arithmetic, can_calculate_polishNote_without_spaces)
{
	arithmetic a("5+3");

	a.Process();
	

	ASSERT_NO_THROW(a.calculat());
}



TEST(arithmetic, compare_calculate_polishNote_without_spaces)
{
	arithmetic a("5+3");
	

	a.Process();
	
	a.calculat();

	EXPECT_EQ(a.GetResult(), 8);
}






