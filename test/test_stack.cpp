// тесты для стека

#include <gtest.h>
#include "stack.h"

TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<int> s);
}

TEST(TStack, can_create_stack_with_positive_lenght)
{
	ASSERT_NO_THROW(TStack<int> s(1));
}

TEST(TStack, throws_when_create_stack_with_negative_lenght)
{
	ASSERT_ANY_THROW(TStack<int> s(-1));
}

TEST(TStack, can_push_element_in_stack)
{
	TStack<int> s;

	ASSERT_NO_THROW(s.Push(1));
}

TEST(TStack, can_push_elements_in_stack_more_than_original_size_suggests)
{
	TStack<int> s(3);
	s.Push(1);
	s.Push(2);
	s.Push(3);

	ASSERT_NO_THROW(s.Push(4));
}

TEST(TStack, can_pop_element_from_stack)
{
	TStack<int> s;

	s.Push(1);

	EXPECT_EQ(1, s.Pop());
}

TEST(TStack, throws_when_pop_element_from_empty_stack)
{
	TStack<int> s;

	s.Push(1);
	s.Pop();

	ASSERT_ANY_THROW(s.Pop());
}

TEST(TStack, Pop_deletes_element_on_the_top_of_stack)
{
	TStack<int> s(3);

	s.Push(3);
	s.Push(2);
	s.Push(1);

	s.Pop();

	EXPECT_EQ(2, s.Pop());
}

TEST(TStack, can_check_element_on_top_of_stack)
{
	TStack<int> s;

	s.Push(1);

	EXPECT_EQ(1, s.CheckTop());
}

TEST(TStack, throws_when_check_element_on_top_of_empty_stack)
{
	TStack<int> s(3);

	s.Push(1);
	s.Pop();

	ASSERT_ANY_THROW(s.CheckTop());
}

TEST(TStack, CheckTop_dont_deletes_element_on_the_top_of_stack)
{
	TStack<int> s(3);

	s.Push(3);
	s.Push(2);
	s.Push(1);

	s.CheckTop();

	EXPECT_EQ(1, s.CheckTop());
}

TEST(TStack, checking_empty_stack_for_emptiness_returns_true)
{
	TStack<int> s(3);

	s.Push(1);
	s.Pop();

	EXPECT_EQ(true, s.IsEmpty());
}

TEST(TStack, cheking_not_empty_stack_for_emptiness_returns_false)
{
	TStack<int> s(3);

	s.Push(1);

	EXPECT_EQ(false, s.IsEmpty());
}

TEST(TStack, can_get_size)
{
	TStack<int> s(3);

	EXPECT_EQ(3, s.GetSize());
}

TEST(TStack, can_clean_stack)
{
	TStack<int> s;

	s.Push(3);
	s.Push(2);
	s.Push(1);

	s.Clean();

	EXPECT_EQ(true, s.IsEmpty());
}

TEST(TStack, if_size_is_more_than_N_it_is_changed_when_clean_stack)
{
	TStack<int> s(11);

	s.Clean();

	EXPECT_EQ(N, s.GetSize());
}
