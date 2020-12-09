// тесты для вычисления арифметических выражений

#include <gtest.h>

#include "arithmetic.h"

TEST(Term, can_create_positive_number)
{
	double a = 1.0;

	ASSERT_NO_THROW(Term(a));
}

TEST(Term, can_create_negative_number)
{
	double a = -1.0;

	ASSERT_NO_THROW(Term(a));
}

TEST(Term, can_create_null_number)
{
	double a = 0.0;

	ASSERT_NO_THROW(Term(a));
}

TEST(Term, compare_type_Lexem_when_create_positive_number)
{
	double a = 1.0;
	Term num(a);

	EXPECT_EQ(num.getTypeLexeme(), 1);
}

TEST(Term, compare_type_Lexem_when_create_negative_number)
{
	double a = -1.0;
	Term num(a);

	EXPECT_EQ(num.getTypeLexeme(), 1);
}

TEST(Term, compare_type_Lexem_when_create_null_number)
{
	double a = 0.0;
	Term num(a);

	EXPECT_EQ(num.getTypeLexeme(), 1);
}

TEST(Term, can_create_operation_plus)
{
	ASSERT_NO_THROW(Term('+'));
}

TEST(Term, can_create_operation_minus)
{
	ASSERT_NO_THROW(Term('-'));
}

TEST(Term, can_create_operation_un_minus)
{
	ASSERT_NO_THROW(Term('~'));
}

TEST(Term, can_create_operation_milti)
{
	ASSERT_NO_THROW(Term('*'));
}

TEST(Term, can_create_operation_div)
{
	ASSERT_NO_THROW(Term('/'));
}

TEST(Term, can_create_operation_open_bracket)
{
	ASSERT_NO_THROW(Term('('));
}

TEST(Term, can_create_operation_close_bracket)
{
	ASSERT_NO_THROW(Term(')'));
}

TEST(Term, compare_type_Lexem_when_create_operation_plus)
{
	Term op('+');

	EXPECT_EQ(op.getTypeLexeme(), 2);
}

TEST(Term, compare_type_Lexem_when_create_operation_minus)
{
	Term op('-');

	EXPECT_EQ(op.getTypeLexeme(), 2);
}

TEST(Term, compare_type_Lexem_when_create_operation_un_minus)
{
	Term op('~');

	EXPECT_EQ(op.getTypeLexeme(), 2);
}

TEST(Term, compare_type_Lexem_when_create_operation_multi)
{
	Term op('*');

	EXPECT_EQ(op.getTypeLexeme(), 2);
}

TEST(Term, compare_type_Lexem_when_create_operation_div)
{
	Term op('/');

	EXPECT_EQ(op.getTypeLexeme(), 2);
}

TEST(Term, compare_type_Lexem_when_create_operation_open_bracket)
{
	Term op('(');

	EXPECT_EQ(op.getTypeLexeme(), 2);
}

TEST(Term, compare_type_Lexem_when_create_close_bracket)
{
	Term op('(');

	EXPECT_EQ(op.getTypeLexeme(), 2);
}

TEST(Term, throw_when_trying_to_create_operation_with_any_not_suitable_symbol)
{
	ASSERT_ANY_THROW(Term('@'));
}

TEST(Term, can_create_alternating)
{
	ASSERT_NO_THROW(Term("xyz"));
}

TEST(Term, compare_type_Lexem_when_create_alternating)
{
	Term alternating("xyz");

	EXPECT_EQ(alternating.getTypeLexeme(), 3);
}

TEST(Term, can_get_positive_number)
{
	Term number(1.0);

	ASSERT_NO_THROW(number.getNumber());
}

TEST(Term, can_get_negative_number)
{
	Term number(-1.0);

	ASSERT_NO_THROW(number.getNumber());
}

TEST(Term, can_get_null_number)
{
	Term number(0.0);

	ASSERT_NO_THROW(number.getNumber());
}

