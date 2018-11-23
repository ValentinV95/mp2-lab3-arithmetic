// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента // push
// - извлечение элемента // pop
// - просмотр верхнего элемента (без удаления) // getTop
// - проверка на пустоту, // isEmpty
// - получение количества элементов в стеке // getSize
// - очистка стека // clear
// при вставке в полный стек должна перевыделяться память // resize


const int N = 3;
template <class T>
class Stack {

private:
	int top;
	T *data;
public:
	// constructors
	Stack() { data = new T[N]; top = -1; }
	Stack(int n) { data = new T[n]; top = -1; }
	// methods
	T getTop();
	T getSize();
	T pop();
	void push(const T &x);
	void clear();
	bool isEmpty();
	bool isFull();
	void resize();
};

template <class T>
void Stack<T>::clear() {
	top = -1;
}

template<class T> 
T Stack<T>::getSize() {
	return top + 1;
}

template <class T> 
T Stack<T>::getTop() {
	return data[top];
}

template <class T>
bool Stack<T>::isEmpty() {
	return top == -1;
}

template <class T>
void Stack <T>::push(const T &x) {
	if (!isFull())
		data[++top] = x;
	else this->resize();
}

template <class T>
T Stack <T>::pop() {
	if (!isEmpty())
		return data[top--];
	else throw "Stack is empty";
}

template <class T>
bool Stack<T>::isFull() {
	return top >= N - 1;
}

template <class T>
void Stack <T>::resize() {
	if (isFull()) {
		T* tmp = new T[N];
		for (int i = 0; i < N; i++) {
			tmp[i] = data[i];
		}
		data = new T[2 * N];
		for (int i = 0; i < N; i++) {
			data[i] = tmp[i];
		}
		delete[] tmp;
	}
}