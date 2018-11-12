#include <gtest.h>
#include "arithmetic.h"

TEST(Lexem, can_create_operand)
{
    double d = 1.0;
    ASSERT_NO_THROW(Lexem t(d));
}
TEST(Lexem, can_create_operation)
{
    string d = "+";
    ASSERT_NO_THROW(Lexem t(d));
}
TEST(Lexem, can_create_unary_operation)
{
    string d = "sqrt";
    ASSERT_NO_THROW(Lexem t(d));
}
TEST(Lexem, can_get_num)
{
    double d = 1.0;
    Lexem t(d);
    EXPECT_EQ(1.0,t.Get_Num());
}
TEST(Lexem, can_get_op)
{
    string d = "/";
    Lexem t(d);
    EXPECT_EQ("/",t.Get_Op());
}
TEST(Lexem, can_get_un_op)
{
    string d = "ln";
    Lexem t(d);
    EXPECT_EQ("ln",t.Get_Un_Op());
}
TEST(Lexem, Is_Num_return_true_when_create_operand)
{
    double d = 1.0;
    Lexem t(d);
    EXPECT_EQ(true,t.Is_Num());
}
TEST(Lexem, Is_Num_return_false_when_create_operation)
{
    string d = "/";
    Lexem t(d);
    EXPECT_EQ(false,t.Is_Num());
}

/*Input validation*/

//find an error like "... after operand"
TEST(Lexem, find_error_when_operand_after_operand)
{
    string s = "(2*8)/2-(9/3)+2.03.4";
    vector<Lexem> t;
	ASSERT_ANY_THROW(from_string_to_vector(s, t));
}
TEST(Lexem, find_error_when_opening_bkt_after_operand)
{
    string s = "ln(1)+3(cos(0))";
    vector<Lexem> t;
	ASSERT_ANY_THROW(from_string_to_vector(s, t));
}
TEST(Lexem, find_error_when_unary_operation_after_operand)
{
    string s = "ln(1)+3cos(0)";
    vector<Lexem> t;
	ASSERT_ANY_THROW(from_string_to_vector(s, t));
}

//find an error like "... after operation"
TEST(Lexem, find_error_when_operation_after_operation)
{
    string s = "ln(1)+(3*sqrt9)+*3";
    vector<Lexem> t;
	ASSERT_ANY_THROW(from_string_to_vector(s, t));
}
TEST(Lexem, find_error_when_closing_bkt_after_operation)
{
    string s = "ln(1)+(3*sqrt9)+(3*0+)";
    vector<Lexem> t;
	ASSERT_ANY_THROW(from_string_to_vector(s, t));
}

//find an error like "... after unary operation"
TEST(Lexem, find_error_when_operation_after_unary_operation)
{
    string s = "ln(1)+3*cos+3";
    vector<Lexem> t;
	ASSERT_ANY_THROW(from_string_to_vector(s, t));
}
TEST(Lexem, find_error_when_closing_bkt_after_unary_operation)
{
    string s = "ln(1)+(sqrt)+3";
    vector<Lexem> t;
	ASSERT_ANY_THROW(from_string_to_vector(s, t));
}

//find an error like "... after opening bracket"
TEST(Lexem, find_error_when_operation_after_opening_bkt)
{
    string s = "(2*8)/2-(*9/3)";
    vector<Lexem> t;
	ASSERT_ANY_THROW(from_string_to_vector(s, t));
}
TEST(Lexem, find_error_when_closing_bkt_after_opening_bkt)
{
    string s = "(2*8)/2-(9/3)+()";
    vector<Lexem> t;
	ASSERT_ANY_THROW(from_string_to_vector(s, t));
}

//find an error like "... after closing bracket"
TEST(Lexem, find_error_when_operand_after_closing_bkt)
{
    string s = "(2*8)/2-(9/3)42";
    vector<Lexem> t;
	ASSERT_ANY_THROW(from_string_to_vector(s, t));
}
TEST(Lexem, find_error_when_opening_bkt_after_closing_bkt)
{
    string s = "(2*8)/2-(9/3)+(-1)(-1)";
    vector<Lexem> t;
	ASSERT_ANY_THROW(from_string_to_vector(s, t));
}
TEST(Lexem, find_error_when_unary_operation_bkt_after_closing_bkt)
{
    string s = "(2*8)/2-(9/3)+(-1)exp2";
    vector<Lexem> t;
	ASSERT_ANY_THROW(from_string_to_vector(s, t));
}

