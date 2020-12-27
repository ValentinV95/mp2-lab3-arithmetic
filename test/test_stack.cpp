// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(TStack, push_el)
{
	TStack<int> s;
	ASSERT_NO_THROW(s.push(9));
}

TEST(TStack, pop_el)
{
	TStack<int> s;
	s.push(9);
	ASSERT_NO_THROW(s.pop());
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
