#pragma once
#ifndef _POLYNOM_H_
#define _POLYNOM_H_

#include <iostream>
#include <math.h>
#include "stack.h"

using namespace std;

struct Monom
{
	double coef;
	int deg;
	Monom* prev;
	Monom* next;
};




class Polynom

{

	Monom* fhead;
public:
	Polynom()
	{
		Monom* tmp = new Monom;
		tmp->coef = 0.0;
		tmp->deg = -1;
		tmp->next = nullptr;
		tmp->prev = nullptr;
		fhead = tmp;

	};

	Polynom(struct Monom* a, int N)
	{
		Monom* tmp = new Monom;
		tmp->coef = 0.0;
		tmp->deg = -1;
		tmp->next = nullptr;
		tmp->prev = nullptr;
		fhead = tmp;

		for (int i = 0; i < N; i++)
		{
			if ((a[i].deg < 0) || (a[i].deg > 999))
				throw "wrong degree";
			else Insert(a[i].coef, a[i].deg);
		}
	};

	Polynom(Polynom& A)
	{
		Monom* tmp1 = new Monom;
		tmp1->coef = 0.0;
		tmp1->deg = -1;
		tmp1->next = nullptr;
		tmp1->prev = nullptr;
		fhead = tmp1;

		Monom* tmp = A.fhead->next;
		while (tmp != nullptr)
		{
			Insert(tmp->coef, tmp->deg);
			tmp = tmp->next;
		}

	};

	bool Mistakes()
	{};

	void Insert(double _coef, int _deg)
	{
		if (_coef == 0.0)
			return;
		if ((_deg < 0) || (_deg > 999))
			throw "wrong degree value";
		if (fhead->next == nullptr)
		{
			Monom* tmp = new Monom;
			tmp->coef = _coef;
			tmp->deg = _deg;
			tmp->prev = fhead;
			tmp->next = nullptr;
			fhead->next = tmp;
		}
		else
		{
			Monom* tmp = fhead;
			while ((tmp->next != nullptr) && (tmp->next->deg > _deg))
				tmp = tmp->next;
			if (tmp->next == nullptr)
			{
				Monom* temp = new Monom;
				temp->coef = _coef;
				temp->deg = _deg;
				temp->prev = tmp;
				temp->next = nullptr;
				tmp->next = temp;
			}
			else
			{
				if (tmp->next->deg != _deg)
				{
					Monom* temp = new Monom;
					temp->deg = _deg;
					temp->coef = _coef;
					temp->next = tmp->next;
					temp->next->prev = temp;
					tmp->next = temp;
					temp->prev = tmp;
				}
				else
				{
					tmp->next->coef += _coef;
					if (tmp->next->coef == 0.0)
						Delete(_deg);
				}
			}
		}
	};



	void Delete(int _deg)
	{
		if ((_deg < 0) || (_deg > 999))
			throw "wrong degree value";
		Monom* tmp = fhead->next;
		if (tmp == nullptr)
			return;
		else
		{
			while ((tmp->next != nullptr) && ((tmp->deg) != _deg))
				tmp = tmp->next;
			if ((tmp->deg) == _deg)
			{
				if (tmp->next != nullptr) {
					tmp->prev->next = tmp->next;
					tmp->next->prev = tmp->prev;
					delete tmp;
				}
				else
				{
					tmp->prev->next = nullptr;
					delete tmp;
				}

			}


		}
	};



	bool IsEmpty()
	{
		if (fhead->next == nullptr)
			return true;
		else return false;
	};



	bool operator==(const Polynom& A) const
	{
		Monom* tmp = fhead->next;
		Monom* temp = A.fhead->next;
		while ((tmp != nullptr) && (temp != nullptr))
		{
			if (((tmp->coef) != (temp->coef)) || ((tmp->deg) != (temp->deg)))
				return false;
			tmp = tmp->next;
			temp = temp->next;
			if (((tmp != nullptr) && (temp == nullptr)) || ((tmp == nullptr) && (temp != nullptr)))
				return false;
		}
		return true;
	};



