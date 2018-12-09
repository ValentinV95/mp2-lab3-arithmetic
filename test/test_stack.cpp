// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create_stack_with_positive_size)
{
	ASSERT_NO_THROW(Stack<int> st(10));
}

TEST(Stack, can_not_create_stack_with_negative_size)
{
	ASSERT_ANY_THROW(Stack<int> st(-10));
}

TEST(Stack, stack_is_empty)
{
	Stack<int> st(5);
	EXPECT_EQ(true, st.IsEmpty());
}

TEST(Stack, correct_pop)
{
	Stack<int> st(10);
	for (int i = 0; i < 10; i++)
		st.push(i);
	st.pop();
	EXPECT_EQ(false, st.IsEmpty());
}
TEST(Stack, correct_push)
{
	Stack<int> st(10);
	ASSERT_NO_THROW(st.push(1));
}

TEST(Stack, correct_front)
{
	Stack<int> st(10);
	for (int i = 0; i < 10; i++)
		st.push(i);
	EXPECT_EQ(9, st.Front());
}

TEST(Stack, throws_when_pop_empty_stack)
{
	Stack<int> st(10);
	st.push(1);
	st.pop();
	ASSERT_ANY_THROW(st.pop());
}

TEST(Stack, correct_clean)
{
	Stack<int> st(10);
	for (int i = 0; i < 10; i++)
		st.push(i);
	st.Clean();
	EXPECT_EQ(true, st.IsEmpty());
}

TEST(Stack, get_size)
{
	Stack<int> st(10);
	for (int i = 0; i < 10; i++)
		st.push(i);
	EXPECT_EQ(10, st.Size());
}