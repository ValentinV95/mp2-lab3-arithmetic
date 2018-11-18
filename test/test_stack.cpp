// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(Stack, create_stack)
{
	ASSERT_NO_THROW(Stack<int> s(2));
}

TEST(Stack, stack_with_negative_length)
{
	ASSERT_ANY_THROW(Stack<int> s(-1));
}

TEST(Stack, get_size_of_stack)
{
	Stack<int> s;
	EXPECT_EQ(0, s.size_stack());
	s.push(1);
	s.push(2);
	EXPECT_EQ(2, s.size_stack());
}

TEST(Stack, get_size_of_stack_1)
{
	Stack<int> s;
	s.push(1);
	s.push(2);
	s.pop();
	EXPECT_EQ(1, s.size_stack());
}

TEST(Stack, get_element)
{
	Stack<int> s;
	s.push(1);
	s.push(2);
	EXPECT_EQ(s.front(), 2);
}

TEST(Stack, get_element_1)
{
	Stack<int> s;
	s.push(-1);
	EXPECT_EQ(s.front(), -1);
}

TEST(Stack, get_element_when_stack_is_empty)
{
	Stack<int>s(1);
	s.push(1);
	s.pop();
	ASSERT_ANY_THROW(s.front());
}

TEST(Stack, push_element)
{
	Stack<int> s(2);
	s.push(1);
	EXPECT_EQ(s.size_stack(), 1);
}

TEST(TStack, check_stack_is_empty)
{
	Stack<int>s;
	EXPECT_EQ(s.IsEmpty(), true);
	s.push(1);
	EXPECT_EQ(s.IsEmpty(), false);
	s.pop();
	EXPECT_EQ(s.IsEmpty(), true);
}


TEST(Stack, delete_all_elements)
{
	Stack<int> s(2);
	s.push(1);
	s.push(2);
	s.clear();
	EXPECT_EQ(s.IsEmpty(), true);
}

TEST(Stack, delete_elemtts)
{
	Stack<int> s(2);
	s.clear();
	EXPECT_EQ(s.IsEmpty(), true);
}


TEST(TStack, pop_element_when_stack_is_empty)
{
	Stack<int> s(2);
	s.push(1);
	s.pop();
	ASSERT_ANY_THROW(s.pop());
}