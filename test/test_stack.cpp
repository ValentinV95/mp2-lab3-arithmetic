// тесты для стека
#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> stack(3));
}

TEST(TStack, cant_create_stack_with_wrong_size)
{
	ASSERT_ANY_THROW(TStack<int> stack(-1));
	ASSERT_ANY_THROW(TStack<int> stack(MaxStackSize + 1));
}

TEST(TStack, is_stack_empty)
{
	TStack<int> stack(3);
	EXPECT_EQ(true, stack.IsEmpty());
}

TEST(TStack, is_stack_full)
{
	TStack<int> stack(100);
	for (int i = 0; i < 100; i++)
	{
		stack.Put(1);
	}
	EXPECT_EQ(true, stack.IsFull());
}

TEST(TStack, can_get_next_index)
{
	TStack<int> stack(10);
	for (int i = 0; i < 5; i++)
	{
		stack.Put(1);
	}
	EXPECT_EQ(5, stack.GetNextIndex());
}

TEST(TStack, can_get_value_from_stack)
{
	TStack<int> stack1(3), stack2(3);
	stack1.Put(5);
	stack2.Put(stack1.Get());
	EXPECT_EQ(5, stack2.Get());
}

TEST(TStack, cant_get_value_from_empty_stack)
{
	TStack<int> stack(3);
	ASSERT_ANY_THROW(stack.Get());
}

TEST(TStack, cant_put_value_in_full_stack)
{
	TStack<int> stack(100);
	for (int i = 0; i < 100; i++)
	{
		stack.Put(1);
	}
	ASSERT_ANY_THROW(stack.Put(1));
}

TEST(TStack, can_put_value)
{
	TStack<int> stack(3);
	stack.Put(1);
	EXPECT_EQ(1, stack.Get());
}

TEST(TStack, can_assign_stacks_of_same_size)
{
	TStack<int> stack1(3), stack2(3);
	stack1.Put(1);
	ASSERT_NO_THROW(stack1 = stack2);
}

TEST(TStack, assign_changes_size_of_stack)
{
	TStack<int> stack1(10), stack2(3);
	for (int i = 0; i < 9; i++)
	{
		stack1.Put(1);
	}
	stack2 = stack1;
	EXPECT_EQ(9, stack2.GetNextIndex());
}

TEST(TStack, can_assign_stack_to_itself)
{
	TStack<int> stack1(3);
	stack1.Put(1);
	ASSERT_NO_THROW(stack1 = stack1);
}

TEST(TStack, can_copy_stack)
{
	TStack<int> stack1(10);
	for (int i = 0; i < 9; i++)
	{
		stack1.Put(1);
	}
	TStack<int> stack2(stack1);
	EXPECT_EQ(9, stack2.GetNextIndex());
}

TEST(TStack, different_stacks_have_different_memory)
{
	TStack<int> stack1(5), stack2(10);
	EXPECT_NE(&stack1, &stack2);
}