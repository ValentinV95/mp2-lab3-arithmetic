// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<int> s);
}

TEST(TStack, cant_create_stack_with_null_size)
{
	ASSERT_ANY_THROW(TStack<int> s(0));
}

TEST(TStack, can_create_copied_stack)
{
	TStack<int> s;

	ASSERT_NO_THROW(TStack<int> s1);
}

TEST(TStack, can_push_element_in_stack)
{
	TStack<int> s;

	ASSERT_NO_THROW(s.push(5));
}

TEST(TStack, can_push_element_in_full_stack)
{
	TStack<int> s(2);
	const int expVal = -1;

	s.push(8); s.push(2);
	s.push(expVal);

	EXPECT_EQ(expVal, s.getTop());
}

TEST(TStack, can_check_on_emptiness_for_empty_stack)
{
	TStack<int> s;
	bool expVal = true;

	EXPECT_EQ(expVal, s.isEmpty());
}

TEST(TStack, can_check_on_emptiness_for_not_empty_stack)
{
	TStack<int> s;
	bool expVal = false;

	s.push(3);

	EXPECT_EQ(expVal, s.isEmpty());
}

TEST(TStack, can_check_on_full_for_full_stack)
{
	TStack<int> s(2);
	bool expVal = true;

	s.push(1); s.push(2);

	EXPECT_EQ(expVal, s.isFull());
}

TEST(TStack, can_check_on_full_for_not_full_stack)
{
	TStack<int> s;
	bool expVal = false;

	EXPECT_EQ(expVal, s.isFull());
}

TEST(TStack, can_get_top_element_without_deletion)
{
	TStack<int> s(1);
	const int expVal = 10;
	bool expEmp = false;

	s.push(expVal);

	EXPECT_EQ(expVal, s.getTop());
	EXPECT_EQ(expEmp, s.isEmpty());
}

TEST(TStack, can_pop_element)
{
	TStack<int> s;
	const int expVal = -9;
	bool expEmp = true;

	s.push(expVal);

	EXPECT_EQ(expVal, s.pop());
	EXPECT_EQ(expEmp, s.isEmpty());
}

TEST(TStack, cant_pop_element_from_empty_stack)
{
	TStack<int> s;

	ASSERT_ANY_THROW(s.pop());
}

TEST(TStack, cant_get_top_element_from_empty_stack)
{
	TStack<int> s;

	ASSERT_ANY_THROW(s.getTop());
}
