// объявление и реализация шаблонного стека
#pragma once
#include <iostream>
const int maxsize = 10; // Максимальный размер памяти для стека

template <class T>
class Stack
{
private:
	T * stack;
	int end;
	int tmp;
public:
	Stack(int n1 = maxsize);
	~Stack();
	T pop();// - извлечение элемента
	void push(T val);// - вставка элемента
	bool IsEmpty();// - проверка на пустоту
	void Clean();// - очистка стека
	T Front();// - просмотр верхнего элемента (без удаления)
	int Size();// - получение количества элементов в стеке
};

template <class T>
Stack<T>::Stack(int n1) {
	if (n1 <= 0)
	{
		throw "Wrong length";
	}
	else {
		stack = new T[n1];
		tmp = n1;
		end = -1;
	}
}

template <class T>
Stack<T>::~Stack() {
	delete[] stack;
	stack = 0;
	end = -1;
}

template <class T>
T Stack<T>::pop() {
	if ((*this).IsEmpty() == true) {
		throw "Stack is empty";
	}
	else {
		int temp = end;
		end--;
		return stack[temp];
	}
}

template <class T>
void Stack<T>::push(T val) {
	if (end + 1 < tmp) {
		end++;
		stack[end] = val;
	}
	else {
		T *temp;
		temp = new T[2 * tmp];
		for (int i = 0; i < tmp; i++)
			temp[i] = stack[i];
		delete[] stack;
		stack = temp;
		tmp = 2 * tmp;
	}
}

template <class T>
bool Stack<T>::IsEmpty() {
	if (end == -1) {
		return true;
	}
	else
		return false;
}

template <class T>
void Stack<T>::Clean() {
	end = -1;
	tmp = 0;
	delete[] stack;
	stack = NULL;
}

template <class T>
T Stack<T>::Front() {
	if (IsEmpty() == true)
		throw "Stack is empty";
	else
		return stack[end];
}

template <class T>
int Stack<T>::Size() {
	return (end + 1);
}
