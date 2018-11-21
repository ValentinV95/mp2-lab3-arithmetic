// ���������� � ���������� ���������� �����
// ���� ������������ ��������: 
// - ������� ��������, 
// - ���������� ��������, 
// - �������� �������� �������� (��� ��������)
// - �������� �� �������, 
// - ��������� ���������� ��������� � �����
// - ������� �����
// ��� ������� � ������ ���� ������ �������������� ������
#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
	T *pMem;
	int size;
	int top;
	int dataCount;
public:
	TStack(int _size)// �����������
	{
		dataCount = 0;
		size = _size;
		top = -1;
		if ((size < 1) || (size > MaxStackSize))
		{
			throw "wrong size of the stack";
		}
		pMem = new T[size];
	}
	~TStack()// ����������
	{
		delete[] pMem;
	}
	TStack(const TStack &stack)// ����������� �����������
	{
		pMem = new T[stack.size];
		size = stack.size;
		top = stack.top;
		dataCount = stack.dataCount;
		for (int i = 0; i < stack.size; i++)
		{
			pMem[i] = stack.pMem[i];
		}
	}
	TStack& operator=(const TStack &stack)// �������� ������������
	{
		this->size = stack.size;
		this->pMem = new T[size];
		for (int i = 0; i < size; i++)
		{
			this->pMem[i] = stack.pMem[i];
		}
		this->top = stack.top;
		this->dataCount = stack.dataCount;
		return *this;
	}
	int GetNextIndex()// �������� ��������� ������ 
	{
		return dataCount;
	}
	bool IsEmpty()// �������� �� ������� �����
	{
		if (dataCount == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool IsFull()//�������� �� ������� �����
	{
		if (dataCount == MaxStackSize)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void Put(const T &elem)// �������� ��������
	{
		if (!IsFull())
		{
			if (dataCount >= size)
			{
				dataCount++;
				size = dataCount;
				top = (dataCount - 1);
				T *pMem1;
				pMem1 = new T[size];
				for (int i = 0; i < dataCount - 1; i++)
				{
					pMem1[i] = pMem[i];
				}
				pMem = pMem1;
				pMem[top] = elem;
			}
			else
			{
				pMem[dataCount] = elem;
				top = (dataCount);
				dataCount++;
			}
		}
		else
		{
			throw "the stack is full";
		}
	}
	T Get()// ������� �������� 
	{
		if (!IsEmpty())
		{
			dataCount--;
			return pMem[top--];
		}
		else
		{
			throw "the stack is empty";
		}
	}
};
#endif