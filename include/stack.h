// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

#ifndef _STACK_H_
#define _STACK_H_
#include <iostream>
using namespace std;
template <typename T>
class TStack
{
	T* data;
	int top, size;
public:
	TStack()
	{
		data = new T[10];
		top = 0;
		size = 10;
	}
	TStack(int x)
	{
		if (x <= 0) throw exception("ERROR");
		data = new T[x];
		top = 0;
		size = x;
	}
	~TStack() { }
	void push(T x)
	{
		if (top == size)
		{
			T* tmp = data;
			data = new T[size * 2];
			for (int i = 0; i < size; ++i) data[i] = tmp[i];
			delete[] tmp;
			size = size * 2;
		}
		data[top] = x;
		top++;
	}
	T pop()
	{
		if (this->isempty()) throw exception("ERROR");
		top--;
		return data[top];
	}
	T show()
	{
		if (this->isempty()) throw exception("ERROR");
		int temp;
		temp = top - 1;
		return data[temp];
	}
	bool isempty() { return top == 0; }
	int number() { return top; }
	void clrst() { top = 0; }
};
#endif _STACK_H_
