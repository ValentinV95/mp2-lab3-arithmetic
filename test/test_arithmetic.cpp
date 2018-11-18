// тесты для вычисления арифметических выражений

#include <gtest.h>
#include <arithmetic.h>

TEST(Is_op, operation)
{
	Calculate t("1");
	EXPECT_EQ(t.is_op('-'), true);
}

TEST(Is_op, operation1)
{
	Calculate t("1");
	EXPECT_EQ(t.is_op('2'), false);
}

TEST(Is_op, operation2)
{
	Calculate t("1");
	EXPECT_EQ(t.is_op('*'), true);
}

TEST(Is_op, operation3)
{
	Calculate t("1");
	EXPECT_EQ(t.is_op('q'), false);
}

TEST(delim, operation)
{
	Calculate t("1");
	EXPECT_EQ(t.delim('-'), false);
}

TEST(delim, operation1)
{
	Calculate t("1");
	EXPECT_EQ(t.delim(' '), true);
}

TEST(is_digit, operation)
{
	Calculate t("1");
	EXPECT_EQ(t.is_digit(' '), false);
}

TEST(is_digit, operation1)
{
	Calculate t("1");
	EXPECT_EQ(t.is_digit('2'), true);
}

TEST(is_digit, operation2)
{
	Calculate t("1");
	EXPECT_EQ(t.is_digit('3'), true);
}

TEST(is_digit, operation3)
{
	Calculate t("1");
	EXPECT_EQ(t.is_digit('0'), true);
}

TEST(Prover1, check1)
{
	Calculate t("2 + 3 - x + (ml)");
	EXPECT_ANY_THROW(t.Prover1());
}

TEST(Prover1, check2)
{
	Calculate t("2 + 3 = 2");
	EXPECT_ANY_THROW(t.Prover1());
}

TEST(Prover1, check3)
{
	Calculate t("2 + 3 - x + 2.5.2");
	EXPECT_ANY_THROW(t.Prover1());
}

TEST(Prover1, check4)
{
	Calculate t("2 + 3 - x + 2.5");
	EXPECT_EQ(t.Prover1(), true);
}

TEST(Prover1, check5)
{
	Calculate t("2 + 3 - x + 2.5 + (2 - 2)*67 - x");
	EXPECT_EQ(t.Prover1(), true);
}

TEST(Prover1, check6)
{
	Calculate t("2 + 3 - x + 2.5 + (2 - 2)*67 - x + y*z - 25*i ------5 + 6 + r");
	EXPECT_EQ(t.Prover1(), true);
}

TEST(Prover2, check1)
{
	Calculate t("2 + 3 - x + 2.5 + (2 - 2)*67 - x + y*z - 25*i ------5 + 6 + r");
	EXPECT_EQ(t.Prover2(), true);
}

TEST(Prover2, check2)
{
	Calculate t("(2 + (2*3) + 2) - (2 - 1)");
	EXPECT_EQ(t.Prover2(), true);
}

TEST(Prover2, check3)
{
	Calculate t("(2 + (2*3) + 2) - ((2 - 1) - 1)");
	EXPECT_EQ(t.Prover2(), true);
}

TEST(Prover2, check4)
{
	Calculate t("(((2 + (2*3) + 2) - (2 - 1)))");
	EXPECT_EQ(t.Prover2(), true);
}

TEST(Prover2, check5)
{
	Calculate t("2 + (2*3) + 2) - (2 - 1)");
	EXPECT_ANY_THROW(t.Prover2());
}

TEST(Prover2, check6)
{
	Calculate t("(2 + 2*3) + 2) - (2 - 1)");
	EXPECT_ANY_THROW(t.Prover2());
}

TEST(Prover2, check7)
{
	Calculate t("(2 + (2*3) + 2) - (2 - 1)(");
	EXPECT_ANY_THROW(t.Prover2());
}

TEST(Prover2, check8)
{
	Calculate t("(");
	EXPECT_ANY_THROW(t.Prover2());
}

TEST(Prover2, check9)
{
	Calculate t(")");
	EXPECT_ANY_THROW(t.Prover2());
}

TEST(Prover3, check)
{
	Calculate t("23 34");
	EXPECT_ANY_THROW(t.Prover3());
}

TEST(Prover3, check1)
{
	Calculate t("(+2 - 3)");
	EXPECT_ANY_THROW(t.Prover3());
}

TEST(Prover3, check2)
{
	Calculate t("(*2 + 3) + 2");
	EXPECT_ANY_THROW(t.Prover3());
}

TEST(Prover3, check3)
{
	Calculate t("2 + (2 +)");
	EXPECT_ANY_THROW(t.Prover3());
}

TEST(Prover3, check4)
{
	Calculate t("*-2");
	EXPECT_ANY_THROW(t.Prover3());
}

TEST(Prover3, check5)
{
	Calculate t("-+34");
	EXPECT_ANY_THROW(t.Prover3());
}

TEST(Prover3, check6)
{
	Calculate t("/*-+");
	EXPECT_ANY_THROW(t.Prover3());
}

TEST(Prover3, check7)
{
	Calculate t("(*2)");
	EXPECT_ANY_THROW(t.Prover3());
}

TEST(Prover3, check8)
{
	Calculate t("23*(2 + 2 -)");
	EXPECT_ANY_THROW(t.Prover3());
}

TEST(Prover3, check9)
{
	Calculate t("-2 * 3 - 2 + 2()");
	EXPECT_ANY_THROW(t.Prover3());
}

TEST(Prover3, check10)
{
	Calculate t("(2 + 2)3");
	EXPECT_ANY_THROW(t.Prover3());
}