//Wrong_bracket_sequence
TEST(Lexem, find_error_when_wrong_bracket_sequence_1)
{
    string s = "(2*8)/2-(9/3)+(-1)*exp2)";
    vector<Lexem> t;
	ASSERT_ANY_THROW(from_string_to_vector(s, t));
}
TEST(Lexem, find_error_when_wrong_bracket_sequence_2)
{
    string s = ")*(2*8)/2-(9/3)+(-1)*exp2";
    vector<Lexem> t;
	ASSERT_ANY_THROW(from_string_to_vector(s, t));
}
TEST(Lexem, find_error_when_wrong_bracket_sequence_3)
{
    string s = "(((3*2))";
    vector<Lexem> t;
	ASSERT_ANY_THROW(from_string_to_vector(s, t));
}

TEST(Lexem, find_error_when_enter_unacceptable_substring_1)
{
    string s = "(2*8)+Ln3+(-1)*exp2";
    vector<Lexem> t;
    ASSERT_ANY_THROW(from_string_to_vector(s, t));
}
TEST(Lexem, find_error_when_enter_unacceptable_substring_2)
{
    string s = "(2*8)/2-(9/3)+log3+(-1)*exp2";
    vector<Lexem> t;
    ASSERT_ANY_THROW(from_string_to_vector(s, t));
}

TEST(Lexem, find_error_when_enter_unacceptable_symbol_1)
{
    string s = "(2*8)/2-(9/3)+3^2+(-1)*exp2";
    vector<Lexem> t;
    ASSERT_ANY_THROW(from_string_to_vector(s, t));
}
TEST(Lexem, find_error_when_enter_unacceptable_symbol_2)
{
    string s = "(2*8)/2-(9/3)+3:2+(-1)*exp2";
    vector<Lexem> t;
    ASSERT_ANY_THROW(from_string_to_vector(s, t));
}

TEST(Lexem, find_error_when_incorrect_first_symbol_1)
{
    string s = "*(2*8)/2-(9/3)+3.0/2.0+(-1)*exp2";
    vector<Lexem> t;
    ASSERT_ANY_THROW(from_string_to_vector(s, t));
}
TEST(Lexem, find_error_when_incorrect_first_symbol_2)
{
    string s = ")(2*8)/2-(9/3)+3.0/2.0+(-1)*exp2-sin3.14";
    vector<Lexem> t;
    ASSERT_ANY_THROW(from_string_to_vector(s, t));
}

TEST(Lexem, find_error_when_incorrect_last_symbol_1)
{
    string s = "(2*8)/2-(9/3)+3.0/2.0+(-1)*exp2-";
    vector<Lexem> t;
    ASSERT_ANY_THROW(from_string_to_vector(s, t));
}
TEST(Lexem, find_error_when_incorrect_last_symbol_2)
{
    string s = "(2*8)/2-(9/3)+3.0/2.0+(-1)*exp2-sin";
    vector<Lexem> t;
    ASSERT_ANY_THROW(from_string_to_vector(s, t));
}
TEST(Lexem, find_error_when_incorrect_last_symbol_3)
{
    string s = "8*(5+5)-";
    vector<Lexem> t;
    ASSERT_ANY_THROW(from_string_to_vector(s, t));
}

/*Calculation validation */