TEST(Term, compare_get_positive_number)
{
	Term number(1.0);

	EXPECT_EQ(number.getNumber(), 1.0);
}

TEST(Term, compare_get_negative_number)
{
	Term number(-1.0);

	EXPECT_EQ(number.getNumber(), -1.0);
}

TEST(Term, compare_get_null_number)
{
	Term number(0.0);

	EXPECT_EQ(number.getNumber(), 0.0);
}

TEST(Term, can_get_operation_plus)
{
	Term operation('+');

	ASSERT_NO_THROW(operation.getOperation());
}

TEST(Term, can_get_operation_minus)
{
	Term operation('-');

	ASSERT_NO_THROW(operation.getOperation());
}

TEST(Term, can_get_operation_multi)
{
	Term operation('*');

	ASSERT_NO_THROW(operation.getOperation());
}

TEST(Term, can_get_operation_div)
{
	Term operation('/');

	ASSERT_NO_THROW(operation.getOperation());
}

TEST(Term, can_get_operation_open_bracket)
{
	Term operation('(');

	ASSERT_NO_THROW(operation.getOperation());
}

TEST(Term, can_get_operation_close_bracket)
{
	Term operation(')');

	ASSERT_NO_THROW(operation.getOperation());
}

TEST(Term, compare_get_operation_plus)
{
	Term operation('+');

	EXPECT_EQ(operation.getOperation(), '+');
}

TEST(Term, compare_get_operation_minus)
{
	Term operation('-');

	EXPECT_EQ(operation.getOperation(), '-');
}

TEST(Term, compare_get_operation_multi)
{
	Term operation('*');

	EXPECT_EQ(operation.getOperation(), '*');
}

TEST(Term, compare_get_operation_div)
{
	Term operation('/');

	EXPECT_EQ(operation.getOperation(), '/');
}

TEST(Term, compare_get_operation_open_bracket)
{
	Term operation('(');

	EXPECT_EQ(operation.getOperation(), '(');
}

TEST(Term, compare_get_operation_close_bracket)
{
	Term operation(')');

	EXPECT_EQ(operation.getOperation(), ')');
}

TEST(Term, can_get_alternating)
{
	Term alternating("xyz");

	ASSERT_NO_THROW(alternating.getAlternating());
}

TEST(Term, compare_get_alternating)
{
	Term alternating("xyz");

	EXPECT_EQ(alternating.getAlternating(), "xyz");
}

TEST(Term, can_get_type_lexem_positive_number)
{
	Term number(1.0);

	ASSERT_NO_THROW(number.getTypeLexeme());
}

TEST(Term, can_get_type_lexem_negative_number)
{
	Term number(-1.0);

	ASSERT_NO_THROW(number.getTypeLexeme());
}

TEST(Term, can_get_type_lexem_null_number)
{
	Term number(0.0);

	ASSERT_NO_THROW(number.getTypeLexeme());
}

TEST(Term, can_get_type_lexem_operation_plus)
{
	Term operation('+');

	ASSERT_NO_THROW(operation.getTypeLexeme());
}

TEST(Term, can_get_type_lexem_operation_minus)
{
	Term operation('-');

	ASSERT_NO_THROW(operation.getTypeLexeme());
}

TEST(Term, can_get_type_lexem_operation_multi)
{
	Term operation('*');

	ASSERT_NO_THROW(operation.getTypeLexeme());
}

TEST(Term, can_get_type_lexem_operation_div)
{
	Term operation('/');

	ASSERT_NO_THROW(operation.getTypeLexeme());
}

TEST(Term, can_get_type_lexem_operation_open_bracket)
{
	Term operation('(');

	ASSERT_NO_THROW(operation.getTypeLexeme());
}

TEST(Term, can_get_type_lexem_operation_close_bracket)
{
	Term operation(')');

	ASSERT_NO_THROW(operation.getTypeLexeme());
}

