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

const int n1 = 10;

template <class ValType>
class Stack
{
public:
	Stack(int n = n1);
	~Stack();
	ValType pop();
	void push(ValType val);
	bool IsEmpty();
	void Empty();
	ValType Value();
	int Size();
private:
	ValType * stack;
	int end;
	int n;
};

template <class ValType>
Stack<ValType>::Stack(int n1) {
	if (n1 <= 0)
	{
		throw "Incorrect length";
	}
	else {
		n = n1;
		stack = new ValType[n];
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
	if ((*this).IsEmpty())
		throw "Empty stack";
	else {
		int temp = end;
		end--;
		return stack[temp];
	}
}

template <class ValType>
int Stack<ValType>::Size() {
	return (end + 1);
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
void Stack<Valtype>::Empty() {
	end = -1;
	n = 0;
	delete[] stack;
	stack = nullptr;
}

template <class Valtype>
Valtype Stack<Valtype>::Value() {
	if (IsEmpty()) 
		throw "Stack is Empty";
	else return stack[end];
}

