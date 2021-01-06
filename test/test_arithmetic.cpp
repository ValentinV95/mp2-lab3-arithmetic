#include "arithmetic.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
    ASSERT_NO_THROW(TPostfix("a+b"));
}
TEST(TPostfix, allegiance_test_one)
{
    string tmp;
    tmp = "a+b";

    TPostfix k(tmp);

    string res;
    res = "ab+";

    EXPECT_EQ(res, k.ToPostfix());
}
TEST(TPostfix, allegiance_test_two)
{
    string tmp;
    tmp = "a+b*c";

    TPostfix k(tmp);

    string res;
    res = "abc*+";

    EXPECT_EQ(res, k.ToPostfix());
}
TEST(TPostfix, allegiance_test_three)
{
    string tmp;
    tmp = "a*d/k";

    TPostfix k(tmp);

    string res;
    res = "ad*k/";

    EXPECT_EQ(res, k.ToPostfix());
}
TEST(TPostfix, allegiance_test_four)
{
    string tmp;
    tmp = "(a+b)-d*k";

    TPostfix k(tmp);

    string res;
    res = "ab+-dk*";

    EXPECT_EQ(res, k.ToPostfix());
}
TEST(TPostfix, allegiance_test_five)
{
    string tmp;
    tmp = "(a+b-c*k)/(d-(z*e-p))";

    TPostfix k(tmp);

    string res;
    res = "ab+ck*-dze*p--/";

    EXPECT_EQ(res, k.ToPostfix());
}
TEST(TPostfix, test_on_calculate_one)
{
    string a;
    a="20+3";

    TPostfix k(a);
    k.ToPostfix();

    double tmp=k.Calculate();
    double res = 23;

    EXPECT_EQ(res, tmp);

}
TEST(TPostfix, test_on_calculate_two)
{
string a;
a = "20*3-100/10";

TPostfix k(a);
k.ToPostfix();

double tmp = k.Calculate();
double res = 50;

EXPECT_EQ(res, tmp);
}

TEST(TPostfix, test_on_calculate_minus)
{
    string a;
    a = "-10.5+10.5";

    TPostfix k(a);
    k.ToPostfix();

    double tmp = k.Calculate();
    double res = 0;

    EXPECT_EQ(res, tmp);
}

TEST(TPostfix, test_on_calculate_four_difficult)
{
    string a;
    a = "-10+10*(-1)+2/4";

    TPostfix k(a);
    k.ToPostfix();

    double tmp = k.Calculate();
    double res = -19.5;

    EXPECT_EQ(res, tmp);
}

