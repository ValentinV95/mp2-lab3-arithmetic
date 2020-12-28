
template <typename T>
class TStack
{
	T* data;
	int top, size;
public:
	TStack()
	{
		data = new T[10];
		top = 0;
		size = 10;
	}
	TStack(int x)
	{
		if (x > 0)
		{
			data = new T[x];
			top = 0;
			size = x;
		}
		else
			throw ("ERROR");
	}
	~TStack()
	{

	}
	void push(T x)
	{
		if (top == size)
		{
			T* tmp = new T[size];
			for (int i = 0; i < size; ++i)
			{
				tmp[i] = data[i];
			}
			delete[] data;
			data = new T[size * 2];
			for (int i = 0; i < size; ++i)
			{
				data[i] = tmp[i];
			}
			delete[]tmp;
			size = size * 2;
		}
		data[top] = x;
		top++;
	}
	T show()
	{
		if (!(this->isempty()))
		{
			int temp;
			temp = top - 1;
			return data[temp];
		}
		else
		{
			throw (0);
		}
	}
	T pop()
	{
		if (!(this->isempty()))
		{
			top--;
			return data[top];
		}
		else
		{
			throw ("ERROR");;
		}
	}
	bool isempty()
	{
		if (top == 0)
		{
			return true;
		}
		return false;
	}
	bool isempty()
	{
		return top;
	}
	void clrst()
	{
		top = 0;
	}
};