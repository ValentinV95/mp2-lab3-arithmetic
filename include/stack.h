#pragma once
// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

using namespace std;

template <class ValType>
class Stack
{
private:
	ValType *stack;
	int N;
	int End;
public:
	Stack(int _N)
	{
		stack = new ValType[_N];
		End = -1;
		N = _N;
	}
	~Stack()
	{
		delete[] stack;
	} 
	void Push(ValType elem)   
	{
		if (End+1 == N)
		{
			ValType *Temp = new ValType[2 * N];
			for (int i = 0; i < N; i++)
				Temp[i] = stack[i];
			N = 2 * N;
			delete[] stack;
			stack = Temp;
		}
		stack[++End] = elem;
	}
	ValType Pop() 
	{
		if (!isEmpty()) {
			return stack[End--];
		}
		else throw "false";
	}
	ValType Value()
	{
		if (!isEmpty()) {
			return stack[End];
		}
		else throw "false";
	}
	bool isEmpty() 
	{
		if (End == -1)
			return true;
		else return false;
	}
	int GetSize()
	{
		return End + 1;
	}
	void Clear()
	{
		End = -1;
		delete [] stack;
		stack = new ValType[N];
	}
};
