// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> m(5));
}

TEST(TStack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> m(-5));
}

TEST(TStack, determines_that_stack_is_empty)
{
	TStack<int> m (2);
	m.Push(2);
	m.Push(2);
	m.pop();
	m.pop();
	EXPECT_EQ(1, m.IsEmpty());
}

TEST(TStack, determines_that_stack_is_full)
{
	TStack<int> m (2);
	m.Push(2);
	m.Push(2);
	EXPECT_EQ(1, m.IsFull());
}

TEST(TStack, can_push_element)
{
	TStack<int> m (2);
	ASSERT_NO_THROW( m.Push(2));
}

TEST(TStack, can_pop_element)
{
	TStack<int> m (2);
	m.Push(2);
	EXPECT_EQ (2, m.pop());
}

TEST(TStack, cant_pop_element_of_empty_stack)
{
	TStack<int> m (2);
	ASSERT_ANY_THROW( m.pop());
}

TEST(TStack, can_push_element_in_full_stack)
{
	TStack<int> m (2);
	m.Push(2);
	m.Push(2);
	ASSERT_NO_THROW(m.Push(2));
}

TEST(TStack, allocates_new_memory_when_push_in_full_stack)
{
	TStack<int> m (2);
	m.Push(2);
	m.Push(2);
	m.Push(2);
	EXPECT_NE(2, m.GetSize());
}
