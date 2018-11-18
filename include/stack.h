#ifndef UNTITLED16_STACK_H
#define UNTITLED16_STACK_H

const int size1 = 100; 

template <class T>
class Stack
{
protected:
	int top;
	int size;
	T *stack1;
public:
	Stack(int n = size1);
	~Stack();
	void push(T x);
	void pop();
	bool IsEmpty();
	T front();
	int size_stack();
	void clear();
	void resize();
};


template <class T>
Stack <T>::Stack(int n) {
	size = n;
	top = -1;
	stack1 = new T[size];
}

template <class T>
Stack <T>::~Stack() {
	delete[] stack1;
}

template <class T>
void Stack <T>::push(T x) {
	if (top + 1 == size) {
		resize();
	}
	stack1[++top] = x;
}

template <class T>
void Stack <T>::pop() {
	if (this->IsEmpty()) {
		throw("Error");
	}
	--top;
}

template <class T>
T Stack <T>::front() {
	if (this->IsEmpty())
	{
		throw("Error");
	}
	return stack1[top];
}

template <class T>
bool Stack <T>::IsEmpty() {
	if (top == -1) return true;
	return false;
}

template <class  T>
int Stack <T>::size_stack() {
	return top + 1;
}

template <class T>
void Stack <T>::clear() {
	while (!(this->IsEmpty()))
	{
		pop();
	}
}

template <class T>
void Stack <T>::resize() {
	int new_size = size * 2;
	T *new_stack = new T[new_size];
	for (int i = 0; i < size; i++)
	{
		new_stack[i] = stack1[i];
	}
	delete[] stack1;
	stack1 = new_stack;
	size = new_size;
}


#endif //UNTITLED16_STACK_H
