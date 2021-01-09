// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"

TEST(work, test_arifm0)
{
	std::string s = "2+2";
	EXPECT_EQ(4, work(s));
}

TEST(work, test_arifm1)
{
	std::string s = "-2+2";
	EXPECT_EQ(0, work(s));
}

TEST(work, test_arifm2)
{
	std::string s = "-2+2*2";
	EXPECT_EQ(2, work(s));
}

TEST(work, test_arifm3)
{
	std::string s = "1/5*cos(9*0)";
	EXPECT_EQ(0.2, work(s));
}

TEST(work, test_arifm4)
{
	std::string s = "1/-10";
	EXPECT_EQ(-0.1, work(s));
}

TEST(work, test_arifm5)
{
	std::string s = "5--5";
	EXPECT_EQ(10, work(s));
}

TEST(work, test_arifm6)
{
	std::string s = "5---5+sin(8*1/8)";
	EXPECT_EQ(0, work(s));
}

TEST(work, test_arifm7)
{
	std::string s = "ln(1) ";
	EXPECT_EQ(0, work(s));
}

TEST(work, test_arifm8)
{
	std::string s = "5*/6";
	ASSERT_ANY_THROW(work(s));
}

TEST(work, test_arifm9)
{
	std::string s = "ln()";
	ASSERT_ANY_THROW(work(s));
}

TEST(work, test_arifm10)
{
	std::string s = "cos*6";
	ASSERT_ANY_THROW(work(s));
}

TEST(work, test_arifm11)
{
	std::string s = "5*6(";
	ASSERT_ANY_THROW(work(s));
}

TEST(work, test_arifm12)
{
	std::string s = "5*6test";
	ASSERT_ANY_THROW(work(s));
}

TEST(work, test_arifm13)
{
	std::string s = "2*(cos(0)-2))";
	ASSERT_ANY_THROW(work(s));
}

TEST(work, test_arifm14)
{
	std::string s = "ln(!)";
	ASSERT_ANY_THROW(work(s));
}