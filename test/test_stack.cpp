// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> st(5));
}
TEST(TStack, cant_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-3));
}

TEST(TStack, can_create_copied_stack)
{
	TStack<int> st(5);
	ASSERT_NO_THROW(TStack<int> st1(st));
}

TEST(TStack, copied_stack_has_its_own_memory)
{
	TStack<int> st1(4);
	TStack<int> st2(4);

	st1.Put(1);
	st1.Put(2);
	st2.Put(1);
	st2.Put(2);
	EXPECT_FALSE(&st1 == &st2);
}

TEST(TStack, can_add_in_full_stack)
{
	ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 1));
}

TEST(TStack, can_get_next_index)
{
	TStack<int> st(5);
	EXPECT_EQ(2, st.GetNextIndex(1));
}

TEST(TStack, can_capture_element_of_empty_stack)
{
	TStack<int>st(1);
	ASSERT_ANY_THROW(st.Get());
}

TEST(TStack, can_not_put_value_in_full_stack)
{
	TStack<int> st(100);
	for (int i = 0; i < 100; i++)
		st.Put(5);
	ASSERT_ANY_THROW(st.Put(5));
}

TEST(TStack, is_stack_empty)
{
	TStack<int> st(3);
	EXPECT_EQ(true, st.IsEmpty());
}

TEST(TStack, is_stack_full)
{
	TStack<int> st(100);
	{
		for (int i = 0; i < 100; i++)
			st.Put(1);
		EXPECT_EQ(true, st.IsFull());
	}
}

TEST(TStack, different_stacks_have_different_memory)
{
	TStack<int> st1(5), st2(10);
	EXPECT_NE(&st1, &st2);
}
