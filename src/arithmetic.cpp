// реализация функций и классов для вычисления арифметических выражений
#include "stack.h"
#include "arithmetic.h"
#include<string>
#include <cstdio>
#include <cstdlib>
#include <iostream>


using namespace std;


Lexeme::Lexeme(char _op, int _f)
{
	op = _op;
	flag = _f;
}
Lexeme::Lexeme(double _number, int _f)
{
	number = _number;
	flag = _f;
}

void Lexeme::Set(char _op, int _f)
{
	op = _op;
	flag = _f;
}
void Lexeme::Set(double _number, int _f)
{
	number = _number;
	flag = _f;
}
void Lexeme::Print()
{
	if (flag == 1)
		cout << '\n' << op;
	else
		cout << '\n' << number;

}

Lexeme& Lexeme::operator=(Lexeme & a) {
	number = a.number;
	op = a.op;
	flag = a.flag;
	return *this;
}

int prt(char _op) {
	int prt;
	switch (_op) {
	case'*':
	case':':
	case'/': prt = 3; break;
	case'+':
	case'-': prt = 2; break;
	case'=':prt = 1; break;
	default:prt = -1;
	}
	return prt;
}

Lexeme* Polish(string s, int & k) {
	k = 0;
	int l = 0;
	int m = 0;
	int n;
	int q;
	int g = 0;
	Lexeme *c;
	c = new Lexeme[size(s)];
	char *d;
	Stack<char> a(size(s));
	for (int i = 0; i < size(s); i++)
		if ((s[i] != '+') && (s[i] != '-') && (s[i] != '*') && (s[i] != '/') && (s[i] != '(') && (s[i] != ')') && (s[i] != ':')) {
			m = 0;
			for (int j = i; (j < size(s)) && (s[j] != '+') && (s[j] != '-') && (s[j] != '*') && (s[j] != '/') && (s[j] != '(') && (s[j] != ')'); j++)
				m++;
			d = new char[m + 1];
			for (int j = i, n = 0; j < i + m; j++, n++)
				d[n] = s[j];
			d[m] = { '\0' };
			double f = atof(d);
			for(int i=1;i<g;i++)
				f = -f;
			
			g = 0;
			c[k++].Set(f, 2);
			i += m - 1;
		}
		else {
			if (l == 0) {
				if ((s[i] == '-') && (i == 0))
					g = 2;
				else
				{
					a.Push(s[i]);
					l++;
					g++;
				}
			}
			else {
				if (s[i] == ')') {
					while (a.Value() != '(') {
						c[k++].Set(a.Pop(), 1);

					}
					a.Pop();
				}
				else {

					if ((prt(a.Value()) < prt(s[i])) || (s[i] == '(')) {
						if ((g == 0) || (s[i] == '('))
							a.Push(s[i]);
						if (s[i] != '(')
							g++;
					}
					else {
						if (g == 0) {
							while ((!a.IsEmpty()) && (prt(a.Value()) >= prt(s[i])) && (a.Value() != '(')) {

								c[k++].Set(a.Pop(), 1);

							}

							a.Push(s[i]);
						}
						else
							g++;
					}
				}

			}

		}

	while (!(a.IsEmpty()))
		c[k++].Set(a.Pop(), 1);
	
	return c;
}


double result(Lexeme *c, int k) {
	double res;
	Stack<double> a(k);
	for (int i = 0; i < k; i++) {
		if (c[i].Flag() == 2) {
			a.Push(c[i].Number());

		}

		else {
			double m = a.Pop();
			double l = a.Pop();
			switch (c[i].Op())
			{
			case '+':
				res = l + m;
				break;
			case '-':
				res = l - m;
				break;
			case '*':
				res = l * m;
				break;
			case ':':
			case '/':
				if (m != 0)
					res = l / m;
				else throw 1;
				break;

			}
			
			a.Push(res);
		}
	}
	if (k == 1)res = a.Pop();

	return res;
}



bool mistake(string s) {
	bool f = true;
	int g = 0;
	char b[19] = { '0','1','2','3','4','5','6','7','8','9','-','+','*','/',':','.',',','(',')' };
	for (int i = 0; i < size(s); i++) {
		for (int j = 0; j < 19; j++)
			if (s[i] == b[j]) {
				g++;
			}
		if (g == 0) {
			cout << '\n' << "The wrong symbol";
			f = false;
		}g = 0;
	}
	Stack<char> a(size(s));
	
	int t = 0;
	char br;
	for (int i = 0; i < size(s); i++)
	{
		if (s[i] == '(')
			a.Push('(');
		else
			if (s[i] == ')')
			{
				if (!(a.IsEmpty()))
				{
					br = a.Pop();
					
				}
				else
				{
					
					t++;
				}
			}
	}	if (t != 0) {
		f = false;
		cout << '\n' << "Wrong sequence of brackets";
	}



	for (int j = 11; j < 17; j++)
		if ((s[0] == b[j]) || (s[0] == ')')) {
			f = false;
			cout << '\n' << "A wrong begining of the expression";
		}
	for (int j = 10; j < 18; j++)
		if (s[size(s) - 1] == b[j]) {
			f = false;
			cout << '\n' << "A wrong end of the expression";
		}
	for (int i = 0; i < size(s); i++) {
		for (int j = 10; j < 19; j++)
			if (s[i] == b[j])
				if ((i + 1) < size(s)) {
					for (int l = 11; l < 16; l++)
						if (((s[i + 1] == b[l])||((s[i+1]=='-') &&(s[i + 2])=='(' ))&&(s[i]!=')')) {
							f = false;
							cout << '\n' << "This is not right sequence of symbols in the expression";
						}
						
				}
	}
	for (int i = 1; i < size(s); i++) {
		if (s[i] == '(') {
			for (int j = 10; j < 15; j++)
				if ((s[i - 1] == b[j]) || (s[i] == '(')) {
					g++;
				}

			if (g == 0) {
				f = false;
				cout << '\n' << "This is not right sequence of symbols in the expression";
			}
		}g = 0;
	}

	for (int i = 0; i < size(s) - 1; i++) {
		if (s[i] == ')') {
			for (int j = 10; j < 15; j++)
				if ((s[i + 1] == b[j]) || (s[i + 1] == ')')) {
					g++;
				}
			if (g == 0)
			{
				f = false;
				cout << '\n' << "This is not right sequence of symbols in the expression";
			}
		}g = 0;
	}

	return f;
}