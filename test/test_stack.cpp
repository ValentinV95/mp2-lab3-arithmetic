// тесты для стека

#include "stack.h"
#include <gtest.h>

//1
TEST(Stack, can_create_stack_with_positive_length)
{
    ASSERT_NO_THROW(Stack<int> st(1));
}

//2
TEST(Stack, throws_when_create_stack_with_negative_length)
{
    ASSERT_ANY_THROW(Stack<int> st(-1));
}

//3
TEST(Stack, throws_when_create_stack_with_length0)
{
    ASSERT_ANY_THROW(Stack<int> st(0));
}

//4
TEST(Stack, when_stack_is_empty_FuncIsEmpty_returnTRUE)
{
    Stack<int> st(10);

    EXPECT_EQ(st.IsEmpty(), true);
}

//5
TEST(Stack, when_stack_isnt_empty_and_isnt_full_FuncIsEmpty_returnFALSE)
{
    Stack<int> st(10);

    int a = 5;
    st.Push(a);

    EXPECT_EQ(st.IsEmpty(), false);
}

//6
TEST(Stack, when_stack_is_full_FuncIsEmpty_returnFALSE)
{
    Stack<int> st(1);

    int a = 5;
    st.Push(a);

    EXPECT_EQ(st.IsEmpty(), false);
}

//7
TEST(Stack, when_stack_is_empty_FuncIsFull_returnFALSE)
{
    Stack<int> st(1);

    EXPECT_EQ(st.IsFull(), false);
}

//8
TEST(Stack, when_stack_isnt_empty_and_isnt_full_FuncIsFull_returnFALSE)
{
    Stack<int> st(10);

    int a = 5;
    st.Push(a);

    EXPECT_EQ(st.IsFull(), false);
}

//9
TEST(Stack, when_stack_is_empty_FuncIsFull_returnTrue)
{
    Stack<int> st(1);

    int a = 5;
    st.Push(a);

    EXPECT_EQ(st.IsFull(), true);
}

//10
TEST(Stack, can_pop_when_stack_with_size1_is_full)
{
    Stack<int> st(1);

    int a = 5;
    st.Push(a);

    ASSERT_NO_THROW(st.Pop());
}

//11
TEST(Stack, compare_pop_when_stack_with_size1_is_full)
{
    Stack<int> st(1);

    int a = 5;
    st.Push(a);

    EXPECT_EQ(st.Pop(), 5);
}

//12
TEST(Stack, throw_when_pop_from_stack_with_size1_is_empty)
{
    Stack<int> st(1);

    ASSERT_ANY_THROW(st.Pop());
}

//13
TEST(Stack, throw_when_pop_from_stack_with_size2_is_empty)
{
    Stack<int> st(2);

    ASSERT_ANY_THROW(st.Pop());
}

//14
TEST(Stack, can_pop_from_stack_with_size2__with_1th_el_without_2th_el)
{
    Stack<int> st(2);

    int a = 5;
    st.Push(a);

    ASSERT_NO_THROW(st.Pop());
}

//15
TEST(Stack, compare_pop_from_stack_with_size2__with_1th_el_without_2th_el)
{
    Stack<int> st(2);

    int a = 5;
    st.Push(a);

    EXPECT_EQ(st.Pop(), 5);
}

//16
TEST(Stack, can_pop_from_stack_with_size2__with_1th_el_with_2th_el)
{
    Stack<int> st(2);

    int a = 5;
    int b = 6;
    st.Push(a);
    st.Push(b);

    ASSERT_NO_THROW(st.Pop());
}

//17
TEST(Stack, compare_pop_from_stack_with_size2__with_1th_el_with_2th_el)
{
    Stack<int> st(2);

    int a = 5;
    int b = 6;
    st.Push(a);
    st.Push(b);

    EXPECT_EQ(st.Pop(), 6);
}

//18
TEST(Stack, can_pop_x2_from_stack_with_size2__with_1th_el_with_2th_el)
{
    Stack<int> st(2);

    int a = 5;
    int b = 6;
    st.Push(a);
    st.Push(b);

    st.Pop();

    ASSERT_NO_THROW(st.Pop());
}

//19
TEST(Stack, compare_pop_x2_from_stack_with_size2__with_1th_el_with_2th_el)
{
    Stack<int> st(2);

    int a = 5;
    int b = 6;
    st.Push(a);
    st.Push(b);

    st.Pop();

    EXPECT_EQ(st.Pop(), 5);
}

//20
TEST(Stack, throw_when_pop_from_stack_isEmpty_with_size10)
{
    Stack<int> st(10);

    ASSERT_ANY_THROW(st.Pop());
}

//21
TEST(Stack, can_pop_from_stack_size10_with_1th_el)
{
    Stack<int> st(10);

    int a = 5;
    st.Push(a);

    ASSERT_NO_THROW(st.Pop());
}

