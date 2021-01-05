// тесты для стека

#include "stack.h"
#include <gtest.h>
TEST(TStack, can_create_stack_with_positive_length)
{
    ASSERT_NO_THROW(TStack<int> st(1));
}

//2
TEST(TStack, throws_when_create_stack_with_negative_length)
{
    ASSERT_ANY_THROW(TStack<int> st(-1));
}

//3
TEST(TStack, throws_when_create_stack_with_length0)
{
    ASSERT_ANY_THROW(TStack<int> st(0));
}

//4
TEST(TStack, when_stack_is_empty_FuncIsEmpty_returnTRUE)
{
    TStack<int> st(10);

    EXPECT_EQ(st.IsEmpty(), true);
}

//5
TEST(TStack, when_stack_isnt_empty_and_isnt_full_FuncIsEmpty_returnFALSE)
{
    TStack<int> st(10);

    int a = 5;
    st.Put(a);

    EXPECT_EQ(st.IsEmpty(), false);
}

//6
TEST(TStack, when_stack_is_full_FuncIsEmpty_returnFALSE)
{
    TStack<int> st(1);

    int a = 5;
    st.Put(a);

    EXPECT_EQ(st.IsEmpty(), false);
}

//7
TEST(TStack, when_stack_is_empty_FuncIsFull_returnFALSE)
{
    TStack<int> st(1);

    EXPECT_EQ(st.IsFull(), false);
}

//8
TEST(TStack, when_stack_isnt_empty_and_isnt_full_FuncIsFull_returnFALSE)
{
    TStack<int> st(10);

    int a = 5;
    st.Put(a);

    EXPECT_EQ(st.IsFull(), false);
}

//9
TEST(TStack, when_stack_is_empty_FuncIsFull_returnTrue)
{
    TStack<int> st(1);

    int a = 5;
    st.Put(a);

    EXPECT_EQ(st.IsFull(), true);
}

//10
TEST(TStack, can_pop_when_stack_with_size1_is_full)
{
    TStack<int> st(1);

    int a = 5;
    st.Put(a);

    ASSERT_NO_THROW(st.Get());
}

//11
TEST(TStack, compare_pop_when_stack_with_size1_is_full)
{
    TStack<int> st(1);

    int a = 5;
    st.Put(a);

    EXPECT_EQ(st.Get(), 5);
}

//12
TEST(TStack, throw_when_pop_from_stack_with_size1_is_empty)
{
    TStack<int> st(1);

    ASSERT_ANY_THROW(st.Get());
}

//13
TEST(TStack, throw_when_pop_from_stack_with_size2_is_empty)
{
    TStack<int> st(2);

    ASSERT_ANY_THROW(st.Get());
}

//14
TEST(TStack, can_pop_from_stack_with_size2__with_1th_el_without_2th_el)
{
    TStack<int> st(2);

    int a = 5;
    st.Put(a);

    ASSERT_NO_THROW(st.Get());
}

//15
TEST(TStack, compare_pop_from_stack_with_size2__with_1th_el_without_2th_el)
{
    TStack<int> st(2);

    int a = 5;
    st.Put(a);

    EXPECT_EQ(st.Get(), 5);
}

//16
TEST(TStack, can_pop_from_stack_with_size2__with_1th_el_with_2th_el)
{
    TStack<int> st(2);

    int a = 5;
    int b = 6;
    st.Put(a);
    st.Put(b);

    ASSERT_NO_THROW(st.Get());
}

//17
TEST(TStack, compare_pop_from_stack_with_size2__with_1th_el_with_2th_el)
{
    TStack<int> st(2);

    int a = 5;
    int b = 6;
    st.Put(a);
    st.Put(b);

    EXPECT_EQ(st.Get(), 6);
}

//18
TEST(TStack, can_pop_x2_from_stack_with_size2__with_1th_el_with_2th_el)
{
    TStack<int> st(2);

    int a = 5;
    int b = 6;
    st.Put(a);
    st.Put(b);

    st.Get();

    ASSERT_NO_THROW(st.Get());
}

