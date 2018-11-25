

#include "stack.h"
#include <gtest.h>

TEST(Stack, can_resize_if)
{
	Stack <int> s;
	for (int i = 0; i < 15; i++)
		s.Set(0);
	int a[15];
	int b[15] = { 0 };
	for (int i = 14;i >= 0;i--)
		a[i] = s.Get();
	EXPECT_EQ(a[14], b[14]);

}
TEST(Stack, can_top)
{
	Stack <int> s(1);
	
		s.Set(0);
	
	EXPECT_EQ(s.Top(), 0);

}
TEST(Stack, can_get_when_empty)
{
	Stack <int> s(10);
	ASSERT_ANY_THROW(s.Get());
}