//22
TEST(Stack, compare_pop_from_stack_size10_with_1th_el)
{
    Stack<int> st(10);

    int a = 5;
    st.Push(a);

    EXPECT_EQ(st.Pop(), 5);
}

//23
TEST(Stack, can_pop_from_stack_size10_with_1th_el_and_2th)
{
    Stack<int> st(10);

    int a = 5;
    int b = 6;
    st.Push(a);
    st.Push(b);

    ASSERT_NO_THROW(st.Pop());
}

//24
TEST(Stack, compare_pop_from_stack_size10_with_1th_el_and_2th)
{
    Stack<int> st(10);

    int a = 5;
    int b = 6;
    st.Push(a);
    st.Push(b);

    EXPECT_EQ(st.Pop(), 6);
}

//25
TEST(Stack, can_pop_x2_from_stack_size10_with_1th_el_and_2th)
{
    Stack<int> st(10);

    int a = 5;
    int b = 6;
    st.Push(a);
    st.Push(b);

    st.Pop();

    ASSERT_NO_THROW(st.Pop());
}

//26
TEST(Stack, compare_pop_x2_from_stack_size10_with_1th_el_and_2th)
{
    Stack<int> st(10);

    int a = 5;
    int b = 6;
    st.Push(a);
    st.Push(b);

    st.Pop();

    EXPECT_EQ(st.Pop(), 5);
}

//27
TEST(Stack, can_pop_from_full_stack_size10)
{
    Stack<int> st(10);

    for (int i = 0; i < 10; i++)
    {
        st.Push(i);
    }

    ASSERT_NO_THROW(st.Pop());
}

//28
TEST(Stack, compare_pop_from_full_stack_size10)
{
    Stack<int> st(10);

    for (int i = 0; i < 10; i++)
    {
        st.Push(i);
    }

    EXPECT_EQ(st.Pop(), 9);
}

//29
TEST(Stack, can_push_to_stack_size1_empty)
{
    Stack<int> st(1);

    ASSERT_NO_THROW(st.Push(1));
}

//30
TEST(Stack, compare_push_to_stack_size1_empty)
{
    Stack<int> st(1);

    st.Push(1);

    EXPECT_EQ(st.GetLastEl(), 1);
}

//31
TEST(Stack, can_push_to_stack_size1_full)
{
    Stack<int> st(1);

    st.Push(1);

    ASSERT_NO_THROW(st.Push(2));
}

//32
TEST(Stack, check_size_when_push_to_stack_size1_full)
{
    Stack<int> st(1);

    st.Push(1);
    st.Push(2);

    EXPECT_EQ(st.GetSize(), 2);
}

//33
TEST(Stack, can_push_to_stack_size2_empty)
{
    Stack<int> st(2);

    ASSERT_NO_THROW(st.Push(1));
}

//34
TEST(Stack, can_push_to_stack_size2_with_1th_el_without_2th)
{
    Stack<int> st(2);

    st.Push(1);

    ASSERT_NO_THROW(st.Push(2));
}

//35
TEST(Stack, compare_push_to_stack_size2_with_1th_el_without_2th)
{
    Stack<int> st(1);

    st.Push(1);
    st.Push(2);

    EXPECT_EQ(st.GetLastEl(), 2);
}

//36
TEST(Stack, can_push_to_stack_size2_with_1th_el_with_2th)
{
    Stack<int> st(2);

    st.Push(1);
    st.Push(2);

    ASSERT_NO_THROW(st.Push(3));
}

//37
TEST(Stack, check_size_push_to_stack_size2_with_1th_el_with_2th)
{
    Stack<int> st(2);

    st.Push(1);
    st.Push(2);
    st.Push(3);

   EXPECT_EQ(st.GetSize(), 4);
}

//38
TEST(Stack, check_size_stack_size1_empty)
{
    Stack<int> st(1);

    EXPECT_EQ(st.GetSize(), 1);
}

//39
TEST(Stack, check_size_stack_size1_full)
{
    Stack<int> st(1);

    st.Push(1);

    EXPECT_EQ(st.GetSize(), 1);
}

//40
TEST(Stack, check_size_stack_size2_empty)
{
    Stack<int> st(2);

    EXPECT_EQ(st.GetSize(), 2);
}

//41
TEST(Stack, check_size_stack_size2_with_1th_el_without_2th)
{
    Stack<int> st(2);

    st.Push(1);

    EXPECT_EQ(st.GetSize(), 2);
}

//42
TEST(Stack, check_size_stack_size2_with_1th_el_with_2th)
{
    Stack<int> st(2);

    st.Push(1);
    st.Push(2);

    EXPECT_EQ(st.GetSize(), 2);
}

