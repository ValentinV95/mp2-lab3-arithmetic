// тесты для стека

#include "stack.h"
#include <gtest.h>
TEST(TStack, can_create_stack_with_positive_length) {
	ASSERT_NO_THROW(TStack<int> st(5));
}
TEST(TStack, can_not_create_stack_with_negative_length) {
	ASSERT_ANY_THROW(TStack<int> st(-5));
}
TEST(TStack, can_not_create_stack_with_too_large_length) {
	ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 1));
}
TEST(TStack, can_return_last_elem_of_stack) {
	TStack<int> a(5);
	for (int i = 0; i < 5; i++) {
		a.Push(i);
	}
	EXPECT_EQ(4, a.Pop());
}
TEST(TStack, can_push_elem_in_stack) {
	TStack<int> a(1);
	ASSERT_NO_THROW(a.Push(10));
}
TEST(TStack, can_pop_elem_of_stack) {
	TStack<int> a(1);
	a.Push(10);
	EXPECT_EQ(10, a.Pop());
}
TEST(TStack, method_pop_delete_elem_of_stack) {
	TStack<int> a(5);
	a.Push(5);
	a.Pop();
	EXPECT_NE(5, a.Pop());
}
TEST(TStack, can_check_stack_for_empty) {
	TStack<int> a(1);
	EXPECT_TRUE(a.IsEmpty());
}
TEST(TStack, can_check_stack_for_full) {
	TStack<int> a(5);
	while (!a.IsFull()) {
		a.Push(5);
	}
	EXPECT_TRUE(a.IsFull());
}
TEST(TStack, can_create_copied_stack) {
	TStack<int> a(5);
	a.Push(5);
	TStack<int> b(a);
	EXPECT_EQ(a, b);
}
TEST(TStack, can_compare_two_stacks) {
	TStack<int> a(5);
	a.Push(5);
	TStack<int> b(a);
	EXPECT_TRUE((a == b));
}
TEST(TStack, two_stacks_are_not_equal) {
	TStack<int> a(5), b(5);
	a.Push(5);
	EXPECT_NE(a, b);
}
TEST(TStack, can_assign_stack) {
	TStack<int> a(1), b(1);
	a.Push(5);
	ASSERT_NO_THROW(b = a);
}
TEST(TStack, assign_operator_change_stack_size) {
	TStack<int> a(5), b(10);
	a = b;
	EXPECT_NE(5, a.Size());
}
TEST(TStack, assign_operator_change_stack_top) {
	TStack<int> a(5), b(10);
	while (!a.IsFull()) {
		a.Push(5);
	}
	b = a;
	EXPECT_NE(-1, b.Top());
}
TEST(TStack, two_different_stacks_have_different_memories) {
	TStack<int> a(2), b(2);
	a = b;
	EXPECT_NE(&a, &b);
}