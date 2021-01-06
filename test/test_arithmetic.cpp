// тесты для вычисления арифметических выражений

#include "gtest.h"
#include "arithmetic.h"

TEST(Arithmetic, can_create_a_calculator)
{
    ASSERT_NO_THROW(Arithmetic calc);
}
TEST(Arithmetic, can_pass_a_string_to_the_calculator)
{
    Arithmetic calc;
    std::string str = "1+5*2";
    ASSERT_NO_THROW(calc.SetFormula(str));
}
TEST(Arithmetic, can_pass_the_correct_string_with_parentheses_to_the_calculator)
{
    Arithmetic calc;
    std::string str = "(1+5)*2";
    ASSERT_NO_THROW(calc.SetFormula(str));
}

TEST(Arithmetic, passing_a_formula_with_incorrectly_placed_parentheses_to_the_calculator_will_cause_an_exception)
{
    Arithmetic calc;
    std::string str = "(1+5*2";
    ASSERT_ANY_THROW(calc.SetFormula(str));
}
TEST(Arithmetic, can_calculate_the_result_of_an_arithmetic_expression)
{
    Arithmetic calc;
    calc.SetFormula("1+5*2");
    calc.ToPostfix();
    ASSERT_NO_THROW(calc.res());
}
TEST(Arithmetic, evaluating_an_expression_with_incorrect_operations_will_throw_an_exception)
{
    Arithmetic calc;
    calc.SetFormula("1+5*");
    calc.ToPostfix();
    ASSERT_ANY_THROW(calc.res());
}


TEST(Arithmetic, the_calculator_adds_integers_correctly)
{
    Arithmetic calc;
    calc.SetFormula("1+5");
    calc.ToPostfix();
    double a = 1.0 + 5.0;
    EXPECT_EQ(a, calc.res());
}


TEST(Arithmetic, the_calculator_subtracts_integers_correctly)
{
    Arithmetic calc;
    calc.SetFormula("2-3");
    calc.ToPostfix();
    double a = 2.0 - 3.0;
    EXPECT_EQ(a, calc.res());
}


TEST(Arithmetic, the_calculator_multiplies_integers_correctly)
{
    Arithmetic calc;
    calc.SetFormula("3*7");
    calc.ToPostfix();
    double a = 3.0 * 7.0;
    EXPECT_EQ(a, calc.res());
}


TEST(Arithmetic, the_calculator_divides_integers_correctly)
{
    Arithmetic calc;
    calc.SetFormula("5/2");
    calc.ToPostfix();
    double a = 5.0 / 2.0;
    EXPECT_EQ(a, calc.res());
}


TEST(Arithmetic, the_calculator_raise_to_a_degree_integers_correctly)
{
    Arithmetic calc;
    calc.SetFormula("3^8");
    calc.ToPostfix();
    double a = pow(3.0, 8.0);
    EXPECT_EQ(a, calc.res());
}

TEST(Arithmetic, the_calculator_correctly_counts_complex_arithmetic_expressions)
{
    Arithmetic calc;
    calc.SetFormula("3*7/(2+5)-(10*4-39)");
    calc.ToPostfix();
    EXPECT_EQ(2, calc.res());
}