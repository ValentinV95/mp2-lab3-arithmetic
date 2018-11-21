// тесты для стека

#include "stack.h"
#include <gtest.h>
TEST(stack, can_push_el)
{
    stack<int> s;  
    ASSERT_NO_THROW(s.push(9));
}
TEST(stack, can_pop_el)
{
    stack<int> s; 
    s.push(9);
    ASSERT_NO_THROW(s.pop());
}
TEST(stack, can_get_number_el)
{
    stack<int> s; 
    for(int i = 0; i < 11; i++)
    {
       s.push(i); 
    }
    EXPECT_EQ(11, s.number());
}
TEST(stack, can_resize_stack)
{
    stack<int> s(2); 
    
    for(int i = 0; i < 4; i++)
    {
       s.push(i); 
    }
    EXPECT_EQ(3, s.pop());
}
TEST(stack, throws_when_pop_empty_stack)
{
    stack<int> s; 
    for(int i = 0; i < 10; i++)
    {
       s.push(i); 
    }
    for(int i = 0; i < 10; i++)
    {
       s.pop(); 
    }
    ASSERT_ANY_THROW(s.pop());
}