//43
TEST(Stack, check_head_stack_size1_empty)
{
    Stack<int> st(1);

    EXPECT_EQ(st.GetHead(), -1);
}

//44
TEST(Stack, check_head_stack_size1_full)
{
    Stack<int> st(1);

    st.Push(1);

    EXPECT_EQ(st.GetHead(), 0);
}

//45
TEST(Stack, check_head_stack_size2_empty)
{
    Stack<int> st(2);

    EXPECT_EQ(st.GetHead(), -1);
}

//46
TEST(Stack, check_head_stack_size2_with_1th_el_without_2th)
{
    Stack<int> st(2);

    st.Push(1);

    EXPECT_EQ(st.GetHead(), 0);
}

//47
TEST(Stack, check_head_stack_size2_with_1th_el_with_2th)
{
    Stack<int> st(2);

    st.Push(1);
    st.Push(2);

    EXPECT_EQ(st.GetHead(), 1);
}

//48
TEST(Stack, throw_when_GetLastEl_stack_is_empty_with_size1)
{
    Stack<int> st(1);

    ASSERT_ANY_THROW(st.GetLastEl());
}

//48
TEST(Stack, can_GetLastEl_stack_is_full_with_size1)
{
    Stack<int> st(1);

    st.Push(1);

    ASSERT_NO_THROW(st.GetLastEl());
}

//49
TEST(Stack, head_dont_change_when_GetLastEl_stack_is_full_with_size1)
{
    Stack<int> st(1);

    st.Push(1);
    st.GetLastEl();

   EXPECT_EQ(st.GetHead(), 0);
}

//50
TEST(Stack, compare_GetLastEl_stack_is_full_with_size1)
{
    Stack<int> st(1);

    st.Push(1);

    EXPECT_EQ(st.GetLastEl(), 1);
}

//51
TEST(Stack, throw_when_GetLastEl_stack_is_empty_with_size2)
{
    Stack<int> st(2);

    ASSERT_ANY_THROW(st.GetLastEl());
}

//52
TEST(Stack, can_GetLastEl_stack_with_size2_with_1th_el_without_2th)
{
    Stack<int> st(2);

    st.Push(1);

    ASSERT_NO_THROW(st.GetLastEl());
}

//53
TEST(Stack, dont_change_head_when_GetLastEl_stack_with_size2_with_1th_el_without_2th)
{
    Stack<int> st(2);

    st.Push(1);
    st.GetLastEl();

    EXPECT_EQ(st.GetHead(), 0);
}

//54
TEST(Stack, compare_GetLastEl_stack_with_size2_with_1th_el_without_2th)
{
    Stack<int> st(2);

    st.Push(1);

    EXPECT_EQ(st.GetLastEl(), 1);
}

//55
TEST(Stack, can_GetLastEl_stack_with_size2_with_1th_el_with_2th)
{
    Stack<int> st(2);

    st.Push(1);
    st.Push(2);

    ASSERT_NO_THROW(st.GetLastEl());
}

//56
TEST(Stack, compare_GetLastEl_stack_with_size2_with_1th_el_with_2th)
{
    Stack<int> st(2);

    st.Push(1);
    st.Push(2);

    EXPECT_EQ(st.GetLastEl(), 2);
}

//57
TEST(Stack, dont_change_head_when_GetLastEl_stack_with_size2_with_1th_el_with_2th)
{
    Stack<int> st(2);

    st.Push(1);
    st.Push(2);
    st.GetLastEl();

    EXPECT_EQ(st.GetHead(), 1);
}

//58
TEST(Stack, can_clear_empty_stack_with_size1)
{
    Stack<int> st(1);

    ASSERT_NO_THROW(st.Clear());
}

//59
TEST(Stack, compare_head_after_clear_empty_stack_with_size1)
{
    Stack<int> st(1);

    st.Clear();

    EXPECT_EQ(st.GetHead(), -1);
}

//60
TEST(Stack, compare_head_after_clear_full_stack_with_size1)
{
    Stack<int> st(1);

    st.Push(1);
    st.Clear();

    EXPECT_EQ(st.GetHead(), -1);
}

//61
TEST(Stack, can_clear_empty_stack_with_size2)
{
    Stack<int> st(2);

    ASSERT_NO_THROW(st.Clear());
}

//62
TEST(Stack, compare_head_after_clear_empty_stack_with_size2_with_1th_el_without_2th)
{
    Stack<int> st(2);

    st.Push(1);
    st.Clear();

    EXPECT_EQ(st.GetHead(), -1);
}

//63
TEST(Stack, compare_head_after_clear_empty_stack_with_size2_with_1th_el_with_2th)
{
    Stack<int> st(2);

    st.Push(1);
    st.Push(2);
    st.Clear();

    EXPECT_EQ(st.GetHead(), -1);
}