TEST(Term, can_get_type_lexem_alternating)
{
	Term alternating("xyz");

	ASSERT_NO_THROW(alternating.getTypeLexeme());
}

TEST(Term, can_get_priority_operation_plus)
{
	Term operation('+');

	ASSERT_NO_THROW(operation.getPriorityOperation());
}

TEST(Term, can_get_priority_operation_minus)
{
	Term operation('-');

	ASSERT_NO_THROW(operation.getPriorityOperation());
}

TEST(Term, can_get_priority_operation_un_minus)
{
	Term operation('~');

	ASSERT_NO_THROW(operation.getPriorityOperation());
}

TEST(Term, can_get_priority_operation_multi)
{
	Term operation('*');

	ASSERT_NO_THROW(operation.getPriorityOperation());
}

TEST(Term, can_get_priority_operation_div)
{
	Term operation('/');

	ASSERT_NO_THROW(operation.getPriorityOperation());
}

TEST(Term, can_get_priority_operation_open_bracket)
{
	Term operation('(');

	ASSERT_NO_THROW(operation.getPriorityOperation());
}

TEST(Term, can_get_priority_operation_close_bracket)
{
	Term operation(')');

	ASSERT_NO_THROW(operation.getPriorityOperation());
}

TEST(Term, compare_priority_operation_plus)
{
	Term operation('+');

	EXPECT_EQ(operation.getPriorityOperation(), 1);
}

TEST(Term, compare_priority_operation_minus)
{
	Term operation('-');

	EXPECT_EQ(operation.getPriorityOperation(), 1);
}

TEST(Term, compare_priority_operation_un_minus)
{
	Term operation('~');

	EXPECT_EQ(operation.getPriorityOperation(), 3);
}

TEST(Term, compare_priority_operation_multi)
{
	Term operation('*');

	EXPECT_EQ(operation.getPriorityOperation(), 2);
}

TEST(Term, compare_priority_operation_div)
{
	Term operation('/');

	EXPECT_EQ(operation.getPriorityOperation(), 2);
}

TEST(Term, compare_priority_operation_open_bracket)
{
	Term operation('(');

	EXPECT_EQ(operation.getPriorityOperation(), 0);
}

TEST(Term, compare_priority_operation_close_bracket)
{
	Term operation(')');

	EXPECT_EQ(operation.getPriorityOperation(), 0);
}

TEST(Arithmetic, throw_when_transle_str_to_term_when_str_hadnt_open_bracket_but_has_close_bracket)
{
	Arithmetic a1;

	ASSERT_ANY_THROW(a1.translateStrToTerm("1+3)"));
}

TEST(Arithmetic, throw_when_transle_str_to_term_when_str_had_open_bracket_but_hadnt_close_bracket)
{
	Arithmetic a1;

	ASSERT_ANY_THROW(a1.translateStrToTerm("(1+3"));
}

TEST(Arithmetic, throw_when_transle_str_to_term_when_str_had_close_bracket_and_after_open_bracket)
{
	Arithmetic a1;
	
	ASSERT_ANY_THROW(a1.translateStrToTerm(")(1+3"));
}

TEST(Arithmetic, can_translate__str_only_with_space_to_term)
{
	Arithmetic a1;

	ASSERT_NO_THROW(a1.translateStrToTerm(" "));
}

TEST(Arithmetic, can_translate_str_with_spaces_to_term)
{
	Arithmetic a1;

	ASSERT_NO_THROW(a1.translateStrToTerm("a + b + 5 -8 + 3 / 9"));
}

TEST(Arithmetic, can_translate_str_without_spaces_to_term)
{
	Arithmetic a1;

	ASSERT_NO_THROW(a1.translateStrToTerm("5+3"));
}

TEST(Arithmetic, can_translate_str_with_un_minus_in_0Pos)
{
	Arithmetic a1;

	ASSERT_NO_THROW(a1.translateStrToTerm("-5+3"));
}

