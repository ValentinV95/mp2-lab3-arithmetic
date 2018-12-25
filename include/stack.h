// ���������� � ���������� ���������� �����
// ���� ������������ ��������: 
// - ������� ��������, 
// - ���������� ��������, 
// - �������� �������� �������� (��� ��������)
// - �������� �� �������, 
// - ��������� ���������� ��������� � �����
// - ������� �����
// ��� ������� � ������ ���� ������ �������������� ������
#pragma once

const int MaxStackSize = 100;

template <typename T>
class TStack
{
	T*pMem; //��������� �� ������ ���������
	int size; // ������ ������ ��� �����
	int top; // ��������� �� ������� �����
	int DataCount; // ���������� ��������� � �����
public:

	TStack(int _size);
	TStack(const TStack & st); //�����������
	~TStack();
	int GetNextIndex(int index);// �������� ��������� ������
	void Put(const T&val); //���������� ��������
	T Get(void); // ��������� ��������	
	void Pop(); // �������� �������� ��������
	bool IsEmpty(); //�������� �� �������
	bool IsFull(); //�������� �� �������
	void Print(void); //�����
};


template <typename T>
TStack<T>::TStack(int _size)
{
	DataCount = 0;
	size = _size;
	top = -1;
	if ((size < 1) || (size > MaxStackSize))
		throw "size";
	pMem = new T[size];
}

template <typename T>
TStack<T>::TStack(const TStack & st) //�����������
{
	DataCount = 0;
	size = st.size;
	pMem = new T[size];
	for (int i = 0; i < size; i++)
	{
		pMem[i] = st.pMem[i];
	}
}

template <typename T>
TStack<T>::~TStack()
{
	delete[] pMem;
}

template <typename T>
int TStack<T>::GetNextIndex(int index)// �������� ��������� ������
{
	int res = index + 1;
	if (res > size)
		throw "error";
	return res;
}

template <typename T>
void TStack<T>::Put(const T&val) //���������� ��������
{
	if (!IsFull())
	{
		top = GetNextIndex(top);
		pMem[top] = val;
		DataCount++;
	}
	else
		throw "error";
}

template <typename T>
T TStack<T>::Get(void)
{
	if (!IsEmpty())
	{
		return pMem[top];
	}
	else
		throw"error";
}
template <typename T>
void TStack<T>::Pop()
{
	if (!IsEmpty())
	{
		DataCount--;
		top--;
	}
	else
		throw"error";
}

template <typename T>
bool TStack<T>::IsEmpty()
{
	if (DataCount == 0)
		return true;
	else
		return false;
}

template <typename T>
bool TStack<T>::IsFull() //�������� �� �������
{
	if (DataCount == MaxStackSize)
		return true;
	else
		return false;
}

template <typename T>
void TStack<T>::Print(void) //�����
{
	for (int i = 0; i < DataCount; i++)
		std::cout << "Stack[" << i << "]= " << pMem[i] << std::endl;
}