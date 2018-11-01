// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память
#include "iostream"
#include "vector"
using namespace std;

template <class val>
class Stack
{
private:
	vector <val> p;
	int Size;
	int top;
	bool IsFull();
public:
	Stack(int n = 10);
	~Stack() {};
	bool empty();
	val front();
	void pop();
	void push(val s);
};

template <class val>
Stack<val>::Stack(int n)
{
	Size = n;
	top = -1;
	p.resize(n);
}
template <class val>
bool Stack<val>::empty()
{
	if(top == -1)
	{
		return true;
	}
	return false;
}

template <class val>
bool Stack<val>::IsFull()
{
	if (top == Size - 1)
	{
		return true;
	}
	return false;

}

template <class val>
void Stack<val>::pop()
{
	if(!empty())
	{
		top--;
	}
	else
	{
		cout << "Stack is empty" << endl;
	}
}

template <class val>
void Stack<val>::push(val v)
{
	if(IsFull())
	{
		Size = 2 * Size;
		p.resize(Size);
	}
	p[++top] = v;
}

template <class val>
val Stack<val>::front()
{
	return p[top];
}