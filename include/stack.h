template <class T>
class Stack {

private:
	int stackSize;
	int top;
	T *data;
public:
	// constructors
	Stack() { stackSize = 100; data = new T[stackSize]; top = -1; }
	Stack(int _size) 
	{ 
		if (!_size) throw "Stack can't have null size";
		stackSize = _size; data = new T[stackSize]; top = -1;
	}
	// methods
	T getTop();
	T getSize();
	T pop();
	void push(const T &x);
	void clear();
	bool isEmpty();
	bool isFull();
};

template <class T>
void Stack<T>::clear()
{
	top = -1;
	delete[] data;
	data = new T[stackSize];
}

template<class T> 
T Stack<T>::getSize() 
{
	return top + 1;
}

template <class T> 
T Stack<T>::getTop() 
{
	if (isEmpty())
		throw "Stack is empty, can't get top";
	return data[top];
}

template <class T>
bool Stack<T>::isEmpty() 
{
	return top == -1;
}

template <class T>
void Stack <T>::push(const T &x) 
{
	if (isFull()) {
		stackSize = (stackSize+1) * 2;
		T* tmp = new T[stackSize];
		for (int i = 0; i < top + 1; i++) {
			tmp[i] = data[i];
		}
		delete[] data;
		data = tmp;
	}
	top++;
	data[top] = x;
}

template <class T>
T Stack <T>::pop() 
{
	if (!isEmpty())
		return data[top--];
	else throw "Stack is empty";
}

template <class T>
bool Stack<T>::isFull() 
{
	return top >= stackSize - 1;
}