	Polynom& operator=(const Polynom& A)
	{
		if (fhead != A.fhead)
		{
			while (fhead->next != nullptr)
				Delete(fhead->next->deg);
			Monom* tmp = A.fhead->next;
			while (tmp != nullptr)
			{
				Insert(tmp->coef, tmp->deg);
				tmp = tmp->next;
			}
		}
		return *this;
	};



	Polynom operator+(Polynom& A)
	{
		Polynom C;
		Monom* tmp = fhead->next;
		Monom* temp = A.fhead->next;
		while ((tmp != nullptr) && (temp != nullptr))
		{
			if (tmp->deg < temp->deg)
			{
				C.Insert(temp->coef, temp->deg);
				temp = temp->next;
			}
			else
			{
				C.Insert(tmp->coef, tmp->deg);
				tmp = tmp->next;
			}
		}
		while (tmp != nullptr)
		{
			C.Insert(tmp->coef, tmp->deg);
			tmp = tmp->next;
		}
		while (temp != nullptr)
		{
			C.Insert(temp->coef, temp->deg);
			temp = temp->next;
		}
		return C;
	};



	Polynom operator-(Polynom& A)
	{
		Polynom C;
		C = A * (-1);
		C = C + *this;
		return C;
	};



	Polynom operator*(double a)
	{
		Polynom C(*this);
		Monom* tmp = C.fhead->next;
		while (tmp != nullptr)
		{
			tmp->coef = a * tmp->coef;
			tmp = tmp->next;
		}
		return C;

	};



	Polynom operator*(Polynom& A)
	{
		Polynom C;
		int d, d1, d2, d3;
		Monom* tmp = fhead->next;
		Monom* temp = A.fhead->next;
		while (temp != nullptr)
		{
			d1 = ((int)temp->deg) / 100 + ((int)temp->deg) / 10 + ((int)temp->deg) % 100;
			while (tmp != nullptr)
			{
				d2 = ((int)tmp->deg) / 100 + ((int)tmp->deg) / 10 + ((int)tmp->deg) % 100;
				d = d1 + d2;
				d3 = ((int)(temp->deg + tmp->deg)) / 100 + ((int)(temp->deg + tmp->deg)) / 10 + ((int)(temp->deg + tmp->deg)) % 100;
				if (d != d3)
					throw "degrees > 9";
				else
					C.Insert(temp->coef * tmp->coef, temp->deg + tmp->deg);
				tmp = tmp->next;
			}
			temp = temp->next;
		}
		return C;
	};

	friend ostream& operator<<(ostream& out, Polynom& A)
	{
		int l = 0;
		Monom* temp = A.fhead->next;
		while (temp != nullptr) {
			if (temp->coef != 0)
				out << temp->coef;

			if ((int)temp->deg / 100 != 0)
				out << "x^" << temp->deg / 100;

			if ((int)temp->deg % 100 / 10 != 0)
				out << "*y^" << temp->deg % 100 / 10;

			if (temp->deg % 10 != 0)
				out << "*z^" << temp->deg % 10;
			temp = temp->next;
			l = 1;
		}

		if (l == 0) out << "0";
		return out;

	};

	friend istream& operator>>(istream& in, Polynom& A)
	{
		int k;
		cout << "Input number of monoms: ";
		in >> k;
		Monom* poly;

		poly = new Monom[k];
		for (int i = 0; i < k; i++) {
			int x = -1, y = -1, z = -1;
			cout << "Input a monom coefficient: ";
			in >> poly[i].coef;
			while ((x < 0) || (x > 9)) {
				cout << "Input a degree of x: ";
				in >> x;
			}

			while ((y < 0) || (y > 9)) {
				cout << "Input a degree of y: ";
				in >> y;
			}

			while ((z < 0) || (z > 9)) {
				cout << "Input a degree of z: ";
				in >> z;
			}

			poly[i].deg = x * 100 + y * 10 + z;
		}

		Polynom B(poly, k);
		A = B;
		return in;
	};

