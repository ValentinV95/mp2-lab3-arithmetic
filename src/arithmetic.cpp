// реализация функций и классов для вычисления арифметических выражений
#include <iostream>
#include "arithmetic.h"
#include "stack.h"
using namespace std;
int TPostfix::FormulaChecker(int bracket[], int &Size) // Проверка правильности скобок
{
	TStack<char> stack(MaxStackSize);
	int index = 1, CountError = 0;
	Size = 0;
	for (int i = 0; i < infix.length(); i++)
	{
		if (infix[i] == '(')
			stack.Put(index++);
		else
			if (infix[i] == ')')
			{
				if (!(stack.IsEmpty()))
				{
					bracket[Size++] = stack.Get();
					bracket[Size++] = index++;
				}
				else
				{
					bracket[Size++] = 0;
					bracket[Size++] = index++;
					CountError++;
				}
			}
	}
	while (!(stack.IsEmpty()))
	{
		CountError++;
		bracket[Size++] = stack.Get();
		bracket[Size++] = 0;
	}
	cout << "Count of error = " << CountError << endl;
	if (CountError != 0)
		for (int i = 0; i < Size - 1; i++, i++)
			cout << bracket[i] << "  " << bracket[i + 1] << endl;
	return CountError;
}

int TPostfix::Priority(char c)
{
	int res = 0;
	switch (c)
	{
	case  '(':
		res = 0;
		break;
	case ')':
		res = 1;
		break;
	case '+':
		res = 2;
		break;
	case '-':
		res = 2;
		break;
	case '*':
		res = 3;
		break;
	case '/':
		res = 3;
		break;
	}
	return res;
}

int TPostfix::IsDigit(char c) //операнда в числовой форме
{
	int a = int(c);
	return ((a >= 48) && (a <= 57));
}

int TPostfix::CheckOp(char c)
{
	int res = 0;
	switch (c)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '(':
	case ')':
	{
		res = 1;
		break;
	}
	}
	return res;
}

string TPostfix::ToPostfix() // перевод в постфиксную форму 
{
	TStack<char> stack(MaxStackSize);
	string postfix;
	int plen = 0; int pr;
	char temp, tmp;
	for (int i = 0; i < infix.length(); i++)
	{
		if (!(CheckOp(infix[i])))
		{
			postfix += infix[i];
		}
		else

			if (stack.IsEmpty())
			{
				stack.Put(infix[i]);
				postfix += ' ';
			}
			else
			{
				pr = Priority(infix[i]);
				if (!pr)
				{
					stack.Put(infix[i]);
				}
				else
				{
					tmp = stack.Get();
					if (pr > Priority(tmp))
					{
						if ((infix[i] != ')') || (tmp != '('))
						{
							postfix += ' ';
							stack.Put(tmp);
							stack.Put(infix[i]);
						}
					}
					else
					{
						if (pr == Priority(tmp))
						{
							postfix += ' ';
							postfix += tmp;
							stack.Put(infix[i]);
						}
						else
						{
							postfix += ' ';
							postfix += tmp;
							temp = infix[i];
							if (temp == ')')
							{
								do
								{
									tmp = stack.Get();
									if (tmp != '(')
									{
										postfix += ' ';
										postfix += tmp;
									}
								} while (tmp != '(');
							}
							else
							{
								if (!stack.IsEmpty())
									temp = stack.Get();
								if (pr <= Priority(temp))
								{
									postfix += temp;
									stack.Put(infix[i]);
								}
								else
									stack.Put(temp);
							}
						}
					}
				}
			}
	}
	while (!stack.IsEmpty())
	{
		postfix += ' ';
		postfix += stack.Get();
	}
	return postfix;
}

double TPostfix::Calculate(string postfix)
{
	char op;
	string post;
	double op1, op2;
	double res = 0;
	double rest = 0;
	TStack <double> Stack(MaxStackSize);
	for (int i = 0; i < postfix.length(); i++)
	{
		if (postfix[i] == ' ')
			continue;
		if (CheckOp(postfix[i]) != 1)
		{

			while (postfix[i] != ' ')
			{
				post += postfix[i];
				i++;
			}
			res = stof(post);
			Stack.Put(res);
			post.clear();
		}
		else
		{
			if (!(Stack.IsEmpty()))
			{
				op2 = Stack.Get();
				op1 = Stack.Get();
			}
			else throw "Not enough operands";
			op = postfix[i];
			switch (op)
			{
			case '+':
			{
				Stack.Put(op1 + op2);
				break;
			}
			case '-':
			{
				Stack.Put(op1 - op2);
				break;
			}
			case '*':
			{
				Stack.Put(op1*op2);
				break;
			}
			case '/':
			{
				if (op2 == 0)
					throw "Division by zero";
				else
					Stack.Put(op1 / op2);
			}
			}
		}

	}
	res = Stack.Get();
	return res;
}
