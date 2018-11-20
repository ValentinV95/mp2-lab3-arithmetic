// реализация функций и классов для вычисления арифметических выражений
#include <arithmetic.h> 
#include <string>
#include <iostream>
using namespace std;

int WhatPriority(string symbol)
{
		if((symbol=="+")||(symbol=="-"))
			return 1;
		if((symbol=="*")||(symbol=="/"))
			return 3;
		if((symbol==")")||(symbol=="("))
			return 5;
		return 0;
	}

int WhatTip(string symbol)
	{
		if((symbol=="+")||(symbol=="-")||(symbol=="*")||(symbol=="/"))
			return 2;
		if((symbol=="(")||(symbol==")"))
			return 3;

		return 0;
	}

void firstcontrol(string str)
{
	int j=0;
	for(int i=0; i<str.length(); i++)//проверка соответствия скобок
	{
		if(str[i]=='(')
			j++;
		if(str[i]==')')
			j--;
		if((i!=str.length()-1)&&(str[i]=='(')&&(str[i+1]==')'))
		{
			cout<<"errors symbol "<<i; 
			throw"empty between parentheses";
		}
		if((i!=str.length()-1)&&(str[i]==')')&&(str[i+1]=='('))
		{
			throw"empty between parentheses";
			cout<<"errors symbol "<<i; 
		}
	}

	if(j>0)
		throw"missing closing parentheses";
	if(j<0)
		throw"missing opening parentheses";

	string a;
	for(int i=0; i<str.length(); i++)//проверка некорректных символов
	{
		a=str.substr(i, 1);
		switch (WhatTip(a))
		{
		case 2: break;
		case 3: break;
		case 0: if((str[i]<='9')&&(str[i]>='0')||(str[i]=='.')||(str[i]==' '))
					break;
			cout<<"errors symbol "<<i; 
			throw"incorrect symbols";
		}
	}
		
}

void secondcontrol(Stack<TLexems> res)
{
	int k,z=0, j, m=res.GetSizeE()-1;
	for(int i=res.GetSizeE()-1; i>=0 ;i--)//проверка на соответствие скобок
	{
		k=0;
		if(res.pStack[i].symbols=="(")
		{
			z=1;
			for(j=m;j>=0;j--)
				if((res.pStack[j].symbols==")")&&(j<i))
				{
					k=1;
					m=j-1;
					break;
				}
		}
		if((!k)&&(z))
		{
			cout<<"errors lexems "<<i; 
			throw"incorrect parentheses";
		}
		z=0;
	}


	
	for(int i=0; i<res.GetSizeE();i++)
	{
		k=0;
		switch (res.pStack[i].UnOrBinOrDig)
		{
		case 2: {
			if((i==res.GetSizeE()-1)||(res.pStack[i-1].UnOrBinOrDig==2)||(res.pStack[i-1].symbols==")"))
			{
				cout<<"errors lexems "<<i-1; 
				throw"incorrect lexems";
			}
				}
				break;
		case 3: {
			if(res.pStack[i].symbols=="(")
				if(res.pStack[i-1].UnOrBinOrDig==2)
				{
					cout<<"errors lexems "<<i-1; 
					throw"incorrect symbols after opening parentheses";
				}

			if(res.pStack[i].symbols==")")
				if((i!=0)&&(res.pStack[i-1].UnOrBinOrDig==0))
				{
					cout<<"errors lexems "<<i-1; 
					throw"incorrect symbols after closing parentheses";
				}
				}
				break;
		case 0: {
			for(int l=0;l<res.pStack[i].symbols.length()-1;l++)//проверяем числа на подобную ошибку 2.2.1
				if(res.pStack[i].symbols[l]=='.')
					k++;
			if(k>1)
			{
				cout<<"errors lexems "<<i; 
				throw"incorrect digit";
			}

			if((i!=0)&&((res.pStack[i-1].UnOrBinOrDig==0)||(res.pStack[i-1].symbols=="(")))
			{
				cout<<"errors lexems "<<i-1; 
				throw"incorrect symbols after digit";
			}
				}
				break;
		}
	}
}

