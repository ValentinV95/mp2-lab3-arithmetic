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

template <class T>
class Stack
{
private:

	T* stack;
	int end; //top elem
	int size; //stack size

public:

	Stack(int n) {
		if (n <= 0)
		{
			throw "Wrong length";
		}
		else {
			stack = new T[n];
			size = n;
			end = -1;
		}
	}

	~Stack() {
		delete[] stack;
		stack = 0;
		end = -1;
	}

	bool IsEmpty() {
		if (end == -1) {
			return true;
		}
		else
			return false;
	}

	bool IsFull() 
	{
		if (end == (size - 1))
			return true;
		else
			return false;
	}

	void Push(T& Elem) 
	{
		if (end + 1 < size) {
			end++;
			stack[end] = Elem;
		}
		else {
			T* temp;
			temp = new T[2 * size];
			for (int i = 0; i < size; i++)
				temp[i] = stack[i];
			delete[] stack;
			stack = temp;
			size = 2 * size;
		}
	}

	T Pop() 
	{
		if ((*this).IsEmpty() == true) 
		{
			throw "Stack is empty";
		}
		else {
			int temp = end;
			end--;
			return stack[temp];
		}
	}

	T GetHeadElement() 
	{
		if ((*this).IsEmpty() == true)
		{
			throw "Stack is empty";
		}
		else
		{
			return stack[end];
		}
	}

	int GetCount() 
	{
		return count;
	}

	void Clear() 
	{
		end = -1;
		size = 0;
		delete[] stack;
		stack = NULL;
	}
};