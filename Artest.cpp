#include <gtest.h>
#include "arifmetika.h"
using namespace std;
TEST(work, test_arifm0)
{
	string s = "2+2";
	EXPECT_EQ(4, work(s));
}

TEST(work, test_arifm1)
{
	string s = "-2+2";
	EXPECT_EQ(0, work(s));
}

TEST(work, test_arifm2)
{
	string s = "-2+2*2";
	EXPECT_EQ(2, work(s));
}

TEST(work, test_arifm3)
{
	string s = "1/-10";
	EXPECT_EQ(-0.1, work(s));
}

TEST(work, test_arifm4)
{
	string s = "5--5";
	EXPECT_EQ(10, work(s));
}
TEST(work, test_arifm5)
{
	string s = "5*/6";
	ASSERT_ANY_THROW(work(s));
}
TEST(work, test_arifm6)
{
	string s = "5*6(";
	ASSERT_ANY_THROW(work(s));
}

TEST(work, test_arifm7)
{
	string s = "5*6test";
	ASSERT_ANY_THROW(work(s));
}