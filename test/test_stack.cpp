// тесты для стека

#include "stack.h"
#include <gtest.h>
TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> st(5));
}
TEST(TStack, can_not_create_stack_with_negative_size)
{
	ASSERT_ANY_THROW(TStack<int> st(-1));
}

TEST(TStack, can_not_create_stack_with_large_size)
{
	ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 1));
}
TEST(TStack, two_different_stacks_have_different_memories)
{
	TStack<int> s1(2), s2(3);
	EXPECT_NE(&s1, &s2);
}
TEST(TStack, check_stack_for_empty)
{
	TStack<int> s1(5);
	EXPECT_EQ(true, s1.IsEmpty());
}
TEST(TStack, check_stack_for_full)
{
	TStack<int> s1(5);
	for (int i = 0; i < 5; i++)
		s1.Push(i);
	EXPECT_EQ(true, s1.IsFull());
}
TEST(TStack, can_clear_stack)
{
	TStack<int> s1(5);
	for (int i = 0; i < 5; i++)
		s1.Push(i);
	s1.Clear();
	EXPECT_EQ(true, s1.IsEmpty());
}
TEST(TStack, can_erase_last_element_in_stack)
{
	TStack<int> s1(5);
	for (int i = 0; i < 5; i++)
		s1.Push(i);
	s1.Erase();
	EXPECT_EQ(false, s1.IsFull());
}
TEST(TStack, can_take_element_in_stack_pop_with_corrected_value)
{
	TStack<int> s1(5);
	for (int i = 0; i < 5; i++)
		s1.Push(i);
	EXPECT_EQ(4, s1.Pop());
}
TEST(TStack, element_is_delete_on_pop)
{
	TStack<int> s1(5);
	for (int i = 0; i < 5; i++)
		s1.Push(i);
	int a = s1.Pop();
	EXPECT_EQ(false, s1.IsFull());
}
TEST(TStack, can_view_last_element_in_stack_without_delete_him)
{
	TStack<int> s1(5);
	for (int i = 0; i < 5; i++)
		s1.Push(i);
	int a = s1.PopWithoutDelete();
	EXPECT_EQ(true, s1.IsFull());
}
TEST(TStack, method_pop_without_delete_return_correct_value)
{
	TStack<int> s1(5);
	for (int i = 0; i < 5; i++)
		s1.Push(i);
	EXPECT_EQ(4, s1.PopWithoutDelete());
}
TEST(TStack, can_know_length_now)
{
	TStack<int>s1(5);
	s1.Push(1);
	EXPECT_EQ(1, s1.Length());
}