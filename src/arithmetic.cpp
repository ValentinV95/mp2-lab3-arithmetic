// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"
#include <cstdlib>

Lexem::Lexem(char operation1, int k1)
{
	IsOper = operation1;
	k = k1;
}

Lexem::Lexem(double number1, int k1)
{
	IsNum = number1;
	k = k1;
}

void Lexem::set(char operation1, int k1)
{
	IsOper = operation1;
	k = k1;
}

void Lexem::set(double number1, int k1)
{
	IsNum = number1;
	k = k1;
}

int Lexem::sign()
{
	return k;
}

double Lexem::number()
{
	return IsNum;
}

char Lexem::operation()
{
	return IsOper;
}

int priority(char operation)
{
	int res = 0;
	switch (operation)
	{
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

Lexem* PolishRecord(string stroka, int& k)
{
	k = 0;
	int a = 0;
	int b = 0;
	int ñ = 0;
	double e;
	char* tmp;
	Lexem* x;
	x = new Lexem[size(stroka)];
	Stack<char> stc(size(stroka));
	for (int i = 0; i < size(stroka); i++)
		if ((stroka[i] != '+') && (stroka[i] != '-') && (stroka[i] != '*') && (stroka[i] != '/') && (stroka[i] != '(') && (stroka[i] != ')')) {
			b = 0;
			for (int j = i; (j < size(stroka)) && (stroka[j] != '+') && (stroka[j] != '-') && (stroka[j] != '*') && (stroka[j] != '/') && (stroka[j] != '(') && (stroka[j] != ')'); j++)
				b++;
			tmp = new char[b + 1];
			for (int j = i, n = 0; j < i + b; j++, n++)
				tmp[n] = stroka[j];
			tmp[b] = { '\0' };
			e = atof(tmp);
			for (int i = 1; i < ñ; i++)
				e = -e;
			ñ = 0;
			x[k++].set(e, 2);
			i += b - 1;
		}
		else
		{
			if (a == 0)
			{
				if ((stroka[i] == '-') && (i == 0))
				{
					ñ = 2;
				}

				else
				{
					stc.push(stroka[i]);
					a++;
					ñ++;
				}
			}
			else
			{
				if (stroka[i] == ')')
				{
					while (stc.Front() != '(')
					{
						x[k++].set(stc.pop(), 1);
					}
					stc.pop();
				}
				else
				{
					if ((stc.IsEmpty() == false) && ((priority(stc.Front()) < priority(stroka[i])) || (stroka[i] == '('))) {
						if ((ñ == 0) || (stroka[i] == '('))
							stc.push(stroka[i]);
						if (stroka[i] != '(')
							ñ++;
					}
					else
					{
						if (ñ == 0) {
							while ((stc.IsEmpty() == false) && (stc.Front() != '('))
							{
								x[k++].set(stc.pop(), 1);
							}
							stc.push(stroka[i]);
						}
						else
							ñ++;
					}
				}
			}
		}
	while (stc.IsEmpty() == false)
		x[k++].set(stc.pop(), 1);
	return x;
}

double result(Lexem* x, int k)
{
	Stack <double> stc(k);
	double res;
	for (int i = 0; i < k; i++)
	{
		if (x[i].sign() == 2)
		{
			stc.push(x[i].number());
		}
		else
		{
			double a = stc.pop();
			double b = stc.pop();
			switch (x[i].operation())
			{
			case '+':
				res = b + a;
				break;
			case '-':
				res = b - a;
				break;
			case '*':
				res = b * a;
				break;
			case '/':
				if (a != 0)
					res = b / a;
				else throw 1;
				break;
			}
			stc.push(res);
		}
	}
	if (k == 1)
		res = stc.pop();
	return res;
}

bool errors(string stroka)
{
	bool a = true;
	int b = 0;
	Stack <char> stc(size(stroka));
	int t = 0;
	char br;
	char c[17] = { '0','1','2','3','4','5','6','7','8','9','-','+','*','/','.','(',')' };
	for (int i = 0; i < size(stroka); i++)
	{
		for (int j = 0; j < 17; j++)
			if (stroka[i] == c[j])
			{
				b++;
			}
		if (b == 0)
		{
			cout << endl << "The symbol is wrong";
			a = false;
		}
		b = 0;
	}
	for (int i = 0; i < size(stroka); i++)
	{
		if (stroka[i] == '(')
			stc.push('(');
		else
			if (stroka[i] == ')')
			{
				if (stc.IsEmpty() == false)
					br = stc.pop();
				else
					t++;
			}
	}
	if (t != 0)
	{
		a = false;
		cout << endl << "Brackets are wrong";
	}
	for (int j = 11; j < 15; j++)
		if ((stroka[0] == c[j]) || (stroka[0] == ')'))
		{
			a = false;
			cout << endl << "The expression starts with a wrong symbol";
		}
	for (int j = 10; j < 16; j++)
		if (stroka[size(stroka) - 1] == c[j])
		{
			a = false;
			cout << endl << "The expression ends with a wrong symbol";
		}
	for (int i = 0; i < size(stroka); i++)
	{
		for (int j = 10; j < 17; j++)
			if (stroka[i] == c[j])
				if ((i + 1) < size(stroka))
				{
					for (int l = 11; l < 15; l++)
						if (((stroka[i + 1] == c[l]) || ((stroka[i + 1] == '-') && (stroka[i + 2]) == '(')) && (stroka[i] != ')')) {
							a = false;
							cout << endl << "Sequence of symbols is wrong";
						}
				}
	}
	for (int i = 1; i < size(stroka); i++)
	{
		if (stroka[i] == '(')
		{
			for (int j = 10; j < 14; j++)
				if ((stroka[i - 1] == c[j]) || (stroka[i - 1] == '(')) {
					b++;
				}
			if (b == 0)
			{
				a = false;
				cout << endl << "Sequence of symbols is wrong";
			}
		}b = 0;
	}
	for (int i = 0; i < size(stroka) - 1; i++)
	{
		if (stroka[i] == ')')
		{
			for (int j = 10; j < 14; j++)
				if ((stroka[i + 1] == c[j]) || (stroka[i + 1] == ')'))
				{
					b++;
				}
			if (b == 0)
			{
				a = false;
				cout << endl << "Sequence of symbols is wrong";
			}
		}
		b = 0;
	}
	return a;
}