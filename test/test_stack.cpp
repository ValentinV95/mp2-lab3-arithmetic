// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack <int> a);
}

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack <int> a(3));
}

TEST(TStack, can_not_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack <int> a(-3));
}

TEST(TStack, can_look_at_the_top)
{
	TStack <double> a;
	a.push(3.14);
	EXPECT_EQ(a.front(), 3.14);
}

TEST(TStack, can_not_look_at_the_top_if_stack_is_empty)
{
	TStack <double> a;
	ASSERT_ANY_THROW(a.front());
}

TEST(TStack, can_push)
{
	TStack <int> a;
	a.push(4);
	EXPECT_EQ(a.size(), 1);
}

TEST(TStack, can_push_to_full_stack_with_memory_realloc)
{
	TStack <int> a(2);
	a.push(4);
	a.push(1);
	ASSERT_NO_THROW(a.push(89));
	EXPECT_EQ(a.size(), 3);
}

TEST(TStack, push_to_full_stack_has_right_element_on_top)
{
	TStack <int> a(2);
	a.push(4);
	a.push(1);
	a.push(45);
	EXPECT_EQ(a.front(), 45);
}

TEST(TStack, pop_from_empty_stack_throw_error)
{
	TStack <int> a;
	ASSERT_ANY_THROW(a.pop());
}

TEST(TStack, can_pop)
{
	TStack <int> a;
	a.push(4);
	a.push(8);
	EXPECT_EQ(a.pop(), 8);
	EXPECT_EQ(a.size(), 1);
}

TEST(TStack, can_see_if_stack_is_empty)
{
	TStack <int> a;
	EXPECT_EQ(a.is_empty(), true);
}

TEST(TStack, can_see_if_stack_is_not_empty)
{
	TStack <int> a;
	a.push(32);
	EXPECT_EQ(a.is_empty(), false);
}

TEST(TStack, can_get_stack_current_size)
{
	TStack <int> a;
	a.push(32);
	a.push(4);
	EXPECT_EQ(a.size(), 2);
}