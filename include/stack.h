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
	int end;
	int tmp;

public:

	Stack(int n1 = 10) {
		if (n1 <= 0)
		{
			throw "Wrong length";
		}
		else {
			stack = new T[n1];
			tmp = n1;
			end = -1;
		}
	};

	~Stack() {
		delete[] stack;
		stack = 0;
		end = -1;
	};

	T pop() {
		if ((*this).IsEmpty() == true) {
			throw "Stack is empty";
		}
		else {
			int temp = end;
			end--;
			return stack[temp];
		}
	};

	void push(T val) {
		if (end + 1 < tmp) {
			end++;
			stack[end] = val;
		}
		else {
			T* temp;
			temp = new T[2 * tmp];
			for (int i = 0; i < tmp; i++)
				temp[i] = stack[i];
			delete[] stack;
			stack = temp;
			tmp = 2 * tmp;
		}
	};

	bool IsEmpty() {
		if (end == -1) {
			return true;
		}
		else
			return false;
	};

	void Clean() {
		end = -1;
		tmp = 0;
		delete[] stack;
		stack = NULL;
	};

	T Front() {
		if (IsEmpty() == true)
			throw "Stack is empty";
		else
			return stack[end];
	};

	int Size() {
		return (end + 1);
	};
};

