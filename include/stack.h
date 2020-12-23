// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память
#define DEFAULT_SIZE 10
#define RESIZE_CONST 2
#include <vector>
#include <iostream>
using namespace std;
template <class T> class TStack
{
private:
	T* a;
	int _size;
	int top;
	bool is_full()
	{
		return top == (_size - 1);
	}
public:
public:
	TStack(int size = DEFAULT_SIZE)
	{
		_size = size;
		a = new T[_size];
		top = -1;
	}
	~TStack()
	{
		delete[] a;
	}
	void push(T number)
	{
		if (this->is_full())
		{
			T* b = new T[RESIZE_CONST * _size];
			_size *= RESIZE_CONST;
			for (int i = 0; i < _size; i++)
			{
				b[i] = a[i];
			}
			delete[] a;
			a = b;

		}
		a[++top] = number;
	}
	T pop()
	{
		if (this->is_empty())
		{
			throw "Stack is empty";
		}
		else
		{
			return a[top--];
		}
	}
	T front()
	{
		if (top != -1)
		{
			return a[top];
		}
		else
		{
			throw "Stack is empty";
		}
	}
	bool is_empty()
	{
		return top == -1;
	}
	int size()
	{
		return top + 1;
	}
	void clear()
	{
		top = -1;
		delete[] a;
		a = new T[DEFAULT_SIZE];
	}
};
