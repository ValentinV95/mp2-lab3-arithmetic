// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

#include <iostream>
#include <cstdlib>

template <class T>
class TStack
{
private:
	int size; // размер стэка
	int head; // верхний элемент стэка
	int count; // количество элементов в стэке
	T* data; 
public:

	TStack(int size = 10) // - конструктор
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

	bool IsEmpty() // - проверка на пустоту
	{
		if (head == -1)
			return true;
		else
			return false;
	}
	
	bool IsFull() // - проверка на полноту
	{
		if (head == (size-1))
			return true;
		else
			return false;
	}

	void Push(T& Elem) // - вставка элемента
	{
		if (IsFull())
		{
			data =  (T*) realloc(data, (size+1) * sizeof(T));
		}
		data[++head] = Elem;
		count++;
	}

	T Pop() // - извлечение элемента
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

	T GetHeadElement() // - просмотр верхнего элемента (без удаления)
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

	int GetCount() // - получение количества элементов в стеке
	{
		return count;
	}

	void Clear() // - очистка стека
	{
		head = -1;
		delete[] data;
		data = new T[size];
	}

	~TStack() // - деструктор
	{
		delete[] data;
	}
};