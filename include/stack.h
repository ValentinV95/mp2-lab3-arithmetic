#ifndef __STACK_H
#define __STACK_H

template <typename T>
class Stack
{
private:
	T* pStack;
	int Size;
	int top;
public:
	Stack(int = 2);
	Stack(const Stack<T> &);
	~Stack();

	inline void push(const T &);
	inline T pop();
	inline T spop();
	inline void isempty();
	inline int istop();
	inline bool empty();
	inline void isfull();
};

template <typename T>
Stack<T>::Stack(int _Size)
{
	if (_Size <= 0)
	{
		throw "size < 0";
	}
	Size = _Size;
	pStack = new T[Size];
	top = 0;
}

template <typename T>
Stack<T>::Stack(const Stack<T> & o_Stack)
{
	Size = o_Stack.Size;
	pStack = new T[Size];
	top = o_Stack.top;

	for (int i = 0; i < top; i++)
		pStack[i] = o_Stack.pStack[i];
}

template <typename T>
Stack<T>::~Stack()
{
	delete[] pStack;
}

template <typename T>
inline void Stack<T>::push(const T &value)
{
	isfull();
	pStack[top++] = value;
}

template <typename T>
inline T Stack<T>::pop()
{
	if (top > 0)
	{
		return pStack[--top];
	}
	else
	{
		throw "Stack is empty";
	}
}

template<typename T>
inline T Stack<T>::spop()
{
	if (top > 0)
	{
		return pStack[top - 1];
	}
}

template<typename T>
inline void Stack<T>::isempty()
{
	top = 0;
}

template<typename T>
inline int Stack<T>::istop()
{
	return top;
}

template <typename T>
inline bool Stack<T>::empty()
{
	return !(top);
}

template <typename T>
inline void Stack<T>::isfull()
{
	if (top == Size)
	{
		Stack<T> temp(*this);
		Size = 2 * Size;
		pStack = new T[Size];
		for (int i = 0; i < temp.Size; i++)
		{
			pStack[i] = temp.pStack[i];
		}
	}
}
// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

#endif