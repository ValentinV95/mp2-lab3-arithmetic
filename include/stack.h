// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память
#pragma once
#include <iostream>
template <class ValType>
class Stack
{
private:
	ValType * stack;
	int n;
	int end;


public:
	Stack(int _n = 100);
	~Stack();
	ValType Pop();
	void Push(double elem);
	bool IsEmpty();
	ValType Value();
	int Size();
	void Empty();

};

template <class ValType>
Stack<ValType>::Stack(int _n) {
	if (_n <= 0)
		throw 2;
	else {
		stack = new ValType[_n];
		end = -1;
		n = _n;
	}

}
template <class ValType>
Stack<ValType>::~Stack()
{
	delete[]stack;
	stack = NULL;
	end = -1;
}
template <class ValType>
ValType Stack <ValType>::Pop()
{
	if ((*this).IsEmpty())
		throw ("error");
	else {
		int temp = end;
		end--;

		return stack[temp];
	}
}

template <class ValType>
int Stack <ValType>::Size()
{
	return (end + 1);
}

template <class ValType>
void Stack<ValType>::Push(double elem)
{
	if (end + 1 >= n) {
		ValType *temp;
		temp = new ValType[2 * n];
		for (int i = 0; i < n; i++)
			temp[i] = stack[i];
		delete[]stack;
		stack = temp;

		n = 2 * n;
	}
	end++;
	stack[end] = elem;
}
template <class ValType>
void Stack<ValType>::Empty()
{
	end = -1;
	n = 0;
	delete[]stack;
	stack = NULL;
}

template <class ValType>
bool Stack<ValType>::IsEmpty()
{
	if (end == -1)
		return true;
	else return false;

}


template <class ValType>
ValType Stack <ValType>::Value()
{
	if (IsEmpty())
		throw 1;
	else
		return stack[end];
}