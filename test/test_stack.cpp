// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create_empty_stack_with_positive_length)
{
	ASSERT_NO_THROW(Stack<int> stack(3));
}

TEST(Stack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(Stack<int> stack(-2));
}

TEST(Stack, can_push_element)
{
	Stack<int> stack(2);
	stack.push(28);
	EXPECT_EQ(stack.Size(), 1);
}

TEST(Stack, can_push_element_when_stack_is_full)
{
	Stack<int> stack(2);
	stack.push(4);
	stack.push(8);
	stack.push(15);
	stack.push(2);
	EXPECT_EQ(stack.Size(), 3);
}

TEST(Stack, can_pop_element)
{
	Stack<int> stack;
	stack.push(23);
	stack.push(42);
	EXPECT_EQ(stack.pop(), 42);
}

TEST(Stack, can_not_pop_element_when_stack_is_empty)
{
	Stack<int> stack(2);
	stack.push(16);
	stack.pop();
	ASSERT_ANY_THROW(stack.pop());
}

TEST(Stack, can_get_stack_current_size)
{
	Stack<int> stack;
	EXPECT_EQ(0, stack.Size());
	stack.push(2);
	EXPECT_EQ(1, stack.Size());
}

TEST(Stack, can_check_if_stack_is_empty)
{
	Stack<int> stack;
	EXPECT_EQ(stack.IsEmpty(), true);
	stack.push(3);
	EXPECT_EQ(stack.IsEmpty(), false);
	stack.pop();
	EXPECT_EQ(stack.IsEmpty(), true);
}

TEST(Stack, can_delete_all_elements)
{
	Stack<int> stack;
	stack.push(15);
	stack.push(-3);
	stack.Empty();
	EXPECT_EQ(stack.IsEmpty(), true);
}

TEST(Stack, can_get_Value_element)
{
	Stack<int> stack;
	stack.push(5);
	stack.push(12);
	EXPECT_EQ(stack.Value(), 12);
}

TEST(Stack, can_not_get_Value_element_when_stack_is_empty)
{
	Stack<int> stack(1);
	stack.push(115);
	stack.pop();
	ASSERT_ANY_THROW(stack.Value());
}