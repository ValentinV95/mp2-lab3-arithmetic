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
const int MaxStackSize = 10; // Максимальный размер памяти для стека

template <class ValType>
class Stack
{
private:
	ValType * stack;
	int end;
	int n;
public:
	Stack(int n1 = MaxStackSize);
	~Stack();
	ValType pop();// - извлечение элемента
	void push(ValType val);// - вставка элемента
	bool IsEmpty();// - проверка на пустоту
	void Clean();// - очистка стека
	ValType Front();// - просмотр верхнего элемента (без удаления)
	int Size();// - получение количества элементов в стеке
};

template <class ValType>
Stack<ValType>::Stack(int n1) {
	if (n1 <= 0)
	{
		throw "Wrong length";
	}
	else {
		stack = new ValType[n1];
		n = n1;
		end = -1;
	}
}

template <class ValType>
Stack<ValType>::~Stack() {
	delete[] stack;
	stack = 0;
	end = -1;
}

template <class Valtype>
Valtype Stack<Valtype>::pop() {
	if ((*this).IsEmpty() == true) {
		throw "Stack is empty";
	}
	else {
		int temp = end;
		end--;
		return stack[temp];
	}
}

template <class ValType>
void Stack<ValType>::push(ValType val) {
	if (end + 1 < n) {
		end++;
		stack[end] = val;
	}
	else {
		ValType *temp;
		temp = new ValType[2 * n];
		for (int i = 0; i < n; i++)
			temp[i] = stack[i];
		delete[] stack;
		stack = temp;
		n = 2 * n;
	}
}

template <class Valtype>
bool Stack<Valtype>::IsEmpty() {
	if (end == -1) {
		return true;
	}
	else
		return false;
}

template <class Valtype>
void Stack<Valtype>::Clean() {
	end = -1;
	n = 0;
	delete[] stack;
	stack = NULL;
}

template <class Valtype>
Valtype Stack<Valtype>::Front() {
	if (IsEmpty() == true)
		throw "Stack is empty";
	else
		return stack[end];
}

template <class ValType>
int Stack<ValType>::Size() {
	return (end + 1);
}
