


#ifndef __STACK_

#define __STACK_

//typedef unsigned size_t;

template <typename T>
class TStack {
private:
    struct elem {
        elem(T value, elem* next = nullptr) :value(value), next(next) {};
        T value;
        elem* next;
    };
public:
    TStack() : head(nullptr), count(0) { /*head = NULL;*/ };
    ~TStack() { clear(); };

    void push(T value);
    T pop();
    T top() const;
    bool empty() const;
    size_t size() const;
    void clear();
private:
    elem* head;
    size_t count;
};

template <typename T>
void TStack<T>::push(T value) {
    head = new elem(value, head);
    count++;
}

template <typename T>
T TStack<T>::pop() {
    elem* popped = head;
    head = head->next;
    T value = popped->value;
    delete popped;
    count--;
    return value;
}

template <typename T>
T TStack<T>::top() const {
    return head->value; //(*head).value
}

template <typename T>
bool TStack<T>::empty() const {
    return head == nullptr;
}

template <typename T>
size_t TStack<T>::size() const {
    return count;
}

template <typename T>
void TStack<T>::clear() {
    while (head != nullptr) {
        elem* del = head;
        head = head->next;
        delete del;
    }
    count = 0;
}

#endif
