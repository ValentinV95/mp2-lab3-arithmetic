// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_size)
{
	ASSERT_NO_THROW(TStack <int> s(5));
}

TEST(TStack, cant_create_stack_with_negative_size)
{
	ASSERT_ANY_THROW(TStack <int> s(-5));
}

TEST(TStack, cant_create_stack_with_zero_size)
{
	ASSERT_ANY_THROW(TStack <int> s(0));
}

TEST(TStack, can_push_element_in_non_full_stack)
{
	TStack <int> s(2);
	int a = 5;
	s.Push(a);

	EXPECT_EQ(1, s.GetCount());
}

TEST(TStack, can_push_element_in_full_stack)
{
	TStack <int> s(2);
	int a = 5;
	int b = 4;
	int c = 3;
	s.Push(a);
	s.Push(b);
	s.Push(c);

	EXPECT_EQ(3, s.GetCount());
}

TEST(TStack, can_pop_element_out_of_non_empty_stack)
{
	TStack <int> s(2);
	int a = 5;
	int b = 4;
	s.Push(a);
	s.Push(b);

	EXPECT_EQ(4, s.Pop());
}

TEST(TStack, cant_pop_out_of_empty_stack)
{
	TStack <int> s(5);
	ASSERT_ANY_THROW(s.Pop());
}

TEST(TStack, full_stack_is_full)
{
	TStack <int> s(2);
	int a = 5;
	int b = 4;
	s.Push(a);
	s.Push(b);

	ASSERT_TRUE(s.IsFull());
}

TEST(TStack, non_full_stack_is_not_full)
{
	TStack <int> s(3);
	int a = 5;
	int b = 4;
	s.Push(a);
	s.Push(b);

	ASSERT_FALSE(s.IsFull());
}

TEST(TStack, empty_stack_is_empty)
{
	TStack <int> s(5);

	ASSERT_TRUE(s.IsEmpty());
}


TEST(TStack, non_empty_stack_is_not_empty)
{
	TStack <int> s(3);
	int a = 5;
	int b = 4;
	s.Push(a);
	s.Push(b);

	ASSERT_FALSE(s.IsFull());
}

TEST(TStack, can_get_head_element)
{
	TStack <int> s(3);
	int a = 5;
	int b = 4;
	s.Push(a);
	s.Push(b);

	EXPECT_EQ(4, s.GetHeadElement());
}

TEST(TStack, cant_get_head_element_if_stack_is_empty)
{
	TStack <int> s(3);

	ASSERT_ANY_THROW(s.GetHeadElement());
}

TEST(TStack, can_get_count_of_elements_in_stack)
{
	TStack <int> s(3);
	int a = 5;
	int b = 4;
	s.Push(a);
	s.Push(b);
	s.Pop();

	EXPECT_EQ(1, s.GetCount());
}

TEST(TStack, can_clear_stack)
{
	TStack <int> s(3);
	int a = 5;
	int b = 4;
	s.Push(a);
	s.Push(b);
	s.Clear();

	ASSERT_TRUE(s.IsEmpty());
}