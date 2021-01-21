#ifndef _ARITHMETIC_H_ 
#define _ARITHMETIC_H_ 

#include <iostream>
#include <string>
#include<vector>
#include "stack.h"
using namespace std;

class Arithmetic

{
	string infix;
	string postfix;

public:

	Arithmetic(string s)

	{
		infix = s;
	}




	bool IsOperator(char s)
	{

		if (s == '+' || s == '*' || s == '-' || s == '/' || s == '_')
			return true;
		else return false;
	}
	int Priority(char s)
	{
		if (s == '_')
			return 2;
		if (s == '*')
			return 1;
		if (s == '/')
			return 1;
		if (s == '+')
			return 0;
		if (s == '-')
			return 0;
	}

	char IsUnar(int i)
	{
		int j = i;
		if ((j == 0) || infix[j - 1] == '(' || IsOperator(infix[j - 1]))
			return '_';
		else return '-';

	}

	string NewInfix(string s)
	{
		string t;
		for (int i = 0; i < s.size(); i++)
		{
			if (!IsOperator(s[i]))
				t += s[i];
			else
				if (IsUnar(i) == '_')
					t += '_';
				else t += s[i];
		}
		return t;
	}
	string ToPostfix()
	{
		Stack<char> opers(infix.size());
		string tmp = NewInfix(infix);
		infix = tmp;
		int j = 0;
		for (int i = 0; i < infix.size(); i++)
		{
			for (int i = 0; i < infix.size(); i++)
			{
				if (!IsOperator(infix[i]) && infix[i] != '(' && infix[i] != ')')
				{
					if (infix[i] != ' ')
					{
						int j = i;
						while (!IsOperator(infix[j]) && j != infix.size() && infix[j] != ')' && infix[j] != ' ')
						{
							postfix += infix[j];
							j++;
						}
						i = j - 1;
						postfix += ',';
					}
				}
				else if (opers.IsEmpty() || opers.CheckTopEl() == '(')
					opers.Push(infix[i]);
				else if (Priority(infix[i]) >= Priority(opers.CheckTopEl()))
				{
					if (infix[i] == ')')
						goto metka1;
					else
						opers.Push(infix[i]);
				}
				else if (Priority(infix[i]) < Priority(opers.CheckTopEl()))
				{
					while ((!opers.IsEmpty()) && (opers.CheckTopEl() != '(' || (Priority(opers.CheckTopEl()) < Priority(infix[i]))))
					{
						postfix += opers.Pop();
						postfix += ',';
					}

					opers.Push(infix[i]);

				}

				else metka1:if (infix[i] == '(')

					opers.Push(infix[i]);

				else if (infix[i] == ')')

				{
					while (opers.CheckTopEl() != '(')
					{
						postfix += opers.Pop();
						postfix += ',';
					}
					opers.Pop();
				}
			}
			while (!opers.IsEmpty())
			{
				char t = opers.Pop();
				if (t != '(' && t != ')')
				{
					postfix += t;
					postfix += ',';
				}
			}
			return postfix;
		}
	}
	double count(double a, double b, char c)
	{
		double res;
		if (c == '+')
			res = a + b;
		if (c == '-')
			res = a - b;
		if (c == '*')
			res = a * b;
		if (c == '/')
		{
			if (b == 0) throw "impossible to divide by zero";
			res = a / b;
		}
		return res;
	}
	double Unar(double a)
	{
		return (-a);
	}
	double Calculator()
	{
		double res, k;
		Stack<double> nums(postfix.size());
		for (int i = 0; i < postfix.size(); i++)
		{
			if (postfix[i] == ',')
				goto metka;
			if (!IsOperator(postfix[i]))
			{
				string tmp;
				tmp += postfix[i];
				i++;
				while (postfix[i] != ',')
				{
					tmp += postfix[i];
					i++;
				}
				nums.Push(atof(tmp.c_str()));
			}
			else if (postfix[i] == '_')
			{
				double d = Unar(nums.Pop());
				nums.Push(d);
				i++;
			}
			else
			{
				k = nums.Pop();
				res = count(nums.Pop(), k, postfix[i]);
				nums.Push(res);
				i++;
			}
			}
		metka: return (nums.Pop());
		}
		bool Error()
		{

			bool res = true;
			int l = 0;
			Stack<char> x(infix.size());
			int t = 0;
			char brasc;
			if (infix.empty())
			{
				cout << " string is empty" << endl;
				return false;
			}

			else
			{
				if ((infix[0] == '+') || (infix[0] == '*') || (infix[0] == '/') || (infix[0] == ')') || (infix[0] == '.'))
				{
					res = false;
					cout << "wrong begin of expression" << endl;
				}

				if (IsOperator(infix[infix.size() - 1]) || (infix[infix.size() - 1] == '(') || (infix[infix.size() - 1] == '.'))
				{
					res = false;
					cout << "wrong end of expression" << endl;
				}
			}

			for (int i = 0; i < infix.size() - 2; i++)
			{
				if (infix[i] == '.')
				{
					if (isdigit(infix[i + 1]) == 0)
					{
						cout << "spelling error" << endl;
						res = false;
					}
				}
			}

			for (int i = 0; i < infix.size() - 2; i++)
			{
				if (infix[i] == ')')
				{

					if ((isdigit(infix[i + 1]) != 0) || (int(infix[i + 1]) >= 65 && int(infix[i + 1]) <= 90) || ((int(infix[i + 1]) >= 97 && int(infix[i + 1]) <= 122)) || (infix[i + 1] == '.'))
					{
						cout << "spelling error" << endl;
						res = false;
					}
				}
			}

			for (int i = 0; i < infix.size() - 2; i++)
			{
				if (infix[i] == '+' || infix[i] == '*' || infix[i] == '/')
				{
					if (infix[i + 1] == '+' || infix[i + 1] == '*' || infix[i + 1] == '/')
					{
						cout << "several operations in a row" << endl;
						res = false;
					}
				}
			}

			for (int i = 0; i < infix.size() - 2; i++)
			{
				if (infix[i] == '(')
				{
					if ((infix[i + 1] == ')') || (infix[i + 1] == '.'))
					{
						cout << "spelling error" << endl;
						res = false;
					}
				}
			}for (int i = 0; i < infix.size(); i++)
			{
				if (!((isdigit(infix[i]) != 0) || (infix[i] == ')') || (infix[i] == '(') || IsOperator(infix[i]) || (infix[i] == '.') || (infix[i] == ' ')))
				{
					cout << "invalid symbol on " << i + 1 << " position" << endl;
					res = false;
				}if (infix[i] == '(')
					x.Push('(');
				else
					if (infix[i] == ')')
					{
						if (!(x.IsEmpty()))
						{
							brasc = x.Pop();
						}

						else
						{
							t++;
						}

					}
			}

			if (t != 0)
			{
				res = false;
				cout << "error in brackets" << endl;
			}
			return res;
		}
};
#endif _ARITHMETIC_H