	~Polynom()
	{
		while (fhead->next != nullptr)
		{
			Delete(fhead->next->deg);
		}
		delete fhead;
	};
};
/*class Arithmetic {
private:
	string infix;
	string postfix;
public:
	Arithmetic(string s);
	bool isop(char s);
	int priority(char s);
	char Unar(int i);
	string newinfix(string s);
	string ToPostfix();
	double count(double a, double b, char c);
	double perevodUn(double a);
	double Calculator();
	bool Error();
};*/
class Arithmetic
{
private:
	string infix;
	string postfix;

public:
	Arithmetic(string s)
	{
		infix = s;
	}
	bool isop(char s)
	{
		if (s == '+' || s == '*' || s == '-' || s == '/' || s == '_')
			return true;
		else return false;
	}
	int priority(char s)
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
	char Unar(int i)
	{
		int j = i;
		if ((j == 0) || infix[j - 1] == '(' || isop(infix[j - 1]))
			return '_';
		else return '-';
	}
	string newinfix(string s)
	{
		string t;
		for (int i = 0; i < s.size(); i++)
		{
			if (!isop(s[i]))
				t += s[i];
			else if (Unar(i) == '_')
				t += s[i];
			else t += s[i];
		}
		return t;
	}
	string ToPostfix()
	{
		Stack<char> opers(infix.size());
		string tmp = newinfix(infix);
		infix = tmp;
		int j = 0;
		for (int i = 0; i < infix.size(); i++)
		{
			if (!isop(infix[i]) && infix[i] != '(' && infix[i] != ')')
			{
				if (infix[i] != ' ')
				{
					int j = i;
					while (!isop(infix[j]) && j != infix.size() && infix[j] != ')' && infix[j] != ' ')
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

			else if (priority(infix[i]) >= priority(opers.CheckTopEl()))
				opers.Push(infix[i]);

			else if (priority(infix[i]) < priority(opers.CheckTopEl()))
			{
				while ((!opers.IsEmpty()) && (opers.CheckTopEl() != '(' || (priority(opers.CheckTopEl()) < priority(infix[i]))))
				{
					postfix += opers.Pop();
					postfix += ',';
				}
				opers.Push(infix[i]);
			}
			else if (infix[i] == '(')
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
			if (b == 0) throw "divide by zero";
			res = a / b;
		}
		return res;
	}
	double perevodUn(double a)
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
			if (!isop(postfix[i]))
			{
				string tmp;
				tmp += postfix[i];
				i++;
				while (postfix[i] != ',')
				{
					tmp += postfix[i];
					i++;
				}
				nums.Push(atof(tmp.c_str())); // atof из string в double
			}
			else if (postfix[i] == '_')
			{
				double d = perevodUn(nums.Pop());
				nums.Push(d);
				i++;
			}
			else
			{
				k = nums.Pop();
				res = count(nums.Pop(), k, postfix[i]);
				res = count(nums.Pop(), k, postfix[i]);
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
			cout << "string is empty" << endl;
			return false;
		}
		else
		{
			if ((infix[0] == '+') || (infix[0] == '*') || (infix[0] == '/') || (infix[0] == ')') || (infix[0] == '.'))
			{
				res = false;
				cout << "Wrong begin" << endl;
			}
		}if (isop(infix[infix.size() - 1]) || (infix[infix.size() - 1] == '(') || (infix[infix.size() - 1] == '.'))
		{
			res = false;
			cout << "Wrong end" << endl;
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
				if ((isdigit(infix[i + 1]) != 0) || (infix[i + 1] == '.'))
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
		}
		for (int i = 0; i < infix.size(); i++)
		{
			if (!((isdigit(infix[i]) != 0) || (infix[i] == ')') || (infix[i] == '(') || isop(infix[i]) || (infix[i] == '.') || (infix[i] == ' ')))
			{
				cout << "invalid symbol on " << i + 1 << "position" << endl;
				res = false;
			}
			if (infix[i] == '(')
				x.Push('(');
			else if (infix[i] == ')')
			{
				if (!(x.IsEmpty()))
				{
					brasc = x.Pop();
				}
				else
					t++;
			}
			if (t != 0)
			{
				res = false;
				cout << "Error with brackets" << endl;
			}
		}
		return res;
	}


};
#endif _POLYNOM_H_