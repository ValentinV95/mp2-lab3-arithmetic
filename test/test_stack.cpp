// тесты для стека

#include "gtest.h"
#include "arithmetic.h"


TEST(Stack, can_create_stack_with_positive_MaxSize)
{
    ASSERT_NO_THROW(Stack<int> s(3));
}
TEST(Stack, throws_when_create_stack_with_negative_MaxSize)
{
    ASSERT_ANY_THROW(Stack<int> s(-1));
}

TEST(Stack, can_get_size)
{
    Stack<int> s(3);
    s.Push(3);
    ASSERT_NO_THROW(s.Size());
    EXPECT_EQ(1, s.Size());
}

TEST(Stack, can_copy_the_stack)
{
    Stack<int> s(3);
    s.Push(3);
    ASSERT_NO_THROW(Stack<int> copy(s));
}

TEST(Stack, the_copied_stack_is_the_same_as_the_original_one)
{
    Stack<int> s(3);
    s.Push(3);
    Stack<int> copy(s);
    EXPECT_EQ(s.Size(), copy.Size());
    EXPECT_EQ(s.Pop(), copy.Pop());
}

TEST(Stack, can_assign_stacks_of_the_same_data_types_and_MaxSize)
{
    Stack<int> s1(5);
    Stack<int> s2(5);
    s1.Push(5);
    s1.Push(7);
    s2.Push(3);
    ASSERT_NO_THROW(s2 = s1);
    EXPECT_EQ(s1.Size(), s2.Size());
    EXPECT_EQ(s1.Pop(), s2.Pop());
}
TEST(Stack, can_assign_stacks_of_the_same_data_types_and_different_MaxSize)
{
    Stack<int> s1(8);
    Stack<int> s2(5);
    s1.Push(5);
    s1.Push(7);
    s2.Push(3);
    ASSERT_NO_THROW(s2 = s1);
    EXPECT_EQ(s1.Size(), s2.Size());
    EXPECT_EQ(s1.Pop(), s2.Pop());
}

TEST(Stack, can_compare_stacks)
{
    Stack<int> s1(5);
    Stack<int> s2(5);
    s1.Push(5);
    s2.Push(3);
    ASSERT_NO_THROW(s2 == s1);
}

TEST(Stack, comparing_the_stack_with_itself_gives_the_truth)
{
    Stack<int> s(5);
    EXPECT_EQ(1, s == s);
}

TEST(Stack, comparing_the_same_stack_gives_the_truth)
{
    Stack<int> s1(5);
    Stack<int> s2(5);
    s1.Push(5);
    s2.Push(5);
    EXPECT_EQ(1, s1 == s2);
}

TEST(Stack, comparing_different_stack_gives_the_lie)
{
    Stack<int> s1(5);
    Stack<int> s2(5);
    s1.Push(5);
    s2.Push(5);
    EXPECT_EQ(1, s1 == s2);
}
TEST(Stack, can_check_the_stack_for_emptiness)
{
    Stack<int> s(5);
    ASSERT_NO_THROW(s.Empty());
}
TEST(Stack, initially_the_stack_is_empty)
{
    Stack<int> s(5);
    EXPECT_EQ(true, s.Empty());
}
TEST(Stack, a_stack_with_a_size_greater_than_zero_is_not_empty)
{
    Stack<int> s(5);
    s.Push(5);
    EXPECT_EQ(false, s.Empty());
}
TEST(Stack, can_check_the_stack_for_completeness)
{
    Stack<int> s(5);
    ASSERT_NO_THROW(s.Full());
}
TEST(Stack, if_the_stack_size_is_equal_to_the_MaxSize_then_the_stack_is_full)
{
    int max_size = 2;
    Stack<int> s(max_size);
    s.Push(1);
    s.Push(2);
    EXPECT_EQ(s.Size(), max_size);
    EXPECT_EQ(true, s.Full());
}
TEST(Stack, can_add_an_item_to_an_incomplete_stack)
{
    Stack<int> s(3);
    ASSERT_NO_THROW(s.Push(3));
}
TEST(Stack, cant_add_an_item_to_the_full_stack)
{
    Stack<int> s(1);
    s.Push(5);
    ASSERT_ANY_THROW(s.Push(5));
}
TEST(Stack, can_see_what_is_at_the_top_of_a_non_empty_stack)
{
    Stack<int> s(3);
    s.Push(3);
    ASSERT_NO_THROW(s.Top());
}
TEST(Stack, viewing_the_top_of_the_stack_does_not_change_the_state_of_the_stack)
{
    Stack<int> s(3);
    s.Push(3);
    int size = s.Size();
    int a = s.Top();
    EXPECT_EQ(size, s.Size());
    EXPECT_EQ(a, s.Top());
}
TEST(Stack, cant_look_at_the_top_of_an_empty_stack)
{
    Stack<int> s(3);
    ASSERT_ANY_THROW(s.Top());
}
TEST(Stack, can_take_an_element_from_a_non_empty_non_empty_stack)
{
    Stack<int> s(3);
    s.Push(3);
    ASSERT_NO_THROW(s.Pop());
}
TEST(Stack, taking_an_element_from_the_stack_reduces_its_size_by_one)
{
    Stack<int> s(3);
    int a = 2, b = 3;
    s.Push(a);
    s.Push(b);
    int size = s.Size();
    int elem = s.Pop();
    EXPECT_EQ(elem, b);
    EXPECT_EQ(size - 1, s.Size());
}
TEST(Stack, cant_take_an_element_from_an_empty_stack)
{
    Stack<int> s(5);
    ASSERT_ANY_THROW(s.Pop());
}