#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> s(5));
}

TEST(TStack, cannot_create_stack_with_negative_length)
{
    ASSERT_ANY_THROW(TStack<int> s(-5));
}

TEST(TStack, cannot_create_stack_with_large_length)
{
    ASSERT_ANY_THROW(TStack<int> s(MAX_SIZE_STACK + 1));
}

TEST(TStack, can_set_and_get_element)
{
    TStack<int> s(4);

    s.Push(2);

    EXPECT_EQ(s.Pop(), 2);
}


TEST(TStack, can_get_size)
{
    TStack<int> s(5);

    EXPECT_EQ(5, s.GetSize());
}

TEST(TStack, can_show_elem_of_stack)
{
    TStack<int> s(4);

    s.Push(4);

    EXPECT_EQ(4, s.Top());
}


TEST(TStack, check_on_not_empty_stack)
{
    TStack<int> s(4);

    s.Push(2);

    EXPECT_NE(true, s.IsEmpty());
}

TEST(TStack, check_on_not_full_stack)
{
    TStack<int> s(5);


    EXPECT_NE(true, s.IsFull());
}



TEST(TStack, pop)
{
    TStack<int> s(5);
    s.Push(5);
    ASSERT_NO_THROW(s.Pop());
}

TEST(TStack, push)
{
    TStack<int> s(5);
    ASSERT_NO_THROW(s.Push(5));
}



TEST(TStack, can_push)
{
    TStack<int> s(5);

    s.Push(3);

    EXPECT_EQ(false, s.IsEmpty());
}
