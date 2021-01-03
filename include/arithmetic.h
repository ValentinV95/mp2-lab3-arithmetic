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
	int Arithmetic::Priority(char elem)
	{
		switch (elem)
		{
		case  '(': return 0;
		case  ')': return 1;
		case  '+': return 2;
		case  '-': return 2;
		case  '*': return 3;
		case  '/': return 3;
		case  '^': return 4;
		case  'un-': return 4;
		case  'sin': return 4;
		case  'cos': return 4;
		case  'ln': return 4;
		case  'exp': return 4;
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
			if (infix[i] == '(')
			{
				if (st_c.Full())
				{
					return false;
				}
				else
				{
					st_c.Push('(');
				}
			}
			if (infix[i] == ')')
			{
				if (st_c.Empty() == true)
				{
					return false;
				}
				else
				{
					st_c.Pop();
				}
			}
		}
		return st_c.Empty();
	}

	void Arithmetic::SetFormula(string str)
	{
		infix = "";
		for (unsigned int i = 0; i < str.size(); i++)
		{
			if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^')
			{
				infix += " ";
			}
			infix += str[i];
		}
		if (CheckBrackets() != true)
		{
			throw 0;
		}
		Stack<char> s(infix.size());
		Stack<double> d(infix.size());
		st_c = s;
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


	void Arithmetic::SetExpression(string expr)
	{
		infix = expr;
		if (CheckBrackets())
		{
			ToPostfix();
		}
	}


	void  Arithmetic::ToPostfix()
	{
		if (!CheckBrackets())
		{
			throw "Wrong number of brackets";
		}
		st_c.Clear();
		st_d.Clear();
		postfix = " ";
		string scr = "( " + infix + " )";
		char elem = ' ! ';
		unsigned int i = 0;
		st_c.Clear();
		while (i < scr.size())
		{
			if (scr[i] == '+' || scr[i] == '-' || scr[i] == '*' || scr[i] == '/' || scr[i] == '^' || scr[i] == 'un-' || scr[i] == 'sin' || scr[i] == 'cos' || scr[i] == 'ln' || scr[i] == 'exp')
			{
				postfix += " ";
				elem = st_c.Pop();
				while (Priority(elem) >= Priority(scr[i]))
				{
					postfix += elem;
					elem = st_c.Pop();
				}
				st_c.Push(elem);
				st_c.Push(scr[i]);
			}
			else
				if (scr[i] == '(')
				{
					st_c.Push(scr[i]);
				}
				else
					if (scr[i] == ')')
					{
						elem = st_c.Pop();
						while (elem != '(')
						{
							postfix += elem;
							elem = st_c.Pop();
						}
					}
					else
						if (scr[i] >= '0' && scr[i] <= '9')
						{
							postfix += scr[i];
						}
			i++;
		}
		if (!st_c.Empty())
		{
			throw 0;
		}
	}



	double  Arithmetic::CalcPostfix()
	{
		if (!CheckBrackets())
		{
			throw "Wrong number of brackets";
		}
		st_d.Clear();
		char* tmp;
		unsigned int i = 0;
		double res = 0;
		while (i < postfix.size())
		{
			if (postfix[i] >= '0' && postfix[i] <= '9')
			{
				double d = strtod(&postfix[i], &tmp);
				int j = tmp - &postfix[i];
				i += j - 1;
				st_d.Push(d);
			}
			if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^')
			{
				if (st_d.Empty())
				{
					throw "Wrong";
				}
				else
				{
					double op1, op2;
					op2 = st_d.Pop();
					op1 = st_d.Pop();
					switch (postfix[i]) {
					case '+':
						res = op1 + op2; break;
					case '-':
						res = op1 - op2; break;
					case '*':
						res = op1 * op2; break;
					case '/':
						res = op1 / op2; break;
					case '^':
						res = pow(op1, op2); break;
					case'un-':
						res = -1*op2; break;
					case'sin':
						res = sin(op2); break;
					case'cos':
						res = cos(op2); break;
					case'ln':
						res = log(op2); break;
					case'exp':
						res = exp(op2); break;
					default: if (formula[i] != ' ')
						st_d.Push(formula[i] - '0');
						break;
					}
					st_d.Push(res);
				}
			}
			i++;
		}
		if (st_d.Empty())
		{
			throw "Wrong";
		}
		else
		{
			res = st_d.Pop();
			return res;
		}
	}
};
