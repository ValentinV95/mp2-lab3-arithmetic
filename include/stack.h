#ifndef _STACK_H_
#define _STACK_H_

#include <vector>

const int size0 = 50;

template <class ValType>
class TStack
{
private:
	int top;
	int size;
	std::vector<ValType> v;
public:
	TStack(int n = size0);
	virtual ~TStack() {};
	bool isFull() const;                 // Проверка на полноту
	bool isEmpty() const;                // Проверка на пустоту
	void push(ValType elem);             // Вставка элемента
	int CurrentSize() const;             // Получение количества элементов в стеке
	ValType front() const;               // Просмотр верхнего элемента (без удаления)
	ValType pop();                       // Извлечение элемента
	void AllClear();                     // Очистка стека
};

template <class ValType>
TStack<ValType>::TStack(int n)
{
	if (n <= 0)
	{
		throw "Incorrect length";
	}
	size = n;
	v.resize(size);
	top = -1;
}

template <class ValType>
int TStack<ValType>::CurrentSize() const
{
	return top + 1;
}

template <class ValType>
ValType TStack<ValType>::front() const
{
	if (isEmpty())
	{
		throw "Stack is empty";
	}
	return v[top];
}

template <class ValType>
bool TStack<ValType>::isEmpty() const
{
	return top == -1;
}

template <class ValType>
bool TStack<ValType>::isFull() const
{
	return top == size - 1;
}

template <class ValType>
void TStack<ValType>::push(ValType elem)
{
	if (isFull())
	{
		v.resize(size * 2);
		size = size * 2;
	}
	v[++top] = elem;
}

template <class ValType>
ValType TStack<ValType>::pop()
{
	if (isEmpty())
	{
		throw "Stack is empty";
	}
	return v[top--];
}

template <class ValType>
void TStack<ValType>::AllClear()
{
	size = size0;
	top = -1;
	v.clear();
	v.resize(size);
}

#endif