TEST(Lexem, calculation_validation_1)
{
    string s = "(2.0*8.0)";
    vector<Lexem> t;
    priority_creation();
    from_string_to_vector(s,t);
    t = RPN(t);
    EXPECT_NEAR(2.0*8.0,calc(t),eps);
}
TEST(Lexem, calculation_validation_2)
{
    string s = "((2*8)-8.0)";
    vector<Lexem> t;
    priority_creation();
    from_string_to_vector(s,t);
    t = RPN(t);
    EXPECT_NEAR(8.0,calc(t),eps);
}
TEST(Lexem, calculation_validation_3)
{
    string s = "-((2*8)-8)";
    vector<Lexem> t;
    priority_creation();
    from_string_to_vector(s,t);
    t = RPN(t);
    EXPECT_NEAR(-8.0,calc(t),eps);
}
TEST(Lexem, calculation_validation_4)
{
    string s = "ln(1.0)+3*(cos(0))";
    vector<Lexem> t;
    priority_creation();
    from_string_to_vector(s,t);
    t = RPN(t);
    EXPECT_NEAR(3,calc(t),eps);
}
TEST(Lexem, calculation_validation_5)
{
    string s = "exp(-cos(3.14159265))";
    vector<Lexem> t;
    priority_creation();
    from_string_to_vector(s,t);
    t = RPN(t);
    EXPECT_NEAR(exp(1),calc(t),eps);
}
TEST(Lexem, calculation_validation_6)
{
    string s = "6*(-6*(-6*1))";
    vector<Lexem> t;
    priority_creation();
    from_string_to_vector(s,t);
    t = RPN(t);
    EXPECT_NEAR(216,calc(t),eps);
}
TEST(Lexem, calculation_validation_7)
{
    string s = "sqrt(-6*(-6*(-6*(-6))))";
    vector<Lexem> t;
    priority_creation();
    from_string_to_vector(s,t);
    t = RPN(t);
    EXPECT_NEAR(36,calc(t),eps);
}
TEST(Lexem, calculation_validation_8)
{
    string s = "-5.00001";
    vector<Lexem> t;
    priority_creation();
    from_string_to_vector(s,t);
    t = RPN(t);
    EXPECT_NEAR(-5.00001,calc(t),eps);
}
TEST(Lexem, calculation_validation_9)
{
    string s = "4536.845-7896.124*(4586.6/741.7)+97/3.02*42583.42+(-(-73))";
    double ans = 4536.845 - 7896.124 * (4586.6 / 741.7) + 97 / 3.02 * 42583.42 + (-(-73));
    vector<Lexem> t;
    priority_creation();
    from_string_to_vector(s,t);
    t = RPN(t);
    EXPECT_NEAR(ans,calc(t),eps);
}
TEST(Lexem, calculation_validation_10)
{
    string s = "ln(exp(sqrt(4*(cos(-exp(sqrt(42)))*cos(-exp(sqrt(42)))+sin(-exp(sqrt(42)))*sin(-exp(sqrt(42)))))))+2.0";
    vector<Lexem> t;
    priority_creation();
    from_string_to_vector(s,t);
    t = RPN(t);
    EXPECT_NEAR(4.0,calc(t),eps);
}
TEST(Lexem, calculation_validation_11)
{
    string s = "2.36548---2158+9";
    double ans = 2.36548 - 2158 + 9;
    vector<Lexem> t;
    priority_creation();
    from_string_to_vector(s,t);
    t = RPN(t);
    EXPECT_NEAR(ans,calc(t),eps);
}
TEST(Lexem, calculation_validation_12)
{
    string s = "5.1413 + -3.1415";
    double ans = 5.1413 - 3.1415;
    vector<Lexem> t;
    priority_creation();
    from_string_to_vector(s,t);
    t = RPN(t);
    EXPECT_NEAR(ans,calc(t),eps);
}
TEST(Lexem, calculation_validation_13)
{
	string s = "2 - - - - 2";
	double ans = 4;
	vector<Lexem> t;
	priority_creation();
	from_string_to_vector(s, t);
	t = RPN(t);
	EXPECT_NEAR(ans, calc(t), eps);
}
TEST(Lexem, calculation_validation_14)
{
	string s = "2 + - - - - 2";
	double ans = 4;
	vector<Lexem> t;
	priority_creation();
	from_string_to_vector(s, t);
	t = RPN(t);
	EXPECT_NEAR(ans, calc(t), eps);
}

/*Correctness of math expression */

TEST(Lexem, correctness_of_math_expression_div_0_1)
{
    string s = "42/(3559*3559-1321*9588-733)";
    vector<Lexem> t;
    priority_creation();
    from_string_to_vector(s,t);
    t = RPN(t);
    ASSERT_ANY_THROW(calc(t));
}
TEST(Lexem, correctness_of_math_expression_div_0_2)
{
    string s = "42/ln(1)";
    vector<Lexem> t;
    priority_creation();
    from_string_to_vector(s,t);
    t = RPN(t);
    ASSERT_ANY_THROW(calc(t));
}
TEST(Lexem, correctness_of_math_expression_negative_argument_1)
{
    string s = "42/ln(-1)";
    vector<Lexem> t;
    priority_creation();
    from_string_to_vector(s,t);
    t = RPN(t);
    ASSERT_ANY_THROW(calc(t));
}
TEST(Lexem, correctness_of_math_expression_negative_argument_2)
{
    string s = "ln(ln(exp(-42)))";
    vector<Lexem> t;
    priority_creation();
    from_string_to_vector(s,t);
    t = RPN(t);
    ASSERT_ANY_THROW(calc(t));
}
TEST(Lexem, correctness_of_math_expression_negative_argument_3)
{
    string s = "sqrt(cos(3.14159265))";
    vector<Lexem> t;
    priority_creation();
    from_string_to_vector(s,t);
    t = RPN(t);
    ASSERT_ANY_THROW(calc(t));
}

/*Calculation validation with parameters*/

