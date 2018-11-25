// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

 
#include <stdlib.h>
#ifndef STACK_H
#define STACK_H
template <typename T> class Stack
{
private:
	int n;
	T *q;
	int pos;
public:
	Stack(int nk=10)
	{
		n = nk;
		q = new T[n];
		pos = 0;
	}
	~Stack()
	{
		pos = 0;
		delete[] q;
	}
	int Get_pos() { return pos; }
	void Resize_IF()
	{
		if (pos == n)
		{
			T* tmp;
			tmp = new T[1.5*n];
			for (int i = n - 1;i >= 0;i--)
				tmp[i] = Get();
			delete[] q;
			q = tmp; 
			pos = n;
			n = 1.5*n;
		}
	}
	bool IsEmpty()
	{
		if (!(pos))
			return(true);
		else
			return(false);
	}
	void Set(T k)
	{
		Resize_IF();
		q[pos++] = k;
	}
	T Get()
	{
		if (!(IsEmpty()))
		{
			pos--;
			return(q[pos]);
		}
		else
			throw "Stack is empty";
	}
	T Top()
	{
		return(q[pos-1]);
	}
};
#endif STACK_H