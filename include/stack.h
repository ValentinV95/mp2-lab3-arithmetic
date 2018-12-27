#pragma once
#include <iostream>
const int maxsize = 10; // Ìàêñèìàëüíûé ðàçìåð ïàìÿòè äëÿ ñòåêà

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
	T pop();// - èçâëå÷åíèå ýëåìåíòà
	void push(T val);// - âñòàâêà ýëåìåíòà
	bool IsEmpty();// - ïðîâåðêà íà ïóñòîòó
	void Clean();// - î÷èñòêà ñòåêà
	T Front();// - ïðîñìîòð âåðõíåãî ýëåìåíòà (áåç óäàëåíèÿ)
	int Size();// - ïîëó÷åíèå êîëè÷åñòâà ýëåìåíòîâ â ñòåêå
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