#pragma once
#ifndef __STACK_H__ 
#define __STACK_H__ 
#include <iostream>

using namespace std;

const int MAX_STACK_SIZE = 100;

template <class TType>
class Stack
{
	TType *Mass;
	int Top;
	int Size;

public:
	Stack();
	Stack(int Size);	
	void Push(TType val);
	TType Pop();			
	TType CheckTop();		
	TType GetSize();	
	void ClearStack();		
	bool IsEmpty();			
	bool IsFull();			
	void NewLen();
	TType CheckTopEl();
	~Stack();
};


template<class TType>
Stack<TType>::Stack()
{
	Size = 10;
	Top = -1;
}

template<class TType>
Stack<TType>::Stack(int _Size)
{
	if (_Size <=0)
		throw "size must be positive";
	if (_Size > MAX_STACK_SIZE)
		throw "too large size";
	Size = _Size;
	Mass = new TType[Size];
	Top = -1;
}

template<class TType>
void Stack<TType>::Push(TType val)
{
	if (!IsFull())
	{
		Mass[++Top] = val;
	}
	else 
	{
		NewLen();
		Mass[++Top] = val;
	}
}

template<class TType>
TType Stack<TType>::Pop()
{
	if (!IsEmpty())
	{
		return Mass[Top--];
	}
	else throw "Stack is empty";
}

template<class TType>
bool Stack<TType>::IsEmpty()
{
	if (Top == -1)
		return true;
	else return false;
}

template<class TType>
bool Stack<TType>::IsFull()
{
	if (Top == Size - 1)
		return true;
	else return false;
}

template<class TType>
TType Stack<TType>::CheckTopEl()
{
	if(!IsEmpty())
		return Mass[Top];
	else throw"stack is empty";

}

template<class TType>
void Stack<TType>::NewLen()
{
	TType*_Mass = new TType[Size * 2];
	for (int i = 0; i < Size; i++)
		_Mass[i] = Mass[i];
	delete[]Mass;
	Size *= 2;
	Mass=_Mass;
}

template<class TType>
TType Stack<TType>::CheckTop()
{
	return Top;
}

template<class TType>
TType Stack<TType>::GetSize()
{
	return Size;
}

template<class TType>
void Stack<TType>::ClearStack()
{
	Top = -1;
}

template<class TType>
Stack<TType>::~Stack()
{
	delete[]Mass;
}

#endif