TEST(Arithmetic, can_translate_str_with_variety_parametres)
{
	Arithmetic a1;

	ASSERT_NO_THROW(a1.translateStrToTerm("a + b + c"));
}

TEST(Arithmetic, throw_when_str_has_not_allowing_symbols_on_translating_to_term)
{
	Arithmetic a1;

	ASSERT_ANY_THROW(a1.translateStrToTerm("(!+3"));
}

TEST(Arithmetic, can_tanslate_only_with_space_term_to_polish_note)
{
	Arithmetic a1;

	a1.translateStrToTerm(" ");

	ASSERT_NO_THROW(a1.TermToPolishNote());
}

TEST(Arithmetic, can_tanslate_term_without_spaces_to_polish_note)
{
	Arithmetic a1;

	a1.translateStrToTerm("5+3");

	ASSERT_NO_THROW(a1.TermToPolishNote());
}

TEST(Arithmetic, can_tanslate_term_with_spaces_to_polish_note)
{
	Arithmetic a1;

	a1.translateStrToTerm("a + b + 5 -8 + 3 / 9");

	ASSERT_NO_THROW(a1.TermToPolishNote());
}

TEST(Arithmetic, can_tanslate_term_without_spaces_with_un_minus_to_polish_note)
{
	Arithmetic a1;

	a1.translateStrToTerm("-5+3");

	ASSERT_NO_THROW(a1.TermToPolishNote());
}

TEST(Arithmetic, can_tanslate_term_with_spaces_with_un_minus_to_polish_note)
{
	Arithmetic a1;

	a1.translateStrToTerm("-5 + 3");

	ASSERT_NO_THROW(a1.TermToPolishNote());
}

TEST(Arithmetic, can_translate_term_with_variety_parametres_to_polishNote)
{
	Arithmetic a1;
	a1.translateStrToTerm("a + b + c");

	ASSERT_NO_THROW(a1.TermToPolishNote());
}

TEST(Arithmetic, throw_when_calculate_polishNote_with_only_space)
{
	Arithmetic a1;

	a1.translateStrToTerm(" ");
	a1.TermToPolishNote();

	ASSERT_ANY_THROW(a1.calculate());
}

TEST(Arithmetic, can_calculate_polishNote_without_spaces)
{
	Arithmetic a1;

	a1.translateStrToTerm("5+3");
	a1.TermToPolishNote();

	ASSERT_NO_THROW(a1.calculate());
}

TEST(Arithmetic, can_calculate_polishNote_with_spaces)
{
	Arithmetic a1;

	a1.translateStrToTerm("a + b + 5 -8 + 3 / 9");
	a1.TermToPolishNote();

	ASSERT_NO_THROW(a1.calculate());
}

TEST(Arithmetic, can_calculate_polishNote_with_un_minus)
{
	Arithmetic a1;

	a1.translateStrToTerm("-5+3");
	a1.TermToPolishNote();

	ASSERT_NO_THROW(a1.calculate());
}

TEST(Arithmetic, compare_calculate_polishNote_without_spaces)
{
	Arithmetic a1;

	a1.translateStrToTerm("5+3");
	a1.TermToPolishNote();
	a1.calculate();

	EXPECT_EQ(a1.GetResult(), 8);
}

TEST(Arithmetic, compare_calculate_polishNote_with_spaces)
{
	Arithmetic a1;

	a1.translateStrToTerm("5 + 3");
	a1.TermToPolishNote();
	a1.calculate();

	EXPECT_EQ(a1.GetResult(), 8);
}

TEST(Arithmetic, compare_calculate_polishNote_with_un_minus)
{
	Arithmetic a1;

	a1.translateStrToTerm("-5 + 3");
	a1.TermToPolishNote();
	a1.calculate();

	EXPECT_EQ(a1.GetResult(), -2);
}


