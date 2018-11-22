// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память
#ifndef _STACK_H_
#define _STACK_H_
#include <iostream> 
template <typename T> class stack { 
	T *parr; 
	int top, size; 
public: 
	stack() { 
		parr = new T[15]; 
		top = 0;
		size = 15;
	} 
	stack(int x) {
		parr = new T[x]; 
		top = 0; 
		size = x;
	}
	~stack() {}
	void push(T x) { 
		if (top == size) {

			T *temp = new T[size];

			for(int i = 0; i < size ; ++i) {
				temp[i]=parr[i];
			}

			delete [] parr;

			parr = new T[size*2]; 

			for(int i = 0; i < size ; ++i) {
				parr[i]=temp[i];
			}

			size = size* 2;
		}
		parr[top] = x; 
		top++; 
	} 
	T pop(){ 
		if (!(this->isempty())){ 
			top--; 
			return parr[top]; 
		} else {
		throw (0); 
		}
	} 
	
	T show() {
		if (!(this->isempty())){
			int temp;
			temp= top -1;
			return parr[temp]; 
		} else {
		throw (0); 
		}
	}

	bool isempty() { 
		if(top == 0) { 
			return true; 
		} 
		return false; 
	} 	
	
	int number() {
		return top;
	}

	void clrst() {
		top = 0;
	} 
};
#endif _STACK_H_