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
		if (x>0)
		{
		  data = new T[x];
		  top = 0;
		  size = x;
		}
		else
			throw ("ERROR");
	}
	~TStack() 
	{

	}
	void push(T x) 
	{
		if (top == size) 
		{
			T* tmp = new T[size];
			for (int i = 0; i < size; ++i) 
			{
				tmp[i] = data[i];
			}
			delete[] data;
			data = new T[size * 2];
			for (int i = 0; i < size; ++i) 
			{
				data[i] = tmp[i];
			}
			delete []tmp;
			size = size * 2;
		}
		data[top] = x;
		top++;
	}
	T pop() 
	{
		if (!(this->isempty())) 
		{
			top--;
			return data[top];
		}
		else 
		{
			throw ("ERROR");;
		}
	}
	T show() 
	{
		if (!(this->isempty())) 
		{
			int temp;
			temp = top - 1;
			return data[temp];
		}
		else 
		{
			throw (0);
		}
	}
	bool isempty() 
	{
		if (top == 0) 
		{
			return true;
		}
		return false;
	}
	int number() 
	{
		return top;
	}
	void clrst() 
	{
		top = 0;
	}
};
#endif _STACK_H_
