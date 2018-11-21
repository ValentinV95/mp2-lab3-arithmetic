// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__

#include <string>
#include "stack.h"

using namespace std;

class TArithmetic
{
	string infix;
	string arithmetic;
public:
	TArithmetic(string str)
	{
		int ind1[255] = {}, k = 0, h = 0, j = 0, operand = 0;
		int ind2[255] = {};
		int ind3[255] = {};
		int ind4[255] = {};
		infix = str;
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == '(')
			{
				ind1[k++] = i;
				continue;
			}
			if (str[i] == ')')
			{
				ind2[j++] = i;
				continue;
			}
			if ((str[i] == '+') || (str[i] == '-') || (str[i] == '/') || (str[i] == '*'))
			{
				ind3[h++] = i;
			}
			else
			{
				ind4[operand] = i;
				operand++;
			}
		}
		if (j != k)
		{
			throw "wrong infix";
		}
		else
		{
			for (int g = 0; g < j; g++)
			{
				if (ind1[g] >= ind2[g])
				{
					throw "wrong infix";
				}
			}
		}
		int a = ind3[0];
		if ((operand - h) < 1)
		{
			throw "wrond infix";
		}
		for (int g = 1; g < h; g++)
		{
			if ((ind3[g] - a) <= 1)
			{
				throw "wrong infix";
			}
			a = ind3[g];
		}
		int a1 = ind4[0];
		for (int b = 1; b < operand; b++)
		{
			if ((ind4[b] - a1) == 1)
			{
				throw "wrong infix";
			}
			a1 = ind4[b];
		}
	}
	string GetInfix() { return infix; }
	string GetArithmetic() { return arithmetic; }
	string ToArithmetic();
	double Calculate(); // ¬вод переменных, вычисление по постфиксной форме
	int Priority(char c);
};

#endif