TEST(Lexem, calculation_validation_with_parameters_1)
{
    string s = "(a*b)";
    vector<Lexem> t;
    
    double a, b, ans;
    a = 3.14159265;
    b = 0.31830988;
    ans = a * b;

    vector<double> param;
    param.push_back(a);
    param.push_back(b);

    priority_creation();
    from_string_to_vector(s,t);
    set_parameters(t,param);
    clear_parameters();
    t = RPN(t);

    EXPECT_NEAR(ans,calc(t),eps);
}
TEST(Lexem, calculation_validation_with_parameters_2)
{
    string s = "(a*b)+a";
    vector<Lexem> t;
    
    double a, b, ans;
    a = 3.14159265;
    b = 0.31830988;
    ans = a * b + a;

    vector<double> param;
    param.push_back(a);
    param.push_back(b);

    priority_creation();
    from_string_to_vector(s,t);
    set_parameters(t,param);
    clear_parameters();
    t = RPN(t);

    EXPECT_NEAR(ans,calc(t),eps);
}
TEST(Lexem, calculation_validation_with_parameters_3)
{
    string s = "65*78.35-ln(2*a*b)+z-97.65";
    vector<Lexem> t;
    
    double a, b, c, ans;
    a = 3.14159265;
    b = 0.31830988;
    c = 23.71;
    ans = 65 * 78.35 - log(2 * a * b) + c - 97.65;

    vector<double> param;
    param.push_back(a);
    param.push_back(b);
    param.push_back(c);
    priority_creation();
    from_string_to_vector(s,t);
    set_parameters(t,param);
    clear_parameters();
    t = RPN(t);

    EXPECT_NEAR(ans,calc(t),eps);
}
TEST(Lexem, calculation_validation_with_parameters_4)
{
    string s = "ln(exp(sqrt(4*(cos(-exp(sqrt(f)))*cos(-exp(sqrt(f)))+sin(-exp(sqrt(f)))*sin(-exp(sqrt(f)))))))+r";
    vector<Lexem> t;
    
    double a, b, ans;
    a = 6.02214129e2;
    b = 3.14159265;
    ans = 2.0 + b;

    vector<double> param;
    param.push_back(a);
    param.push_back(b);
    priority_creation();
    from_string_to_vector(s,t);
    set_parameters(t,param);
    clear_parameters();
    t = RPN(t);

    EXPECT_NEAR(ans,calc(t),eps);
}

/*Correctness of math expression with parameters*/

TEST(Lexem, correctness_of_math_expression_with_parameters_div_0_1)
{
    string s = "ln(a)/b";
    vector<Lexem> t;

    double a, b;
    a = 3.14159265;
    b = 0;

    vector<double> param;
    param.push_back(a);
    param.push_back(b);
    priority_creation();
    from_string_to_vector(s,t);
    set_parameters(t,param);
    clear_parameters();
    t = RPN(t);

    ASSERT_ANY_THROW(calc(t));
}
TEST(Lexem, correctness_of_math_expression_with_parameters_div_0_2)
{
    string s = "46*73.7154-ln(a)/(b+a)";
    vector<Lexem> t;

    double a, b;
    a = 3.14159265;
    b = -a;

    vector<double> param;
    param.push_back(a);
    param.push_back(b);
    priority_creation();
    from_string_to_vector(s,t);
    set_parameters(t,param);
    clear_parameters();
    t = RPN(t);
    
    ASSERT_ANY_THROW(calc(t));
}
TEST(Lexem, correctness_of_math_expression_with_parameters_negative_argument_1)
{
    string s = "42/ln(b)+a/8+14.365";
    vector<Lexem> t;

    double a, b;
    a = 3.14159265;
    b = -a;

    vector<double> param;
    param.push_back(a);
    param.push_back(b);
    priority_creation();
    from_string_to_vector(s,t);
    set_parameters(t,param);
    clear_parameters();
    t = RPN(t);

    ASSERT_ANY_THROW(calc(t));
}
TEST(Lexem, correctness_of_math_expression_with_parameters_negative_argument_2)
{
    string s = "1.0+2.1+3.2+4.3/a+f-sqrt(a*(-b+3))";
    vector<Lexem> t;
   
    double a, b, c;
    a = 3.14159265;
    b = 8;
    c = -a;

    vector<double> param;
    param.push_back(a);
    param.push_back(b);
    param.push_back(c);
    priority_creation();
    from_string_to_vector(s,t);
    set_parameters(t,param);
    clear_parameters();
    t = RPN(t);

    ASSERT_ANY_THROW(calc(t));
}
TEST(Lexem, correctness_of_math_expression_with_parameters_negative_argument_3)
{
    string s = "exp(s)+sqrt(cos(z))";
    vector<Lexem> t;

    double a, b;
    a = 3.14159265;
    b = exp(1);
    vector<double> param;
    param.push_back(a);
    param.push_back(b);
    priority_creation();
    from_string_to_vector(s,t);
    set_parameters(t,param);
    clear_parameters();
    t = RPN(t);

    ASSERT_ANY_THROW(calc(t));
}