#ifndef stack_h
#define stack_h

#include "iostream"
#include "vector"

using namespace std;

template <class val>
class Stack
{
private:
	vector <val> p;
	int Size;
	int top;
	bool IsFull();
public:
	Stack(int n = 10);
	~Stack() {};
	bool IsEmpty();
	val front();
	int GetSize() {return Size;}
	void pop();
	void push(val s);
};

template <class val>
Stack<val>::Stack(int n)
{
	Size = n;
	top = -1;
	p.resize(n);
}
template <class val>
bool Stack<val>::IsEmpty()
{
	if(top == -1)
	{
		return true;
	}
	return false;
}

template <class val>
bool Stack<val>::IsFull()
{
	if (top == Size - 1)
	{
		return true;
	}
	return false;

}

template <class val>
void Stack<val>::pop()
{
	if(!IsEmpty())
	{
		top--;
	}
	else
	{
		throw("Stack is empty");
	}
}

template <class val>
void Stack<val>::push(val v)
{
	if(IsFull())
	{
		Size = 2 * Size;
		p.resize(Size);
	}
	p[++top] = v;
}

template <class val>
val Stack<val>::front()
{
	if(IsEmpty())
	{
		throw("Stack is empty");
	}
	return p[top];
}
#endif 