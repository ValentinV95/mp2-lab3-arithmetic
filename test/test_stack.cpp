// тесты для стека

#include "stack.h"
#include <gtest.h>
TEST(Stack, can_push_el)
{
    Stack<int> s;
    int k = 9;
    ASSERT_NO_THROW(s.push(k));
}
TEST(Stack, is_new_stack_empty)
{
    Stack<int> s;
    EXPECT_EQ(true, s.IsEmpty());
}
TEST(Stack, is_new_stack_not_full)
{
    Stack<int> s;
    EXPECT_NE(true, s.IsFull());
}
TEST(Stack, can_pop_el)
{
    Stack<double> s;
    double k = 1.0;
    s.push(k);
    ASSERT_NO_THROW(s.pop());
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