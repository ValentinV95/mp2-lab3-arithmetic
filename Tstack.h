#pragma once
#include "Tstack.cpp"
template <typename T>
class TStack 
{
	T* data;
	int top, size;
public:
	TStack();
	TStack(int x);
	~TStack();
	void push(T x);
	T show();
	T pop();
	bool isempty();
	bool isempty();
	void clrst();
};
	
