// тесты для стека

#include "stack.h"
#include <gtest.h>
TEST(Stack, can_create_stack_with_positive_size)
{
	ASSERT_NO_THROW(Stack<int> s(5));
}

TEST(Stack, cant_create_stack_with_negative_size)
{
	ASSERT_ANY_THROW(Stack<int> s(-1));
}

TEST(Stack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(Stack<int> s(MAX_STACK_SIZE + 1));
}

TEST(Stack, can_get_size)
{
	Stack<int> s1(10);
	EXPECT_EQ(10, s1.GetSize());
}

TEST(Stack, can_push_element_when_stack_is_not_full)
{
	Stack<int> s1(5);
	s1.Push(1);
	EXPECT_EQ(0, s1.CheckTop());
}

TEST(Stack, can_push_element_when_stack_is_full)
{
	Stack<int> s1(5);
	for (int i = 0; i < 5; i++)
	{
		s1.Push(1);
	}
	s1.Push(1);
	EXPECT_EQ(5, s1.CheckTop());
}

TEST(Stack, can_check_top)
{
	Stack<int> s1(5);
	EXPECT_EQ(-1, s1.CheckTop());
}

TEST(Stack, stack_is_empty)
{
	Stack<int> s1(5);
	EXPECT_EQ(true, s1.IsEmpty());
}

TEST(Stack, stack_is_full)
{
	Stack<int> s1(5);
	for (int i = 0; i < 5; i++)
		s1.Push(1);
	EXPECT_EQ(true, s1.IsFull());
}


TEST(Stack, throws_when_pop_element_from_empty_stack)
{
	Stack<int> s1(5);
	ASSERT_ANY_THROW(s1.Pop());
}


TEST(Stack, can_pop_element)
{
	Stack<int> s1(5);
	for (int i = 0; i < 5; i++)
		s1.Push(1);
	s1.Pop();
	EXPECT_EQ(3, s1.CheckTop());
}




TEST(Stack, can_clear_stack)
{
	Stack<int> s1(5);
	for (int i = 0; i < 5; i++)
		s1.Push(1);
	s1.ClearStack();
	EXPECT_EQ(-1, s1.CheckTop());
}
