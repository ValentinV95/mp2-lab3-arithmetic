#ifndef __STACK_H__
#define __STACK_H__ 

const int MAX_SIZE_STACK = 100;

template <class ValType>
class TStack
{
    ValType *pMem;
    int count;
    int size;
    int head;
public:
    TStack(int len);
    ~TStack();
    int GetSize() { return size; }
    bool IsEmpty();
    bool IsFull();
    void Push(ValType val);
    void Clear();
    ValType Pop();
    ValType Top();
    
};

template <class ValType>
TStack<ValType>::TStack(int len)
{
    if((len<1) || (len>MAX_SIZE_STACK)) throw (len);
    size = len;
    count = 0;
    pMem=new ValType[size];
}

template<class ValType>
TStack<ValType>::~TStack()
{
    delete[] pMem;
}

template <class ValType>
bool TStack<ValType>::IsEmpty()
{
    if (count == -1)
    {
        return true;
    }
    else {
        return false;
    }
}

template<class ValType>
bool TStack<ValType>::IsFull()
{
    if (count == size-1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class ValType>
void TStack<ValType>::Push(ValType val)
{
    if (IsFull()) throw("stack");
    pMem[count++]=val;
}

template<class ValType>
void TStack<ValType>::Clear()
{
    head = -1;
    delete[] pMem;
    pMem = new TStack(size);
}

template <class ValType>
ValType TStack<ValType> ::Pop()
{
    if (IsEmpty() == 1)
    {
        throw ("Stack");
    }
    else
    {
        return pMem[(count--) - 1];
    }
}
    template <class ValType>
    ValType TStack<ValType>::Top()
    {
        if(IsEmpty()) throw("Stack");
            return pMem[(count)-1];
    }
    


#endif
