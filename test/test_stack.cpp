// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(Stack <int> T (10));
};

TEST(Stack, can_not_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(Stack <int> T(-7));
};

TEST(Stack, can_push_element)
{
	Stack <int> T(4);
	T.Push(15);
	T.Push(16);

	EXPECT_EQ(T.GetSize(),2);
};

TEST(Stack, can_push_element_with_realloc_memory)
{
	Stack <int> T(2);

	T.Push(15);
	T.Push(16);

	ASSERT_NO_THROW(T.Push(17));
	EXPECT_EQ(T.GetSize(),3);
};

TEST(Stack, push_to_full_stack_has_right_element_on_top)
{
	Stack <int> T(2);
	T.Push(15);
	T.Push(16);
	T.Push(17);

	EXPECT_EQ(T.Pop(),17);
};

TEST(Stack, can_pop_element)
{
	Stack <int> T(4);
	T.Push(15);
	T.Push(16);
	
	EXPECT_EQ(T.Pop(),16);
	EXPECT_EQ(T.GetSize(),1); 	
};

TEST(Stack, can_not_pop_element_when_stack_is_empty)
{
	Stack <int> T(4);
	T.Push(15);
	T.Pop();

	ASSERT_ANY_THROW(T.Pop());
};

TEST(Stack, can_look_at_the_end_of_stack)
{
	Stack <int> T(2);
	T.Push(15);
	T.Push(17);

	EXPECT_EQ(T.Value(),17);
	EXPECT_EQ(T.GetSize(),2);
};

TEST(Stack, can_not_look_at_the_end_if_stack_is_empty)
{
	Stack <int> T(2);

	ASSERT_ANY_THROW(T.Value());
};

TEST(Stack, can_see_if_stack_is_empty)
{
	Stack <int> T(2);

	EXPECT_EQ(T.isEmpty(),true);
};

TEST(Stack, can_see_if_stack_is_not_empty)
{
	Stack <int> T(2);
	T.Push(5);

	EXPECT_EQ(T.isEmpty(),false);
};

TEST(Stack, can_get_correct_size_of_stack)
{
	Stack <int> T(5);
	T.Push(1);
	T.Push(2);
	
	EXPECT_EQ(T.GetSize(),2);
};

TEST(Stack, can_clear_stack)
{
	Stack <int> T(5);
	T.Push(1);
	T.Push(2);
	T.Clear();

	EXPECT_EQ(T.isEmpty(),true);
};