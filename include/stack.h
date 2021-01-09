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
template <class T>
class Stack
{
	int size, max_size;
	T* mas;
public:
	Stack(int Max_size = 10)
	{
		if (Max_size <= 0)
		{
			throw Max_size;
		}
		max_size = Max_size;
		mas = new T[max_size];
		for (int i = 0; i < max_size; i++)
		{
			mas[i] = 0;
		}
		size = 0;
	}

	~Stack()
	{
		size = 0;
		delete[] mas;
	}

	Stack(const Stack <T>& m)
	{
		max_size = m.max_size;
		mas = new T[max_size];
		size = m.size;
		for (int i = 0; i < size; i++)
		{
			mas[i] = m.mas[i];
		}
	}

	Stack& operator=(const Stack <T>& m)
	{
		if (max_size != m.max_size)
		{
			delete[] mas;
			max_size = m.max_size;
			mas = new T[max_size];
		}
		size = m.size;
		for (int i = 0; i < size; i++)
		{
			mas[i] = m.mas[i];
		}
		return (*this);
	}

	bool operator == (const Stack<T>& s)
	{
		//if (this != &s)
		if (max_size != s.max_size || size != s.size)
		{
			return false;
		}
		for (int i = 0; i < size; i++)
		{
			if (mas[i] != s.mas[i])
			{
				return false;
			}
		}

		return true;
	}

	bool operator != (const Stack<T>& s)
	{
		return !(*this == s);
	}

	bool Empty()
	{
		if (size == 0)
			return true;
		return false;
	}

	bool Full()
	{
		if (size == max_size)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Push(T a)
	{
		if (Full() == true)
		{
			throw "Stack is full";
		}
		mas[size] = a;
		size++;
	}

	T Pop()
	{
		if (Empty())
		{
			throw "Stack is empty";
		}
		size--;
		return mas[size];
	}

	T Top()
	{
		if (Empty())
		{
			throw "Stack is empty";
		}
		return mas[size - 1];
	}
	void Clear()
	{
		size = 0;
	}
	int Size()
	{
		return size;
	}
};