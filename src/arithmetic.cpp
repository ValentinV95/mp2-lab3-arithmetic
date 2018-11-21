// реализация функций и классов для вычисления арифметических выражений
#include "arithmetic.h"
#include "stack.h"
#include <iostream>

int TArithmetic::Priority(char c)
{
	switch (c)
	{
	case '+':
	{
		return 2;
	}
	case '-':
	{
		return 2;
	}
	case '*':
	{
		return 3;
	}
	case '/':
	{
		return 3;
	}
	}
}

string TArithmetic::ToArithmetic()
{
	TStack<char> stack(1);
	arithmetic += ' ';
	for (int i = 0; i < infix.length(); i++)
	{
		if (((int)infix[i] > 47) || (infix[i] == '.'))
		{
			arithmetic += infix[i];
			continue;
		}
		if (infix[i] == '(')
		{
			stack.Put('(');
			continue;
		}
		if ((infix[i] == ')') && !(stack.IsEmpty()))
		{
			bool flag1 = false;
			while (!flag1)
			{
				if (stack.IsEmpty())
				{
					flag1 = true;
					goto in1;
				}
				char tmp1 = stack.Get();
				if (tmp1 != '(')
				{
					flag1 = true;
					arithmetic += ' ';
					arithmetic += tmp1;
				}
			}
			char tmp2;
			if (!stack.IsEmpty())
			{
				tmp2 = stack.Get();
			}
			else
			{
				goto in1;
			}
			while ((tmp2 != '(') && !(stack.IsEmpty()))
			{
				arithmetic += ' ';
				arithmetic += tmp2;
				tmp2 = stack.Get();
			}
			continue;
		}
		if (stack.IsEmpty())
		{
			arithmetic += ' ';
			stack.Put(infix[i]);
		}
		else
		{
			bool flag = false;
			while (!flag)
			{
				if (stack.IsEmpty())
				{
					stack.Put(infix[i]);
					goto in1;
				}
				char tmp = stack.Get();
				if (tmp == '(')
				{
					arithmetic += ' ';
					stack.Put(tmp);
					stack.Put(infix[i]);
					goto in1;
				}
				if (Priority(tmp) >= Priority(infix[i]))
				{

					arithmetic += ' ';
					arithmetic += tmp;
				}
				else
				{
					arithmetic += ' ';
					stack.Put(tmp);
					stack.Put(infix[i]);
					flag = true;
				}
			}
		}
	in1: int a;
	}
	while (!stack.IsEmpty())
	{
		arithmetic += ' ';
		arithmetic += stack.Get();
	}
	return arithmetic;
}

double TArithmetic::Calculate()
{
	TStack<double> stack(1);
	string str;
	for (int i = 1; i < arithmetic.length(); i++)
	{
		while ((arithmetic[i] != ' ') && ((arithmetic[i] == '+') || (arithmetic[i] == '-') || (arithmetic[i] == '/') || (arithmetic[i] == '*')))
		{
			switch (arithmetic[i])
			{
			case '+':
			{
				double a1 = stack.Get();
				double a2 = stack.Get();
				stack.Put(a2 + a1);
				break;
			}
			case '-':
			{
				double a1 = stack.Get();
				double a2 = stack.Get();
				stack.Put(a2 - a1);
				break;
			}
			case '*':
			{
				double a1 = stack.Get();
				double a2 = stack.Get();
				stack.Put(a2 * a1);
				break;
			}
			case '/':
			{
				double a1 = stack.Get();
				double a2 = stack.Get();
				stack.Put(a2 / a1);
				break;
			}
			}
			goto in2;
		}
		while ((arithmetic[i] != ' ') && (((int)arithmetic[i] > 47) || (arithmetic[i] == '.')))
		{
			if ((int)arithmetic[i] > 64)
			{
				string a2;
				cout << "Inter " << arithmetic[i] << " : ";
				cin >> a2;
				str += a2;
				i++;
				goto in3;
			}
			str += arithmetic[i];
			i++;
		}
		if (str != "")
		{
		in3:		stack.Put(atof(str.c_str()));
			str.clear();
		}
	in2: int a;
	}
	return stack.Get();
}