// òåñòû äëÿ ñòåêà

#include "stack.h"
#include <gtest.h>
TEST(TStack, can_push_el)
{
    TStack<int> s;
    ASSERT_NO_THROW(s.push(9));
}
TEST(TStack, can_pop_el)
{
    TStack<int> s;
    s.push(9);
    ASSERT_NO_THROW(s.pop());
}
TEST(TStack, can_get_number_el)
{
    TStack<int> s;
    for (int i = 0; i < 11; i++)
    {
        s.push(i);
    }
    EXPECT_EQ(11, s.number());
}
TEST(TStack, can_resize_stack)
{
    TStack<int> s(2);

    for (int i = 0; i < 4; i++)
    {
        s.push(i);
    }
    EXPECT_EQ(3, s.pop());
}
TEST(TStack, throws_when_pop_empty_stack)
{
    TStack<int> s;
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
