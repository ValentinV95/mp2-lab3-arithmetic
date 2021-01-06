// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#pragma once
#include <string>
#include <cmath>
#include "Stack.h"
using namespace std;

class Arithmetic
{
	string formula;
	Stack <char> st_c;
	Stack <double> st_d;
	string infix;
	string postfix;
	int Arithmetic::Priority(char с)
	{
		switch (с)
		{
		case'+': return 2;
		case'-': return 2;
		case'*': return 3;
		case'/': return 3;
		case'(':return 1;
		case')':return 1;
		case'^':return 4;
		case'sin':return 1;
		case'cos':return 1;
		case'log':return 1;
		case'e':return 1;
		case '-un':return 1;
		default: return 0;
		}
	}
public:
	Arithmetic() :st_c(10), st_d(10)
	{
		infix = "";
		postfix = "";
	}
	Arithmetic(const Arithmetic& calc)
	{
		infix = calc.infix;
		postfix = calc.postfix;
		st_c = calc.st_c;
		st_d = calc.st_d;
	}
	~Arithmetic() {};
	bool Arithmetic::CheckBrackets()
	{
		st_c.Clear();
		st_d.Clear();
		for (int i = 0; i < infix.size(); i++)
		{
			if (infix[i] == '(' || infix[i] == 'sin' || infix[i] == 'cos' || infix[i] == 'e' || infix[i] == 'log' || infix[i] == '-un')
			{
				st_c.Push(infix[i]);
			}
			if (infix[i] == ')')
			{
				if (st_c.Empty() == true)
				{
					return false;
				}
				st_c.Pop();
			}
		}
		return st_c.Empty();
	}

	void Arithmetic::SetFormula(string str)
	{
		infix = " ";
		for (unsigned int i = 0; i < str.size(); i++)
		{
			if (str[i] == 'sin' || str[i] == 'cos' || str[i] == 'e' || str[i] == 'log' || infix[i] == '-un')
			{
				infix += " ";
				infix += str[i];
				i += 3;
				if (i >= str.size() - 2)
					throw 0;
			}
			else
			{
				if (Priority(str[i]) != 0)
				{
					infix += " ";
				}
				infix += str[i];
			}

		}
		infix += ' ';
		if (CheckBrackets() != true)
		{
			throw 0;
		}
		Stack<char> c(infix.size());
		Stack<double> d(infix.size());
		st_c = c;
		st_d = d;
	}

	string Arithmetic::GetInfix()
	{
		return infix;
	}

	string Arithmetic::GetPostfix()
	{
		return postfix;
	}

	void  Arithmetic::ToPostfix()
	{
		st_c.Clear();
		st_d.Clear();
		postfix = "";
		std::string tmp = "(" + infix + ")";
		for (unsigned int i = 0; i < tmp.size(); i++)
		{
			if (Priority(tmp[i]) == 0)
			{
				postfix += tmp[i];
			}
			else
			{
				if (tmp[i] == '(' || tmp[i] == 'sin' || tmp[i] == 'cos' || tmp[i] == 'log' || tmp[i] == 'e' || infix[i] == '-un')
				{
					st_c.Push(tmp[i]);
				}
				else
				{
					if (tmp[i] == ')')
					{
						while (st_c.Top() != '(' && st_c.Top() != 'sin' && st_c.Top() != 'cos' && st_c.Top() != 'log' && st_c.Top() != 'e' && st_c.Top() != '-un')
						{
							char a = st_c.Pop();
							postfix += ' ';
							postfix += a;
						}
						if (st_c.Top() == '(')
							st_c.Pop();
						else
						{
							char a = st_c.Pop();
							postfix += ' ';
							postfix += a;
						}
					}
					else
					{
						while (Priority(st_c.Top()) >= Priority(tmp[i]))
						{
							char a = st_c.Pop();
							postfix += ' ';
							postfix += a;
						}
						st_c.Push(tmp[i]);
					}
				}
			}
		}
		if (!st_c.Empty())
		{
			throw 0;
		}
	}



	double res()
	{
		ToPostfix();
		st_c.Clear();
		st_d.Clear();
		for (int i = 0; i < postfix.size(); i++)
		{
			double a, b;
			switch (postfix[i])
			{
			case'+': a = st_d.Pop(); b = st_d.Pop();
				st_d.Push(a + b);
				break;
			case'-': a = st_d.Pop(); b = st_d.Pop();
				st_d.Push(b - a);
				break;
			case'*': a = st_d.Pop(); b = st_d.Pop();
				st_d.Push(b * a);
				break;
			case'/': a = st_d.Pop(); b = st_d.Pop();
				st_d.Push(b / a);
				break;
			case'^': a = st_d.Pop(); b = st_d.Pop();
				st_d.Push(pow(b, a));
				break;
			case'sin': a = st_d.Pop(); st_d.Push(sin(a));
				break;
			case'cos': a = st_d.Pop(); st_d.Push(cos(a));
				break;
			case'e': a = st_d.Pop(); st_d.Push(exp(a));
				break;
			case'log': a = st_d.Pop(); st_d.Push(log(a));
				break;
			case'-un': a = st_d.Pop(); st_d.Push(-1 * a);
				break;
			default:
				if (postfix[i] != ' ')
				{
					unsigned int k = i, point = 0, flag = 0;;
					while (postfix[k] != ' ' && k != postfix.size())
					{
						if (postfix[k] == '.')
						{
							point = k;
							flag = 1;
						}
						k++;
					}
					unsigned int delta = k - i - flag;
					if (flag == 1)
					{
						point = k - point - flag;
					}
					k = i;
					double z = 0;
					while (postfix[k] != ' ' && k != postfix.size())
					{
						if (postfix[k] != '.')
						{
							delta--;
							z += (postfix[k] - '0') * pow(10, delta);
						}
						k++;
					}
					if (flag == 1)
					{
						z /= pow(10, point);
					}
					st_d.Push(z);
					i = k;
				}
				break;
			}
		}
		if (st_d.Size() != 1)
		{
			throw 0;
		}
		return st_d.Pop();
	}
};

