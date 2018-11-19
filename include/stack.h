// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, +
// - извлечение элемента, +
// - просмотр верхнего элемента (без удаления)+
// - проверка на пустоту, +
// - получение количества элементов в стеке+
// - очистка стека+
// при вставке в полный стек должна перевыделяться память+
#ifndef STACK_H
#define STACK_H
#define DEFC 2

template <class ValType>
class Stack
{
public:
	ValType *pStack;
	int finish;//Последний занятый
	int SizeE;//Количество элементов
	int SizeS;//Размер стека

		
	Stack()
	{
		pStack = new ValType[2];
		finish=-1;
		SizeS=2;
		SizeE=0;
	}
	Stack(int Size)
	{
		if(Size<0)
			throw"Negative leinght";
		pStack = new ValType[Size];
		finish=-1;
		SizeS=Size;
		SizeE=0;
	}
	
	void ClrSt()
	{
		finish=-1;
		SizeE=0;
	}

	void ClrElem()
	{
		finish--;
		SizeE--;
	}

	ValType Check()
	{
		if(!(IsEmpty()))
			return pStack[finish];			
		else
			throw"stack is empty";
		
	}
	int GetSizeE()
	{
		return SizeE;
	}
	void IsFull()
	{
		
		if(finish==SizeS-1)
		{
			int NewSize = DEFC*SizeS;

			ValType *pStack2;
			pStack2 = new ValType[NewSize];

			for(int i=0; i<SizeS; i++)
				pStack2[i]=pStack[i];

			delete[]pStack;
			pStack=pStack2;		
			
			SizeS=NewSize;
			
		}
	}
	int IsEmpty()
	{
		if(finish==-1)
			return 1;
		else
			return 0;
	}


	ValType Pop()
	{
		if(!(IsEmpty()))
		{
			ValType res = pStack[finish];
			finish--;
			SizeE--;
			return res;
		}
		else
			throw"stack is empty";
		
	}
	void Push(ValType Elem)
	{
		IsFull();
		finish++;	
		SizeE++;
		pStack[finish]=Elem;	
	}


};

#endif STACK_H