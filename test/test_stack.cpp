#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create_stack)
{
    ASSERT_NO_THROW(Stack<int> v());
}
TEST(Stack, can_push_elem)
{
    Stack<int> v;  
    ASSERT_NO_THROW(v.push(1));
}
TEST(Stack, can_pop_elem)
{
    Stack<int> v; 
    v.push(1);
    ASSERT_NO_THROW(v.pop());
}
TEST(Stack, can_get_size)
{
    Stack<int> v; 
    for(int i = 0; i < 10; i++)
    {
       v.push(i); 
    }
    EXPECT_EQ(10,v.GetSize());
}
TEST(Stack, can_get_front_elem)
{
    Stack<int> v; 
    for(int i = 0; i < 10; i++)
    {
       v.push(i); 
    }
    EXPECT_EQ(9, v.front());
}
TEST(Stack, can_resize_stack)
{
    Stack<int> v; 
    int temp = v.GetSize();
    for(int i = 0; i <= 10; i++)
    {
       v.push(i); 
    }
    EXPECT_EQ(2 * temp, v.GetSize());
}
TEST(Stack, throws_when_pop_empty_stack)
{
    Stack<int> v; 
    for(int i = 0; i <= 10; i++)
    {
       v.push(i); 
    }
    for(int i = 0; i <= 10; i++)
    {
       v.pop(); 
    }
    ASSERT_ANY_THROW(v.pop());
}
TEST(Stack, throws_when_get_front_from_empty_stack)
{
    Stack<int> v; 
    int a;
    ASSERT_ANY_THROW(a = v.front());
}