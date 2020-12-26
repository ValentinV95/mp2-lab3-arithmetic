// òåñòû äëÿ ñòåêà

#include "stack.h"
#include <gtest.h>

TEST(TStack, pop)
{
    TStack<int> s;
    s.push(5);
    ASSERT_NO_THROW(s.pop());
}
TEST(TStack, push)
{
    TStack<int> s;
    ASSERT_NO_THROW(s.push(5));
}
TEST(TStack, get_number)
{
    TStack<int> s;
    for (int i = 0; i < 11; i++)
    {
        s.push(i);
    }
    EXPECT_EQ(11, s.number());
}
TEST(TStack, change_size_stack)
{
    TStack<int> s(5);

    for (int i = 0; i < 10; i++)
    {
        s.push(i);
    }
    EXPECT_EQ(7, s.pop());
}
