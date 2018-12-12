// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память
#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;


//Первый вошел - последний вышел
template <class T>
class TStack
{
	T *pMem;
	int size;
	int top;
public:
	TStack(int _size = MaxStackSize)
	{
		if ((_size < 1) || (_size > MaxStackSize))
			throw "data is not correct";
		size = _size;
		top = -1;
		pMem = new T[size];
	}
	~TStack()
	{
		delete[] pMem;
	}
	bool IsEmpty()
	{
		return top == -1;
	}
	bool IsFull()
	{
		return top == size - 1;
	}
	void Clear()
	{
		top = -1;
	}
	void Erase()
	{
		if (!IsEmpty())
			top--;
	}
	T Pop()
	{
		return pMem[top--];
	}
	T PopWithoutDelete()
	{
		return pMem[top];
	}
	void Push(T v)
	{
		pMem[++top] = v;
	}
	int Length() 
	{
		return top + 1;
	}
};

#endif