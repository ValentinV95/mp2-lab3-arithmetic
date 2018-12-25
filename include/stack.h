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

const int MaxStackSize = 100;

template <typename T>
class TStack
{
	T*pMem; //указатель на массив элементов
	int size; // размер памяти для стека
	int top; // указатель на вершину стека
	int DataCount; // Количество элементов в стеке
public:

	TStack(int _size);
	TStack(const TStack & st); //копирование
	~TStack();
	int GetNextIndex(int index);// Получить следующий индекс
	void Put(const T&val); //Добавление элемента
	T Get(void); // получение элемента	
	void Pop(); // удаление верхнего элемента
	bool IsEmpty(); //Проверка на пустоту
	bool IsFull(); //Проверка на полноту
	void Print(void); //Вывод
};


template <typename T>
TStack<T>::TStack(int _size)
{
	DataCount = 0;
	size = _size;
	top = -1;
	if ((size < 1) || (size > MaxStackSize))
		throw "size";
	pMem = new T[size];
}

template <typename T>
TStack<T>::TStack(const TStack & st) //копирование
{
	DataCount = 0;
	size = st.size;
	pMem = new T[size];
	for (int i = 0; i < size; i++)
	{
		pMem[i] = st.pMem[i];
	}
}

template <typename T>
TStack<T>::~TStack()
{
	delete[] pMem;
}

template <typename T>
int TStack<T>::GetNextIndex(int index)// Получить следующий индекс
{
	int res = index + 1;
	if (res > size)
		throw "error";
	return res;
}

template <typename T>
void TStack<T>::Put(const T&val) //Добавление элемента
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

template <typename T>
T TStack<T>::Get(void)
{
	if (!IsEmpty())
	{
		return pMem[top];
	}
	else
		throw"error";
}
template <typename T>
void TStack<T>::Pop()
{
	if (!IsEmpty())
	{
		DataCount--;
		top--;
	}
	else
		throw"error";
}

template <typename T>
bool TStack<T>::IsEmpty()
{
	if (DataCount == 0)
		return true;
	else
		return false;
}

template <typename T>
bool TStack<T>::IsFull() //Проверка на полноту
{
	if (DataCount == MaxStackSize)
		return true;
	else
		return false;
}

template <typename T>
void TStack<T>::Print(void) //Вывод
{
	for (int i = 0; i < DataCount; i++)
		std::cout << "Stack[" << i << "]= " << pMem[i] << std::endl;
}