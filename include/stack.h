// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

#ifndef _STACK_
#define _STACK_

#include <stdio.h>
#include <iostream>
using namespace std;
template <typename T>
class TStack
{
private :
	T *mas;
	int size;
	int quant;
public:
	TStack(){size = 0; quant = 0; mas = new T[1];}
	TStack(int s)
	{ 
		if( s > 0)
		{
		quant = 0;
		size = s;
		mas = new T [s]; 
		}
		else throw "Negative length!";
	}

	int GetSize() {return size;}
	bool IsEmpty()
	{
		if (quant == 0)
			return 1;
		return 0;
	}

	bool IsFull ()
	{
		if ( quant == size )
		{
			return 1;
		}
		return 0;
	}

	void Push(T El)
	{
		if (IsFull ())
		{
			T *tmp  = new T [size+10];
			for (int i = 0; i < quant; i++)
			{
				tmp [i] = mas[i];
			}

			delete []mas;
			mas=tmp;
			size = size + 10;
		}
		mas[quant] = El;
		quant ++;
	}

	T pop()
	{
		if (IsEmpty() == 0)
		{
			T tmp = mas[quant-1];
			quant --;
			return tmp;
		}
		else throw ( " empty");
	}

	void Print()
	{
		for (int i = 0; i < quant; i++)
		{
			cout << mas[i] << " ";
		}
		cout << endl;
	}
};

#endif _STACK_
