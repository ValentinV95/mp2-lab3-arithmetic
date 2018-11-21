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

template <class T>
class TStack
{
	T *pMem;
	int size;
	int top;
	int dataCount;
public:
	TStack(int _size)// конструктор
	{
		dataCount = 0;
		size = _size;
		top = -1;
		if ((size < 1) || (size > MaxStackSize))
		{
			throw "wrong size of the stack";
		}
		pMem = new T[size];
	}
	~TStack()// деструктор
	{
		delete[] pMem;
	}
	TStack(const TStack &stack)// конструктор копирования
	{
		pMem = new T[stack.size];
		size = stack.size;
		top = stack.top;
		dataCount = stack.dataCount;
		for (int i = 0; i < stack.size; i++)
		{
			pMem[i] = stack.pMem[i];
		}
	}
	TStack& operator=(const TStack &stack)// оператор присваивания
	{
		this->size = stack.size;
		this->pMem = new T[size];
		for (int i = 0; i < size; i++)
		{
			this->pMem[i] = stack.pMem[i];
		}
		this->top = stack.top;
		this->dataCount = stack.dataCount;
		return *this;
	}
	int GetNextIndex()// получить следующий индекс 
	{
		return dataCount;
	}
	bool IsEmpty()// проверка на пустоту стэка
	{
		if (dataCount == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool IsFull()//проверка на полноту стэка
	{
		if (dataCount == MaxStackSize)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void Put(const T &elem)// добавить значение
	{
		if (!IsFull())
		{
			if (dataCount >= size)
			{
				dataCount++;
				size = dataCount;
				top = (dataCount - 1);
				T *pMem1;
				pMem1 = new T[size];
				for (int i = 0; i < dataCount - 1; i++)
				{
					pMem1[i] = pMem[i];
				}
				pMem = pMem1;
				pMem[top] = elem;
			}
			else
			{
				pMem[dataCount] = elem;
				top = (dataCount);
				dataCount++;
			}
		}
		else
		{
			throw "the stack is full";
		}
	}
	T Get()// извлечь значение 
	{
		if (!IsEmpty())
		{
			dataCount--;
			return pMem[top--];
		}
		else
		{
			throw "the stack is empty";
		}
	}
};
#endif