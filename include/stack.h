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
#include <cstdlib>

template <class T>
class TStack
{
private:

	int size; 
	int head; 
	int count; 
	T* data;

public:

	TStack(int size = 10) 
	{
		if (size <= 0)
		{
			throw "negative or zero size";
		}
		else
		{
			data = new T[size];
			this->size = size;
			count = 0;
			head = -1;
		}
	}

	~TStack() 
	{
		delete[] data;
	}

	bool IsEmpty() 
	{
		if (head == -1)
			return true;
		else
			return false;
	}

	bool IsFull() 
	{
		if (head == (size - 1))
			return true;
		else
			return false;
	}

	void Push(T& Elem) 
	{
		if (IsFull())
		{
			data = (T*)realloc(data, (size + 1) * sizeof(T));
		}
		data[++head] = Elem;
		count++;
	}

	T Pop() 
	{
		if (IsEmpty())
		{
			throw "Can't pop out of empty stack";
		}
		else
		{
			T result = data[head--];
			count--;
			return result;
		}
	}

	T GetHeadElement() 
	{
		if (IsEmpty())
		{
			throw "stack is empty";
		}
		else
		{
			return data[head];
		}
	}

	int GetCount() 
	{
		return count;
	}

	void Clear() 
	{
		head = -1;
		delete[] data;
		data = new T[size];
	}
};