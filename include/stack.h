// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

template <typename T>
class Stack
{
	T* data;
	int head, n;
public:
	Stack(int _n = 10)
	{
		if (_n > 0)
		{
			data = new T[_n];
			head = 0;
			n = _n;
		}
		else
			throw("invalid stack size");
	}
	~Stack()
	{

	}
	void push(T x)
	{
		if (head == n)
		{
			T* tmp = new T[n];
			for (int i = 0; i < n; ++i)
			{
				tmp[i] = data[i];
			}
			delete[] data;
			data = tmp;
			delete[] tmp;
			n = n * 2;
		}
		data[head] = x;
		head++;
	}
	T pop()
	{
		if (!(this->IsEmpty()))
		{
			head--;
			return data[head];
		}
		else
		{
			throw ("stack is full!");;
		}
	}
	T value()
	{
		if (!(this->IsEmpty()))
		{
			int temp;
			temp = head - 1;
			return data[temp];
		}
		else
		{
			throw (0);
		}
	}
	bool IsEmpty()
	{
		if (head == 0)
		{
			return true;
		}
		return false;
	}	
	bool IsFull()
	{
		if (head == 0)
		{
			return false;
		}
		return true;
	}
};