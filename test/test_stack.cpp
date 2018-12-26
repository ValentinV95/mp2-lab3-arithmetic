#include "stack.h"
#include <gtest.h> 
#include <gtest.h>
#include "stack.h"
#include <gtest.h>
#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create_stack)
{
	ASSERT_NO_THROW(Stack<int> st(10));
}
TEST(Stack, can_push_elem)
{
	Stack<int> st(10);
	ASSERT_NO_THROW(st.Push(1));
}
TEST(Stack, can_pop_elem)
{
	Stack<int> st(10);
	st.Push(1);
	ASSERT_NO_THROW(st.Pop());
}
TEST(Stack, can_get_size)
{
	Stack<int> st(100);
	for (int i = 0; i < 10; i++)
		st.Push(i);
	EXPECT_EQ(10, st.Size());
}
TEST(Stack, can_get_top_elem)
{
	Stack<int> st(10);
	st.Push(1);
	EXPECT_EQ(1, st.Value());
}
TEST(Stack, can_resize_stack)
{
	Stack<int> st(10);

	for (int i = 0; i < 15; i++)
	{
		st.Push(i);
	}
	EXPECT_EQ(15, st.Size());
}

TEST(Stack, throws_when_pop_empty_stack)
{
	Stack<int> st(2);
	st.Push(1);
	st.Pop();
	ASSERT_ANY_THROW(st.Pop());
}
TEST(Stack, throws_when_get_value_from_empty_stack)
{
	Stack<int> st(10);
	int temp;
	ASSERT_ANY_THROW(temp = st.Value());
}
TEST(Stack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(Stack<int> st(10));
}
TEST(Stack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(Stack<int> st(-1));
}

TEST(Stack, can_get_stack_current_size)
{
	Stack<int> st(10);
	for (int i = 0; i < 5; i++)
		st.Push(i);
	EXPECT_EQ(5, st.Size());
}
TEST(Stack, can_check_if_stack_is_empty)
{
	Stack<int> st(10);
	EXPECT_EQ(st.IsEmpty(), true);
}

TEST(Stack, can_delete_all_elements)
{
	Stack<int> st(10);
	for (int i = 0; i < 5; i++)
		st.Push(i);
	st.Empty();
	EXPECT_EQ(st.IsEmpty(), true);
}