double interpreter(string str)
{
	Stack<TLexems> res;
	double answer=0.0;
	int i = str.length()-1;
	int k = 0, un = 0;

	firstcontrol(str);

	while(i >= 0)
	{
		un=0;
		k = 0;

		if((str.substr(i, 1)=="-")&&(str.substr(i+1, 1)=="("))//учитываем унарный минус
			if((i==0)||((i!=0)&&(WhatTip(str.substr(i-1, 1))==2)))
			{
				k = 1;
				i--;
				un=1;
			}

		if(i>=0)
		if ((WhatPriority(str.substr(i, 1))==0))//выделение чисел
		{
			k = 1;
			i--;
			
			while((i>=0)&&((WhatPriority(str.substr(i, 1))==0)||((str.substr(i, 1)=="-")&&((i==0)||(str.substr(i-1, 1)=="(")||(WhatTip(str.substr(i-1, 1))==2)))))//учитываем, что минус может стоять перед числом и это будет отриц. число
			{
				k++;
				i--;
			}
		} 

		
		
		if ((i>=0)&&(WhatPriority(str.substr(i, 1))!=0)&&(k==0)&&(WhatPriority(str.substr(i, 1))!=5))//Выделение лексем
		{
			k = 1;
			i--;
			if(i>=0)
			while((WhatPriority(str.substr(i, 1))!=0)&&(WhatPriority(str.substr(i, 1))!=5))
			{
				k++;
				i--;
			}
		}

		if ((i>=0)&&(WhatPriority(str.substr(i, 1))==5)&&(k==0))//выделение скобок
		{
			k = 1;
			i--;
		}
		
		TLexems a(str.substr(i+1, k));

		if(un==1)//учитываем унарный минус
		{
			a.UnOrBinOrDig=1;
			a.priority=4;
		}

		//cout<<a.symbols<<"  ";
		res.Push(a);
			

	}

	secondcontrol(res);
	return notation(res);
		
}

double notation(Stack<TLexems> res)
{
	int Size = res.GetSizeE();
	Stack<TLexems> not(Size);
	Stack<TLexems> lex;

	
	for(int i=0; i<Size; i++)
	{
		switch(res.Check().priority)
		{
			case 0:not.Push(res.Pop());break;
			case 5:
				{
					if(res.Check().symbols=="(")
						lex.Push(res.Pop());
					if(res.Check().symbols==")")
					{
						res.ClrElem();
						while(lex.Check().priority!=5)
							not.Push(lex.Pop());
						lex.ClrElem();
					}

				}
				break;

			case 1:
				{
					if(lex.IsEmpty())
						lex.Push(res.Pop());
					else
					{
						
						if((lex.Check().priority<1)||(lex.Check().symbols=="("))
							lex.Push(res.Pop());
						else
						{
							while(!lex.IsEmpty())
							{
								if(lex.Check().symbols=="(")
									break;
								not.Push(lex.Pop());
							}
							lex.Push(res.Pop());
						}

						
					}


				}
				break;

			case 4:
				{
					if(lex.IsEmpty())
						lex.Push(res.Pop());
					else
						if((lex.Check().priority<4)||(lex.Check().symbols=="("))
							lex.Push(res.Pop());
						else
						{
							while(!lex.IsEmpty())
							{
								if(lex.Check().symbols=="(")
									break;
								not.Push(lex.Pop());
							}
							lex.Push(res.Pop());
						}
				}
				break;
				
			case 3:
				{
					if(lex.IsEmpty())
						lex.Push(res.Pop());
					else
						if((lex.Check().priority<3)||(lex.Check().symbols=="("))
							lex.Push(res.Pop());
						else
						{
							while(!lex.IsEmpty())
							{
								if(lex.Check().symbols=="(")
									break;
								not.Push(lex.Pop());
							}
							lex.Push(res.Pop());
						}
				}
		}
	}
	while(!lex.IsEmpty())
		not.Push(lex.Pop());
	
	cout<<endl;
	/*while(!not.IsEmpty())
		cout<<not.Pop().symbols<<"  ";*/
	
	return calculate(not);
}


double calculate(Stack<TLexems> not)
{
	int Size = not.GetSizeE();

	Stack<TLexems> invert;
	Stack<double> result;

	while (!not.IsEmpty())
		invert.Push(not.Pop());

	string z;

	for(int i=0; i<Size; i++)
	{
		if(invert.IsEmpty()!=1)
		switch(invert.Check().priority)
		{
		case 0:
			{
				z=invert.Pop().symbols;
				result.Push(atof(z.c_str()));
			}
			break;
		case 1:
			{
				if((invert.IsEmpty()!=1)&&(invert.Check().symbols=="+"))
				{	
					invert.ClrElem();
					double a= result.Pop();
					double b= result.Pop();
					result.Push(a+b);
				}
				if((invert.IsEmpty()!=1)&&(invert.Check().symbols=="-")&&(invert.Check().priority==1))
				{				
					invert.ClrElem();
					double a= result.Pop();
					double b= result.Pop();
					result.Push(b-a);					
				}
			}
			break;
		case 4:
			{
				
				if((invert.IsEmpty()!=1)&&(invert.Check().symbols=="-"))
				{				
					invert.ClrElem();
					double a= result.Pop();
					
					result.Push(-1*a);					
				}
			}
			break;
		case 3:
			{
				if((invert.IsEmpty()!=1)&&(invert.Check().symbols=="*"))
				{	
					invert.ClrElem();
					double a= result.Pop();
					double b= result.Pop();
					result.Push(a*b);
				}
				if((invert.IsEmpty()!=1)&&(invert.Check().symbols=="/"))
				{	
					invert.ClrElem();
					double a= result.Pop();
					double b= result.Pop();
					if(a==0)
						throw"division by 0";
					result.Push(b/a);
				}
			}
			break;
		}
	}

	double a = result.Pop();
	return  a;
}
