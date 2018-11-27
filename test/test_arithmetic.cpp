#include <gtest.h>
#include "arithmetic.h"

TEST(exp, Correct1)
{
	string s = "25*2-43";
	string str = error_checking(s);
	EXPECT_EQ(7, calculate(convertPpn(str)));
}

TEST(exp, Correct2)
{
	string s = "-+25+33";
	string str = error_checking(s);
	EXPECT_EQ(8, calculate(convertPpn(str)));
}

TEST(exp, Correct3)
{
	string s = "98+-91";
	string str = error_checking(s);
	EXPECT_EQ(7, calculate(convertPpn(str)));
}

TEST(exp, Correct4)
{
	string s = "28*3/12";
	string str = error_checking(s);
	EXPECT_EQ(7, calculate(convertPpn(str)));
}

TEST(exp, Correct5)
{
	string s = "-21/-3";
	string str = error_checking(s);
	EXPECT_EQ(7, calculate(convertPpn(str)));
}

TEST(exp, Correct6)
{
	string s = "-1*-7+(-12)";
	string str = error_checking(s);
	EXPECT_EQ(-5, calculate(convertPpn(str)));
}

TEST(exp, Correct7)
{
	string s = "1/-(4+6))";
	string str = error_checking(s);
	EXPECT_EQ(-0.1, calculate(convertPpn(str)));
}

TEST(exp, THROW1)
{
	ASSERT_ANY_THROW(brackets_error("-1*-7)"));
}

TEST(exp, THROW2)
{
	ASSERT_ANY_THROW(brackets_error("-1)(*-7"));
}

TEST(exp, THROW3)
{
	ASSERT_ANY_THROW(error_checking(".-1*-7"));
}

TEST(exp, THROW4)
{
	ASSERT_ANY_THROW(error_checking("-1.*-7"));
}

TEST(exp, THROW5)
{
	ASSERT_ANY_THROW(error_checking("-/25*3"));
}

TEST(exp, THROW6)
{
	ASSERT_ANY_THROW(error_checking("-*25/3"));
}

TEST(exp, THROW7)
{
	ASSERT_ANY_THROW(error_checking("-25 /3"));
}

TEST(exp, THROW8)
{
	ASSERT_ANY_THROW(error_checking("-25:3"));
}

TEST(exp, THROW9)
{
	ASSERT_ANY_THROW(error_checking("-25/3,0"));
}

TEST(exp, THROW10)
{
	ASSERT_ANY_THROW(error_checking("25/0"));
}