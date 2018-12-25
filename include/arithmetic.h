// объявление функций и классов для вычисления арифметических выражений
# pragma once
#include <string>
#include <iostream>
#include "stack.h"
using namespace std;

class TPostfix
{
	string infix;
	string postfix;
	int Priority(char c);
	bool CheckOp(char c);
public:

	TPostfix(string _infix) // Конструктор
	{
		infix = _infix;
	}
	int FormulaChecker(int bracket[], int &Size); // Проверка правильности;	
	string GetInfix() { return infix; }
	string ToPostfix();
	double Calculate(const string& str);

};

int TPostfix::FormulaChecker(int bracket[], int &Size) // Проверка правильности скобок
{
	TStack<char> stack(MaxStackSize);
	int index = 1, CountError = 0;
	Size = 0;
	for (unsigned int i = 0; i < infix.length(); i++)
	{
		if ((isdigit(infix[i]) == 0) && (infix[i] != '+') && (infix[i] != '-') && (infix[i] != '*') && (infix[i] != '/') && (infix[i] != '.') && (infix[i] != '(') && (infix[i] != ')')) 
		{
			cout << "incorrect simbols" << endl;
			return CountError++;
		}
	}
	for (unsigned int i = 0; i < infix.length(); i++)
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

bool TPostfix::CheckOp(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

int TPostfix::Priority(char ch)
{
	if (ch < 0)
		return 3;
	if (ch == '*' || ch == '/')
	{
		return 2;
	}
	if (ch == '+' || ch == '-')
	{
		return 1;
	}
	return 0;
}

string TPostfix::ToPostfix()
{
	string postfix = "";
	bool may_unary = true;
	TStack <char> oper(MaxStackSize);
	for (size_t i = 0; i < infix.length(); ++i)
	{
		if (infix[i] != ' ')
		{
			if (infix[i] == '(')
			{
				oper.Put('(');
				may_unary = true;
			}
			else
			{
				if (infix[i] == ')')
				{
					while (oper.Get() != '(')
					{
						if (oper.Get() == -'-')
						{
							postfix += "@";
						}
						else
						{
							postfix += oper.Get();
						}
						oper.Pop();
					}
					oper.Pop();
					may_unary = false;
				}
				else
				{
					if (CheckOp(infix[i]))
					{
						char curop = infix[i];
						if (may_unary && curop == '-')
						{
							curop = -curop;
						}
						while (!oper.IsEmpty() && (curop >= 0 && Priority(oper.Get()) >= Priority(curop) || curop < 0 && Priority(oper.Get()) > Priority(curop)))
						{

							if (oper.Get() == -'-')
							{
								postfix += "@";
							}
							else
							{
								postfix += oper.Get();
							}
							oper.Pop();
						}
						oper.Put(curop);
						may_unary = true;
					}
					else
					{
						while (i < infix.length() && isdigit(infix[i]))
						{
							postfix += infix[i];
							i++;
						}
						postfix += " ";
						i--;
						may_unary = false;
					}
				}
			}
		}
	}
	while (!oper.IsEmpty())
	{
		if (oper.Get() == -'-')
		{
			postfix += "@";
		}
		else
		{
			postfix += oper.Get();
		}
		oper.Pop();
	}
	return postfix;
}

double TPostfix::Calculate(const string& str)
{
	TStack<double> st(MaxStackSize);
	string operand;
	double left;
	double right;
	for (int i = 0; i < str.length(); i++)
	{
		if (isdigit(str[i]))
		{
			operand = "";
			while (i < str.length() && str[i] != ' ')
			{
				operand += str[i];
				i++;
			}
			st.Put(atoi(operand.c_str()));
		}
		if (str[i] == '@') // унарный минус
		{
			left = st.Get();
			st.Pop();
			left = -left;
			st.Put(left);
		}
		if (CheckOp(str[i]) == true)
		{
			right = st.Get();
			st.Pop();
			left = st.Get();
			st.Pop();
			switch (str[i])
			{
			case '+':  st.Put(left + right);  break;
			case '-':  st.Put(left - right);  break;
			case '*':  st.Put(left * right);  break;
			case '/':  st.Put(left / right);  break;
			}
		}
	}
	return st.Get();
}