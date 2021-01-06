// тесты для стека

#include "stack.h"
#include <gtest.h>
TEST(TStack, push) {
    const int N = 11;
    TStack<int> s;

    for (int i = 0; i < N; i++)
        s.push(i);
    
    EXPECT_EQ(s.size(), N);
}
TEST(TStack, pop) {
    const int N = 11;
    TStack<int> s;

    
    ASSERT_ANY_THROW(s.pop()); //throws when pop empty stack

    for (int i = 0; i < N; i++)
        s.push(i);
    
    for (int i = N - 1; i >= 0; i--)
        EXPECT_EQ(s.pop(), i); //popped elements are correct
    
    EXPECT_EQ(s.size(), 0);
}

TEST(TStack, top) {
    const int N = 11;
    TStack<int> s;

    ASSERT_ANY_THROW(s.top());

    for (int i = 0; i < N; i++)
        s.push(i);
    
    for (int i = 0; i < N; i++)
        EXPECT_EQ(s.top(), N - 1);
    
    EXPECT_EQ(s.size(), N);
}

TEST(TStack, empty_clear_size) {
    const int N = 11;
    TStack<int> s;

    ASSERT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);

    for (int i = 0; i < N; i++)
        s.push(i);

    ASSERT_FALSE(s.empty());
    EXPECT_EQ(s.size(), N);

    for (int i = 0; i < N; i++)
        s.pop();

    ASSERT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);

    s.push(9);

    ASSERT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 1);

    s.clear();

    ASSERT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);
}
