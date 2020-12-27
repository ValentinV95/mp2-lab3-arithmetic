// тесты для вычисления арифметических выражений

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
    tmp = "a+b*c-d";

    TPostfix k(tmp);

    string res;
    res = "abc*+d-";

    EXPECT_EQ(res, k.ToPostfix());
}
TEST(TPostfix, allegiance_test_three)
{
    string tmp;
    tmp = "a/d*k-c*z";

    TPostfix k(tmp);

    string res;
    res = "ad/k*cz*-";

    EXPECT_EQ(res, k.ToPostfix());
}
TEST(TPostfix, allegiance_test_four)
{
    string tmp;
    tmp = "(a+b)-d*(k-z)";

    TPostfix k(tmp);

    string res;
    res = "ab+dkz-*-";

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

TEST(TPostfix, test_on_calculate_three)
{
    string a;
    a = "(100-50)/2-(10*2)";

    TPostfix k(a);
    k.ToPostfix();

    double tmp = k.Calculate();
    double res = 5;

    EXPECT_EQ(res, tmp);
}

TEST(TPostfix, test_on_calculate_four)
{
    string a;
    a = "1024/2-(2048/2-100*3+2)*2+(8192/2)";

    TPostfix k(a);
    k.ToPostfix();

    double tmp = k.Calculate();
    double res = 3156;

    EXPECT_EQ(res, tmp);
}
