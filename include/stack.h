#ifndef __STACK_H__
#define __STACK_H__

#include <iostream>
#include <string>

using namespace std;

class Exception
{
    private:
        string msg_;
    public:
        Exception(string msg) {
            msg_ = msg;
            cerr << "ERROR: " << msg_ << endl;
        }
};

template <class ValType>
class TStack
{
    private:

        ValType* data;
        int top_;
        int maxSize_;

    public:

        TStack(int maxSize);
        TStack();
        TStack(const TStack& s);
        ~TStack();

        bool isFull();
        bool isEmpty();

        void push(const ValType& v);
        ValType pop();
        ValType getTop();
};

template <class ValType>
TStack<ValType>::TStack(int maxSize)
{
    if (maxSize <= 0) {
        throw Exception("cant create stack with null size");
    }

    maxSize_ = maxSize;
    data = new ValType[maxSize_];
    top_ = -1;
}

template <class ValType>
TStack<ValType>::TStack()
{
    maxSize_ = 100;
    data = new ValType[maxSize_];
    top_ = -1;
}

template <class ValType>
TStack<ValType>::TStack(const TStack& s)
{
    maxSize_ = s.maxSize_;
    top_ = s.top_;
    data = new ValType[maxSize_];

    for (int i = 0; i < top_; i++) {
        data[i] = s.data[i];
    }
}

template <class ValType>
TStack<ValType>::~TStack()
{
    delete[] data;
}

template <class ValType>
bool TStack<ValType>::isFull()
{
    if (top_ == maxSize_ - 1) {
        return true;
    }

    return false;
}

template <class ValType>
bool TStack<ValType>::isEmpty()
{
    if (top_ == -1) {
        return true;
    }

    return false;
}

template <class ValType>
void TStack<ValType>::push(const ValType& val)
{
    if (isFull()) {

        maxSize_ = (maxSize_ + 1) * 2;
        ValType* tmp = new ValType[maxSize_];

        for (int i = 0; i < top_; i++) {
            tmp[i] = data[i];
        }

        delete[] data;
        data = tmp;

    }

    top_++;
    data[top_] = val;
}

template <class ValType>
ValType TStack<ValType>::pop()
{
    if (isEmpty()) {
        throw Exception("stack is Empty");
    }
    return data[top_--];
}

template <class ValType>
ValType TStack<ValType>::getTop()
{
    if (isEmpty()) {
        throw Exception("stack is Empty");
    }

    return data[top_];
}

#endif