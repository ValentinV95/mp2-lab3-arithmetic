// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память
#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;


//Первый вошел - последний вышел
template <class Type>
class TStack
{
	Type *pMem;
	int size;
	int top;
public:
	TStack(int _size) : size(_size) {
		if (size < 1 || (size > MaxStackSize)) {
			throw size;
		}
		top = -1;
		pMem = new Type[size];
	}
	TStack(TStack& c) : size(c.size), top(c.top) {
		pMem = new Type[size];
		for (size_t i = 0; i < size; i++) {
			pMem[i] = c.pMem[i];
		}
	}
	bool IsEmpty() {
		return (top == -1);
	}
	bool IsFull() {
		return (top == size - 1);
	}
	Type Pop() {
		return pMem[top--];
	}
	void Push(Type v) {
		if (IsFull()) {
			return;
		}
		pMem[++top] = v;
	}
	int Size() {
		return size;
	}
	int Top() {
		return top;
	}
	Type GetTop() {
		return pMem[top];
	}
	TStack& operator=(TStack &c) {
		if (size != c.size) {
			size = c.size;
			delete[] pMem;
			pMem = new Type[size];
		}
		top = c.top;
		for (size_t i = 0; i < size; i++) {
			pMem[i] = c.pMem[i];
		}
		return (*this);
	}
	bool operator==(const TStack &c) const {
		if (size != c.size) {
			return false;
		}
		if (top != c.top) {
			return false;
		}
		for (size_t i = 0; i < size; i++) {
			if (pMem[i] != c.pMem[i]) {
				return false;
			}
		}
		return true;
	}
	bool operator!=(const TStack &c) const {
		return !(*this == c);
	}
	~TStack() {
		delete[] pMem;
	}
};
#endif