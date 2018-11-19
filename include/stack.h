// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

#ifndef stack_h
#define stack_h

template <class TType>
class TStack
{
	int top;
	int size;
	TType *mas;

public:
	TStack();
	TStack(int ssize);
	void Push(const TType &val);
	TType Pop();
	bool Empty();
	void NewLen();
	~TStack() { delete[]mas; };
	TType CheckLast();
	void ClearStack();
	int GetSize();
};

template <class TType>
TStack <TType>::TStack()
{

	size = 10;
	top = -1;
	mas = new TType[size];
}

template <class TType>
TStack <TType>::TStack(int ssize)
{
	if (ssize <= 0)
		throw ("Uncorr stack leight");
	size = ssize;
	top = -1;
	mas = new TType[size];
}
template <class TType>
void TStack<TType>::Push(const TType &val)
{
	if (size == top + 1)
		NewLen();
	mas[top + 1] = val;
	top++;
}
template <class TType>
TType TStack<TType>::Pop()
{
	if (Empty())
		throw ("Stack is empty");

	TType a = mas[top];
	top--;
	return a;

}
template <class TType>
void TStack<TType>::NewLen()
{
	TType *Copmas = new TType[size * 2];
	for (int i = 0; i < size; i++)
		Copmas[i] = mas[i];
	delete[]mas;
	size *= 2;
	mas = Copmas;
}
template <class TType>
bool TStack<TType>::Empty()
{
	if (top == -1)
		return true;
	else return false;
}

template <class TType>
TType TStack<TType>::CheckLast()
{
	if (Empty())
		 throw ("Stack is empty");
	return (mas[top]);
}
template <class TType>
void TStack<TType>::ClearStack()
{
	top = -1;


}
template <class TType>
int TStack<TType>::GetSize()
{
	return size;
}


#endif