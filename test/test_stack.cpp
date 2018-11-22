// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(TStack, can_generate_stack_without_leight)
{
	ASSERT_NO_THROW(TStack <int> stk);
}
TEST(TStack, can_generate_stack_with_leight)
{
	ASSERT_NO_THROW(TStack <int> stk(20));
}
TEST(TStack, can_create_stack_with_wrong_leight)
{
	ASSERT_ANY_THROW(TStack <int> stk(-20));
}
TEST(TStack, new_stack_is_empty)
{
	TStack <int> stk(20);
	EXPECT_EQ(stk.Empty(), true);
}
TEST(TStack, can_push_to_empty_st)
{
	TStack <int> stk;
	ASSERT_NO_THROW(stk.Push(3));

}
TEST(TStack, can_push_and_check)
{
	TStack <int> stk;
	stk.Push(45);
	EXPECT_EQ(stk.CheckLast(), 45);

}
TEST(TStack, can_push_and_pop)
{
	TStack <int> stk;
	stk.Push(45);
	stk.Pop();
	EXPECT_EQ(stk.Empty(), true);
}

TEST(TStack, overflow_of_massive)
{
	TStack <int> stk(2);
	stk.Push(1);
	stk.Push(2);
	stk.Push(3);
	ASSERT_NO_THROW(stk.Push(4));
}
TEST(TStack, can_pop_empty_stack)
{
	TStack <int> stk;
	ASSERT_ANY_THROW(stk.Pop());
}

TEST(TStack, check_top_elements)
{
	TStack <int> stk(4);
	stk.Push(1);
	stk.Push(2);
	stk.Push(3);
	stk.Pop();
	EXPECT_NE(stk.CheckLast(), 3);
}
TEST(TStack, check_dif_size_0f_stk)
{
	TStack <int> stk(2);
	stk.Push(1);
	stk.Push(2);
	stk.Push(3);
	stk.Push(4);
	EXPECT_NE(stk.GetSize(), 2);

}
TEST(TStack, check_size_of_clear_stk)
{
	TStack <int> stk(20);
	EXPECT_EQ(stk.GetSize(), 20);
}

TEST(TStack, can_check_last_in_empty)
{
	TStack <int> stk;
	ASSERT_ANY_THROW(stk.CheckLast());
}
TEST(TStack, clear_stk)
{
	TStack <int> stk;
	stk.Push(1);
	stk.Push(1);
	stk.Push(1);
	stk.Push(1);
	stk.Push(1);
	stk.Push(1);
	stk.Push(1);
	stk.ClearStack();

	EXPECT_EQ(stk.Empty(), true);

}