//19
TEST(TStack, compare_pop_x2_from_stack_with_size2__with_1th_el_with_2th_el)
{
    TStack<int> st(2);

    int a = 5;
    int b = 6;
    st.Put(a);
    st.Put(b);

    st.Get();

    EXPECT_EQ(st.Get(), 5);
}

//20
TEST(TStack, throw_when_pop_from_stack_isEmpty_with_size10)
{
    TStack<int> st(10);

    ASSERT_ANY_THROW(st.Get());
}

//21
TEST(TStack, can_pop_from_stack_size10_with_1th_el)
{
    TStack<int> st(10);

    int a = 5;
    st.Put(a);

    ASSERT_NO_THROW(st.Get());
}

//22
TEST(TStack, compare_pop_from_stack_size10_with_1th_el)
{
    TStack<int> st(10);

    int a = 5;
    st.Put(a);

    EXPECT_EQ(st.Get(), 5);
}

//23
TEST(TStack, can_pop_from_stack_size10_with_1th_el_and_2th)
{
    TStack<int> st(10);

    int a = 5;
    int b = 6;
    st.Put(a);
    st.Put(b);

    ASSERT_NO_THROW(st.Get());
}

//24
TEST(TStack, compare_pop_from_stack_size10_with_1th_el_and_2th)
{
    TStack<int> st(10);

    int a = 5;
    int b = 6;
    st.Put(a);
    st.Put(b);

    EXPECT_EQ(st.Get(), 6);
}

//25
TEST(TStack, can_pop_x2_from_stack_size10_with_1th_el_and_2th)
{
    TStack<int> st(10);

    int a = 5;
    int b = 6;
    st.Put(a);
    st.Put(b);

    st.Get();

    ASSERT_NO_THROW(st.Get());
}

//26
TEST(TStack, compare_pop_x2_from_stack_size10_with_1th_el_and_2th)
{
    TStack<int> st(10);

    int a = 5;
    int b = 6;
    st.Put(a);
    st.Put(b);

    st.Get();

    EXPECT_EQ(st.Get(), 5);
}

//27
TEST(TStack, can_pop_from_full_stack_size10)
{
    TStack<int> st(10);

    for (int i = 0; i < 10; i++)
    {
        st.Put(i);
    }

    ASSERT_NO_THROW(st.Get());
}

//28
TEST(TStack, compare_pop_from_full_stack_size10)
{
    TStack<int> st(10);

    for (int i = 0; i < 10; i++)
    {
        st.Put(i);
    }

    EXPECT_EQ(st.Get(), 9);
}

//29
TEST(TStack, can_push_to_stack_size1_empty)
{
    TStack<int> st(1);

    ASSERT_NO_THROW(st.Put(1));
}

//30
TEST(TStack, check_size_when_push_to_stack_size1_full)
{
    TStack<int> st(2);

    st.Put(1);
    st.Put(2);

    EXPECT_EQ(st.Count(), 2);
}

//31
TEST(TStack, can_push_to_stack_size2_empty)
{
    TStack<int> st(2);

    ASSERT_NO_THROW(st.Put(1));
}

//32
TEST(TStack, can_push_to_stack_size2_with_1th_el_without_2th)
{
    TStack<int> st(2);

    st.Put(1);

    ASSERT_NO_THROW(st.Put(2));
}

//33
TEST(TStack, can_push_to_stack_size2_with_1th_el_with_2th)
{
    TStack<int> st(2);

    st.Put(1);
    st.Put(2);

    ASSERT_NO_THROW(st.Put(3));
}
//34
TEST(TStack, can_clear_empty_stack_with_size1)
{
    TStack<int> st(1);

    ASSERT_NO_THROW(st.Clear());
}

//35
TEST(TStack, can_clear_empty_stack_with_size2)
{
    TStack<int> st(2);

    ASSERT_NO_THROW(st.Clear());
}

