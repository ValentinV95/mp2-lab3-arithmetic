// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

#include <vector>
#include <iostream>
using namespace std;
#define DEFAULT_SIZE 10
template <class T> class Stack
{
private:
	T* a;
	int _size;
	int top;
public:
	Stack()
	{
		_size = DEFAULT_SIZE;
		a = new T[_size];
		top = -1;
	}
	void push(T number)
	{
		if (this->is_full())
		{
			T* b = new T[2 * _size];
			_size *= 2;
			for (int i = 0;i<_size;i++)
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
	T top()
	{
		return a[top];
	}
	bool is_empty()
	{
		return top == -1;
	}
	bool is_full()
	{
		return top == (_size - 1);
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

