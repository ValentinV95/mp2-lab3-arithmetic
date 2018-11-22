// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"


TEST(Lexem, can_lexeme)
{
	double a = 4;
	EXPECT_NO_THROW(Lexem S(a));
}
TEST(Lexem, can_lexeme_number)
{
	double a = 2;
	Lexem A(a);
	EXPECT_EQ(a, A.GetNum());
}
TEST(Lexem, can_lexeme_with_more_the_one)
{
	double a = 256;
	Lexem A(a);
	EXPECT_EQ(a, A.GetNum());
}
TEST(Lexem, can_lexeme_Operation)
{
	char a = '+';
	Lexem A(a);
	EXPECT_EQ(a, A.GetOper());
}
TEST(Lexem, can_parse_one)
{
	string a = "z";
	vector<Lexem> A;

	EXPECT_NO_THROW(A = Parsing(a));

}
TEST(Lexem, can_parse_more_then_one)
{
	string a = "z+z+2+(4+5)";
	vector<Lexem> A;

	EXPECT_NO_THROW(A = Parsing(a));

}
TEST(Lexem, can_lexeme_value)
{
	string a = "z";
	vector<Lexem> A;
	A = Parsing(a);
	EXPECT_EQ(A[0].IsNum(), true);
}
TEST(Lexem, unary_minus)
{
	string a = "-12+5";
	vector<Lexem> A;
	A = Parsing(a);
	A = Polish(A);
	EXPECT_EQ(A[0].GetNum(), -12);
}
TEST(Lexem, parsing_acting1)
{
	string a = "&^$#%0+2+4";
	vector<Lexem> A;
	A = Parsing(a);
	EXPECT_EQ(A[0].GetNum(), 0);
}
TEST(Lexem, parsing_acting2)
{
	string a = "4+2+4";
	vector<Lexem> A;
	A = Parsing(a);
	EXPECT_EQ(A[1].IsNum(), false);
}

//polish block
TEST(Lexem, do_polish1)
{
	string a = "4+2+4";
	vector<Lexem> A;
	double a1, b1=10;
	A = Parsing(a);
	A= Polish(A);
	a1 = Calc(A);
	EXPECT_EQ(a1,b1);
}
TEST(Lexem, do_polish2)
{
	string a = "4*2+4";
	string b = "4*(2+4)";
	vector<Lexem> A,B;
	double a1, b1;
	A = Parsing(a);
	A = Polish(A);
	B = Parsing(b);
	B = Polish(B);
	a1 = Calc(A);
	b1 = Calc(B);
	EXPECT_NE(a1, b1);
}
TEST(Lexem, do_polish3)
{
	string a = "f*2+4+f";
	vector<Lexem> A;
	double a1, b1=10;
	A = Parsing(a);
	A = PutVal(2,A);
	A = Polish(A);	
	a1 = Calc(A);
	EXPECT_EQ(a1, b1);
}
TEST(Lexem, division)
{
	string a = "4+5/0";
	vector<Lexem> A;
	double a1;
	A = Parsing(a);
	A = PutVal(2, A);
	A = Polish(A);
	
	EXPECT_ANY_THROW(a1 = Calc(A));
}


//checing block
TEST(string, can_check_syntax)
{
	string s = "4+++4";
		EXPECT_EQ(CheckSequence(s), false);

}
TEST(string, can_check_sk)
{
	string s = "(((4+4))";
	EXPECT_EQ(Skobki(s), false);

}
TEST(string, can_check_value)
{
	string s = "a+b+c+d";
	EXPECT_EQ(ValisOne(s), false);
}
TEST(string, Check_all)
{
	string a = "4+2+()*4";
	EXPECT_EQ(Checking_Block(a,11), false);
}