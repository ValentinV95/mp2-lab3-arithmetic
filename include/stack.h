// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

template <class T>
class Stack {
public:
    Stack(int N = 10) {
        if (N <= 0)
            throw std::logic_error("invalid stack size");
        data = new T[N];
        head = -1;
        size = N;
    }

    void push(T& A) {
        if (!IsFull()) {
            data[++head] = A;
        }
        else throw std::logic_error("The stack is full");
    }

    T pop() {
        if (!IsEmpty()) {
            T res = data[head--];
            return res;
        }
        else throw std::logic_error("Stack is empty");
    }

    bool IsEmpty() {
        if (head == -1) return true;
        else return false;
    }

    bool IsFull() {
        if (head == size - 1) return true;
        else return false;
    }

    T show() {
        if (!(this->isempty())) {
            int temp;
            temp = top - 1;
            return data[temp];
        }
        else {
            throw (0);
        }
    }

private:
    T* data;
    int head;
    int size;
}
