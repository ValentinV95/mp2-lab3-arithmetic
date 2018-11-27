#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create_stack)
{
	ASSERT_NO_THROW(Stack<int> s);
}
TEST(Stack, cant_create_stack_with_null_size)
{
	ASSERT_ANY_THROW(Stack<int> s(0));
}
TEST(Stack, can_create_copied_stack)
{
	Stack<int> s;
	ASSERT_NO_THROW(Stack<int> s1);
}
TEST(Stack, can_push_element_in_stack)
{
	Stack<int> s;
	ASSERT_NO_THROW(s.push(5));
}
TEST(Stack, can_push_element_in_full_stack)
{
	Stack<int> s(2);
	const int expVal = -1;
	s.push(8); s.push(2);
	s.push(expVal);
	EXPECT_EQ(expVal, s.spop());
}
TEST(Stack, can_check_on_emptiness_for_empty_stack)
{
	Stack<int> s;
	bool expVal = true;
	EXPECT_EQ(expVal, s.empty());
}
TEST(Stack, can_check_on_emptiness_for_not_empty_stack)
{
	Stack<int> s;
	bool expVal = false;
	s.push(3);
	EXPECT_EQ(expVal, s.empty());
}
TEST(Stack, can_get_top_element_without_deletion)
{
	Stack<int> s(1);
	const int expVal = 10;
	bool expEmp = false;
	s.push(expVal);
	EXPECT_EQ(expVal, s.spop());
	EXPECT_EQ(expEmp, s.empty());
}
TEST(Stack, can_pop_element)
{
	Stack<int> s;
	const int expVal = -9;
	bool expEmp = true;
	s.push(expVal);
	EXPECT_EQ(expVal, s.pop());
	EXPECT_EQ(expEmp, s.empty());
}
TEST(Stack, cant_pop_element_from_empty_stack)
{
	Stack<int> s;
	ASSERT_ANY_THROW(s.pop());
}