#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
	T*pMem; //указатель на массив элементов
	int size; // размер памяти для стека
	int top; // указатель на вершину стека
	int DataCount; // Количество элементов в стеке
public:

	TStack(int _size)
	{
		DataCount = 0;
		size = _size;
		top = -1;
		if ((size < 1) || (size > MaxStackSize))
			throw "size";
		pMem = new T[size];
	}
	TStack(const TStack & st) //копирование
	{
		DataCount = 0;
		size = st.size;
		pMem = new T[size];
		for (int i = 0; i < size; i++) {
			pMem[i] = st.pMem[i];
		}
	}
	~TStack()
	{
		delete[] pMem;
	}
	int GetNextIndex(int index)// Получить следующий индекс
	{
		int res = index + 1;
		if (res > size)
			throw "error";
		return res;
	}
	void Put(const T&val) //Добавление элемента
	{
		if (!IsFull())
		{
			top = GetNextIndex(top);
			pMem[top] = val;
			DataCount++;
		}
		else
			throw "error";
	}
	T Get(void) // удаление элемента
	{
		if (!IsEmpty())
		{
			DataCount--;
			return pMem[top--];
		}
		else
			throw"error";
	}
	bool IsEmpty() //Проверка на пустоту
	{
		if (DataCount == 0)
			return true;
		else
			return false;
	}
	bool IsFull() //Проверка на полноту
	{
		if (DataCount == MaxStackSize)
			return true;
		else
			return false;
	}
	void Print(void) //Вывод
	{
		for (int i = 0; i < MemSize; i++)
			cout << "Stack[" << i << "]= " << pMem[i] << endl;
	}
};

#endif