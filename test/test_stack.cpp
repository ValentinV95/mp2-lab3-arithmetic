// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(Stack<int> s);
}

TEST(Stack, can_create_stack_with_positive_length2)
{
	ASSERT_NO_THROW(Stack<int> s(2));
}

TEST(Stack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(Stack<int> s(-1));
}

TEST(Stack, throws_when_stack_is_empty)
{
	Stack<int> s;
	ASSERT_ANY_THROW(s.Pop());
}

TEST(Stack, can_push_element_in_full_stack)
{
	Stack<int> s;
	s.Push(1);
	s.Push(1);
	ASSERT_NO_THROW(s.Push(1));
}


TEST(Stack, can_Push_Check_element)
{
	Stack<int> s;
	s.Push(1);
	EXPECT_EQ (1, s.Check());
}

TEST(Stack, can_pop_element)
{
	Stack<int> s;
	s.Push(1);
	EXPECT_EQ (1, s.Pop());
}

TEST(Stack, cant_pop_element_of_empty_stack)
{
	Stack<int> s;
	ASSERT_ANY_THROW( s.Pop());
}

TEST(Stack, can_clear_stack)
{
	Stack<int> s;
	s.Push(1);
	s.Push(1);
	s.ClrSt();
	ASSERT_ANY_THROW(s.Pop());
}

TEST(Stack, can_clear_element_of_stack)
{
	Stack<int> s;
	s.Push(1);
	s.Push(1);
	s.ClrElem();
	EXPECT_EQ (1, s.GetSizeE());
}


