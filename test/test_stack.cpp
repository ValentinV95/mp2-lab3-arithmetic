// тесты для стека

#include "stack.h"
#include <gtest.h>
TEST(Stack, can_push_el)
{
    Stack<int> s;
    ASSERT_NO_THROW(s.push(9));
}
TEST(Stack, is_new_stack_empty)
{
    Stack<int> s;
    EXPECT_EQ(true, s.IsEmpty());
    s.
}
TEST(Stack, is_new_stack_not_full)
{
    Stack<int> s;
    EXPECT_NE(true, s.IsFull());
}
TEST(Stack, can_pop_el)
{
    Stack<double> s;
    s.push(1.0);
    ASSERT_NO_THROW(s.pop());
}
TEST(Stack, can_get_number_el)
{
    Stack<int> s;
    for (int i = 0; i < 3; i++)
    {
        s.push(i);
    }
    EXPECT_EQ(3, s.number());
}
TEST(Stack, throws_when_pop_empty_stack)
{
    Stack<int> s;
    for (int i = 0; i < 10; i++)
    {
        s.push(i);
    }
    for (int i = 0; i < 10; i++)
    {
        s.pop();
    }
    ASSERT_ANY_THROW(s.pop());
}