#include "pch.h"
#include "../../Lab 3. Stack, RPN/Lab 3. Stack, RPN/stack.h"
#include "../../Lab 3. Stack, RPN/Lab 3. Stack, RPN/arithmetic.h"
#include "../../Lab 3. Stack, RPN/Lab 3. Stack, RPN/arithmetic.cpp"
TEST(TStack, push) {
	const int N = 11;
	TStack<int> s;

	for (int i = 0; i < N; i++) 
		s.push(i);
	
	EXPECT_EQ(s.size(), N);
}
TEST(TStack, pop) {
	const int N = 11;
	TStack<int> s;

	
	ASSERT_ANY_THROW(s.pop()); //throws when pop empty stack

	for (int i = 0; i < N; i++) 
		s.push(i);
	
	for (int i = N - 1; i >= 0; i--) 
		EXPECT_EQ(s.pop(), i); //popped elements are correct
	
	EXPECT_EQ(s.size(), 0);
}

TEST(TStack, top) {
	const int N = 11;
	TStack<int> s;

	ASSERT_ANY_THROW(s.top());

	for (int i = 0; i < N; i++) 
		s.push(i);
	
	for (int i = 0; i < N; i++)
		EXPECT_EQ(s.top(), N - 1);
	
	EXPECT_EQ(s.size(), N);
}

TEST(TStack, empty_clear_size) {
	const int N = 11;
	TStack<int> s;

	ASSERT_TRUE(s.empty());
	EXPECT_EQ(s.size(), 0);

	for (int i = 0; i < N; i++)
		s.push(i);

	ASSERT_FALSE(s.empty());
	EXPECT_EQ(s.size(), N);

	for (int i = 0; i < N; i++)
		s.pop();

	ASSERT_TRUE(s.empty());
	EXPECT_EQ(s.size(), 0);

	s.push(9);

	ASSERT_FALSE(s.empty());
	EXPECT_EQ(s.size(), 1);

	s.clear();

	ASSERT_TRUE(s.empty());
	EXPECT_EQ(s.size(), 0);
}

TEST(arithmetic, constructor) {
	ASSERT_NO_THROW(arithmetic("1+2"));
	ASSERT_ANY_THROW(arithmetic("1+2 +  + 7"));

	ASSERT_ANY_THROW(arithmetic("(12/2*7"));
	ASSERT_ANY_THROW(arithmetic("cos"));
	ASSERT_ANY_THROW(arithmetic("1*/8"));
}

TEST(arithmetic, isCorrect) {
	ASSERT_TRUE(arithmetic::isCorrect("1+2*(5-16/3)-4"));
	ASSERT_TRUE(arithmetic::isCorrect("-5*9.6+14/(3+56.)-2"));
	ASSERT_TRUE(arithmetic::isCorrect("    5 + 6 + (-2*3)  "));

	ASSERT_FALSE(arithmetic::isCorrect("--1+2 + 8 +  + 7"));
	ASSERT_FALSE(arithmetic::isCorrect("1+2^9.0 + 7"));
	ASSERT_FALSE(arithmetic::isCorrect("1+0.32 / ((7*3)"));
}

TEST(arithmetic, COUNT_transform_deleteSpaces_LeftRightCharacter_isSymbolsCorrect) {
	ASSERT_NEAR(arithmetic("1+2").count(), 3.0, 1e-15);
	ASSERT_NEAR(arithmetic("-5*9.6+14/(2.8+4.2)-2").count(), -48.0, 1e-15);
	ASSERT_NEAR(arithmetic("(((1 + 1) * 1 + 1) * 1 + 1) + 1").count(), 5.0, 1e-15);
	ASSERT_NEAR(arithmetic("-11+11").count(), 0.0, 1e-15);
	ASSERT_NEAR(arithmetic("12-(-12)").count(), 24.0, 1e-15);
	ASSERT_NEAR(arithmetic("10-(-(-10)) + 1/(-5)").count(), -0.2, 1e-15);
	ASSERT_NEAR(arithmetic("-(-5.703)").count(), 5.703, 1e-15);
	ASSERT_NEAR(arithmetic("-11.3").count(), -11.3, 1e-15);
	ASSERT_NEAR(arithmetic("(12/2)+((56/8)-11)").count(), 2, 1e-15);
	ASSERT_NEAR(arithmetic("12/2*5").count(), 30.0, 1e-15);
}
TEST(arithmetic, priority) {
	EXPECT_EQ(priority('*'), priority('/'));
	EXPECT_EQ(priority('+'), priority('-'));
	ASSERT_FALSE(priority('*') < priority('-'));
	ASSERT_TRUE(priority('/') >= priority('+'));
}