TEST(Prover3, check11)
{
	Calculate t("(2 + 3)-");
	EXPECT_ANY_THROW(t.Prover3());
}

TEST(Prover3, check12)
{
	Calculate t("(+)");
	EXPECT_ANY_THROW(t.Prover3());
}

TEST(Prover3, check13)
{
	Calculate t("x(");
	EXPECT_ANY_THROW(t.Prover3());
}

TEST(Prover3, check14)
{
	Calculate t(")x");
	EXPECT_ANY_THROW(t.Prover3());
}

TEST(Prover3, check15)
{
	Calculate t("+x - 2");
	EXPECT_ANY_THROW(t.Prover3());
}

TEST(Prover3, check16)
{
	Calculate t("(*x)");
	EXPECT_ANY_THROW(t.Prover3());
}

TEST(Prover3, check17)
{
	Calculate t("sin10 x");
	EXPECT_ANY_THROW(t.Prover3());
}

TEST(Prover3, check18)
{
	Calculate t("log3(");
	EXPECT_ANY_THROW(t.Prover3());
}

TEST(Prover3, check19)
{
	Calculate t("log3(");
	EXPECT_ANY_THROW(t.Prover3());
}
TEST(Prover3, check20)
{
	Calculate t("x log3");
	EXPECT_ANY_THROW(t.Prover3());
}

TEST(Prover3, check21)
{
	Calculate t("log3/x");
	EXPECT_EQ(t.Prover3(), true);
}

TEST(Prover3, check22)
{
	Calculate t("log3 - x");
	EXPECT_EQ(t.Prover3(), true);
}

TEST(Prover3, check23)
{
	Calculate t("log3 + 2");
	EXPECT_EQ(t.Prover3(), true);
}

TEST(Prover3, check24)
{
	Calculate t("log3 * 2");
	EXPECT_EQ(t.Prover3(), true);
}

TEST(Prover3, check25)
{
	Calculate t("log3 - x + 5 - (2*3) - 14");
	EXPECT_EQ(t.Prover3(), true);
}

TEST(is_fuction, check)
{
	Calculate t("sin10");
	EXPECT_EQ(t.is_function("sin"), true);
}

TEST(is_fuction, check1)
{
	Calculate t("sin10");
	EXPECT_EQ(t.is_function("sin10"), false);
}

TEST(is_fuction, check2)
{
	Calculate t("sin10");
	EXPECT_EQ(t.is_function("cos"), true);
}

TEST(is_fuction, check3)
{
	Calculate t("sin10");
	EXPECT_EQ(t.is_function("r"), false);
}

TEST(is_fuction, check4)
{
	Calculate t("sin10");
	EXPECT_EQ(t.is_function("tan"), true);
}

TEST(is_fuction, check5)
{
	Calculate t("sin10");
	EXPECT_EQ(t.is_function("log"), true);
}

TEST(is_fuction, check6)
{
	Calculate t("sin10");
	EXPECT_EQ(t.is_function("sqrt"), true);
}

TEST(is_fuction, check7)
{
	Calculate t("sin10");
	EXPECT_EQ(t.is_function(",fdsfs"), false);
}

TEST(val_func, check)
{
	Calculate t("1");
	EXPECT_EQ(t.val_func("sin0", 0), 0);
}

TEST(val_func, check1)
{
	Calculate t("1");
	EXPECT_EQ(t.val_func("sqrt4", 0), 2);
}

TEST(val_func, check2)
{
	Calculate t("1");
	EXPECT_ANY_THROW(t.val_func("sqrt-4", 0));
}

TEST(calc, check)
{
	Calculate t("2 + 2");
	EXPECT_EQ(t.calc(), 4);
}

TEST(calc, check1)
{
	Calculate t("2 + 2*2 - 2 + (2 - 2*3)/4 + 2 - 7");
	EXPECT_EQ(t.calc(), -2);
}

TEST(calc, check2)
{
	Calculate t("2 + 2*2 - 2 + (2 - 2*3)/4 + 2 + 2*sqrt4 + (2 - 7 + 5/5 + 1 - 98)");
	EXPECT_EQ(t.calc(), -92);
}

TEST(calc, check3)
{
	Calculate t("2 + 2*2 - 2 + (2 - 2*3)/4 + 2 + 2*sqrt4 + (2 - 7 + 5/5 + 1 - 98) + sin0");
	EXPECT_EQ(t.calc(), -92);
}

TEST(calc, check4)
{
	Calculate t("2 + 2*2 - 2 + (2 - 2*3)/4 + 2 + 2*sqrt4 + (2 - 7 + 5/5 + 1 - 98) + cos0");
	EXPECT_EQ(t.calc(), -91);
}

TEST(calc, check5)
{
	Calculate t("2 + 2*2 - 2 + (2 - 2*3)/4 + 2 + 2*sqrt4 + (2 - 7 + 5/5 + 1 - 98) + cos0 + log1");
	EXPECT_EQ(t.calc(), -91);
}

TEST(calc, check6)
{
	Calculate t("98 -- 98");
	EXPECT_EQ(t.calc(), 196);
}

TEST(calc, check7)
{
	Calculate t("98 --- 98");
	EXPECT_EQ(t.calc(), 0);
}

TEST(calc, check8)
{
	Calculate t("-98 -- 98");
	EXPECT_EQ(t.calc(), 0);
}

TEST(calc, check9)
{
	Calculate t("-1 + 2*9 + 7*9 - 5/4 - 25*(1/0)");
	EXPECT_ANY_THROW(t.calc());
}
