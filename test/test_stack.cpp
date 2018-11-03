#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_empty_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> s(3));
}

TEST(TStack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> s(-2));
}

TEST(TStack, can_get_stack_current_size)
{
	TStack<int> s;
	EXPECT_EQ(0, s.CurrentSize());
	s.push(2);
	EXPECT_EQ(1, s.CurrentSize());
}

TEST(TStack, can_get_front_element)
{
	TStack<int> s;
	s.push(5);
	s.push(12);
	EXPECT_EQ(s.front(), 12);
}

TEST(TStack, can_not_get_front_element_when_stack_is_empty)
{
	TStack<int> s(1);
	s.push(115);
	s.pop();
	ASSERT_ANY_THROW(s.front());
}

TEST(TStack, can_check_if_stack_is_empty)
{
	TStack<int> s;
	EXPECT_EQ(s.isEmpty(), true);
	s.push(3);
	EXPECT_EQ(s.isEmpty(), false);
	s.pop();
	EXPECT_EQ(s.isEmpty(), true);
}

TEST(TStack, can_check_if_stack_is_full)
{
	TStack<int> s(1);
	EXPECT_EQ(s.isFull(), false);
	s.push(15);
	EXPECT_EQ(s.isFull(), true);
}

TEST(TStack, can_delete_all_elements)
{
	TStack<int> s(2);
	s.push(15);
	s.push(-3);
	s.AllClear();
	EXPECT_EQ(s.isEmpty(), true);
}

TEST(TStack, can_push_element)
{
	TStack<int> s(2);
	s.push(28);
	EXPECT_EQ(s.CurrentSize(), 1);
}

TEST(TStack, can_push_element_when_stack_is_full)
{
	TStack<int> s(2);
	s.push(4);
	s.push(8);
	ASSERT_NO_THROW(s.push(15));
	EXPECT_EQ(s.CurrentSize(), 3);
}

TEST(TStack, can_pop_element)
{
	TStack<int> s;
	s.push(23);
	s.push(42);
	EXPECT_EQ(s.pop(), 42);
}

TEST(TStack, can_not_pop_element_when_stack_is_empty)
{
	TStack<int> s(2);
	s.push(16);
	s.pop();
	ASSERT_ANY_THROW(s.pop());
}
