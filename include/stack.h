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

#define N 10

template< class ValType>
class TStack
{
	int top;
	int size;
	ValType *stk;

	void Realoc();

public:

	TStack();  
	TStack(int s);
	~TStack();
	void Push(ValType elem);
	ValType Pop();
	ValType CheckTop();
	bool IsEmpty();
	int GetSize();
	void Clean();
};

template< class ValType>
TStack<ValType>::TStack()
{
	top = -1;
	size = N;
	stk = new ValType[size];
}

template< class ValType>
TStack<ValType>::TStack(int s)
{
	if (s <= 0)
		throw "Error: negative_size";

	top = -1;
	size = s;
	stk = new ValType[size];
}

template< class ValType>
TStack<ValType>::~TStack()
{
	delete[]stk;
}

template< class ValType>
void TStack<ValType>::Push(ValType elem)
{
	if (size == top + 1)
		Realoc();

	stk[top + 1] = elem;
	top++;
}

template< class ValType>
ValType TStack<ValType>::Pop()
{
	if (IsEmpty())
		throw "Error: stack_is_empty";

	return(stk[top--]);
}

template< class ValType>
ValType TStack<ValType>::CheckTop()
{
	if (IsEmpty())
		throw "Error: stack_is_empty";

	return(stk[top]);
}

template< class ValType>
void TStack<ValType>::Realoc()
{
	ValType *point = new ValType[size * 2];

	for (int i = 0; i < size; i++)
		point[i] = stk[i];

	delete[]stk;
	size = size * 2;
	stk = point;
}

template< class ValType>
bool TStack<ValType>::IsEmpty()
{
	if (top == -1)
		return(true);
	else
		return(false);
}

template< class ValType>
int TStack<ValType>::GetSize()
{
	return(size);
}

template< class ValType>
void TStack<ValType>::Clean()
{
	if (size > N)
	{
		delete[]stk;
		size = N;
		stk = new ValType[size];
	}

	top = -1;
}

#endif