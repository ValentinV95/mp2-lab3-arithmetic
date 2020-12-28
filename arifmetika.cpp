
#include <string>
#include <cmath>
#include "Tstack.h"
#include <iostream>
using namespace std;
class Lexem
{
private:
	double n;
	string op;
	bool check;
public:
	Lexem() noexcept
	{

	}
	Lexem(double x) noexcept
	{
		n = x;
		check = true;
	}
	Lexem(string s)
	{
		op = s;
		check = false;
	}
	~Lexem() noexcept
	{

	}

	double getn() noexcept
	{
		return n;
	}

	string getop()
	{
		string s = "";
		s += op;
		return s;
	}

	bool is_num() noexcept
	{
		return check;
	}

	bool is_op() noexcept
	{
		return !check;
	}

	int priority()
	{
		if (op == ")")  return 0;
		else if (op == "(") return 1;
		else if (op == "-") return 2;
		else if (op == "+") return 2;
		else if (op == "*") return 3;
		else if (op == "/") return 3;
		else if (op == "un-") return 4;
	}
	void operator= (double x)
	{
		n = x;
		check = true;
	}
	void operator= (Lexem x)
	{
		if (x.is_num())
		{
			n = x.getn();
			check = true;
		}
		else
		{
			op = x.getop();
			check = false;
		}
	}
	void operator= (string x)
	{
		op = x;
		check = false;
	}
};

double work(string s)
{
	int i = 0, j = 0;
	double tmp, x, d, a0, a1, a2, a3, a4;
	Lexem mas[100];
	bool f1 = true, f2 = true, f3 = true, f4 = true, f5 = true;
	if (s[i] == '-')
	{
		mas[j++] = -1;
		mas[j++] = "*";
		i++;
	}
	while (s[i] != '\0')
	{
		if ((s[i] >= '0') && (s[i] <= '9')) {
			x = 0;
			d = 10;
			while ((s[i] >= '0') && (s[i] <= '9'))
			{
				tmp = (double)(s[i] - '0');
				x = x * 10 + tmp;
				i++;
			}
			if (s[i] == '.') {
				i++;
				while ((s[i] >= '0') && (s[i] <= '9'))
				{
					if ((s[i] >= '0') && (s[i] <= '9')) {
						tmp = (double)(s[i] - '0');

						x = x + tmp / d;
						i++;
						d = d * 10;
					}
				}
			}
			mas[j] = x;
			j++;
		}
		
		else if (s[i] == 'x' && (s[i + 1] == '0'))
		{
			if (f1)
			{
				cout<< "enter  x0" << endl;
				cin >> a0;
				f1 = false;
			}
			mas[j++] = a0;
			i = i + 2;
		}
		else if (s[i] == 'x' && (s[i + 1] == '1'))
		{
			if (f2)
			{
				cout<< "enter  x1" << endl;
				cin >> a1;
				f2 = false;
			}
			mas[j++] = a1;
			i = i + 2;
		}
		else if (s[i] == 'x' && (s[i + 1] == '2'))
		{
			if (f3)
			{
				cout << "enter  x2" << endl;
				cin >> a2;
				f3 = false;
			}
			mas[j++] = a2;
			i = i + 2;
		}
		else if (s[i] == 'x' && (s[i + 1] == '3'))
		{
			if (f4)
			{
				cout << "enter  x3" << endl;
				cin >> a3;
				f4 = false;
			}
			mas[j++] = a3;
			i = i + 2;
		}
		else if (s[i] == 'x' && (s[i + 1] == '4'))
		{
			if (f5)
			{
				cout << "enter  x4" << endl;
				cin >> a4;
				f5 = false;
			}
			mas[j++] = a4;
			i = i + 2;
		}
		else  if (s[i] == '+')
		{
			mas[j] = "+";
			j++;
			i++;
		}
		else  if (s[i] == '*')
		{
			mas[j] = "*";
			j++;
			i++;
		}
		else  if (s[i] == '/')
		{
			mas[j] = "/";
			j++;
			i++;
		}
		else if (s[i] == '-')
		{
			if (mas[j - 1].is_op() && mas[j - 1].getop() != ")")
			{
				mas[j++] = "un-";
				i++;
			}
			else
			{
				mas[j] = "-";
				j++;
				i++;
			}
		}
		else if (s[i] == '(')
		{
			mas[j] = "(";
			j++;
			i++;
		}
		else if (s[i] == ')')
		{
			mas[j] = ")";
			j++;
			i++;
		}
		else
		{
			throw ("ERROR");
		}
	}
	switch (checking(mas, j))
	{
	case 0:
	{
		cout << "GOOD" << endl;
		break;
	}
	case 1:
	{
		throw ("ERROR");
		cout << endl << "wrong symbol";
	}
	case 2:
	{
		throw ("ERROR");
		cout << endl << "wrong symbol";
	}
	case 3:
	{
		throw ("ERROR");
		cout << endl << "wrong symbol";
	}
	case 4:
	{
		throw ("ERROR");
		cout << endl << "wrong symbol";
	}
	case 5:
	{
		throw ("ERROR");
		cout << endl << "wrong symbol";
	}
	case 6:
	{
		throw ("ERROR");
		cout << endl << "wrong symbol";
	}
	case 7:
	{
		throw("ERROR");
		cout << endl << "wrong symbol";
	}
	case 8:
	{
		throw ("ERROR");
		cout << endl << "wrong symbol";
	}

	}

	Lexem* mas1;
	mas1 = new Lexem[j];
	TStack<Lexem> t;
	int l = 0;

	for (int k = 0; k < j; k++)
	{
		if (mas[k].is_num())
		{
			mas1[l] = mas[k];
			l++;
		}
		else
			if (t.isempty())
			{
				t.push(mas[k]);
			}
			else
			{
				if (mas[k].priority() == 1)
				{
					t.push(mas[k]);
				}
				else
				{
					while (!(t.isempty()) && (mas[k].priority() <= t.show().priority()))
					{
						if (t.show().priority() == 1)
						{
							t.pop();
							break;
						}
						else
						{
							mas1[l] = t.pop();
							l++;
						}
					}
					if (mas[k].priority() != 0)
					{
						t.push(mas[k]);
					}
				}
			}
	}
	while (!(t.isempty()))
	{
		mas1[l] = t.pop();
		l++;
	}
	return find_des(mas1, l);
}
int checking(Lexem* mas, int n)
{
	int j = 0;
	for (int i = 0; i < n; i++) {
		if (mas[i].is_num()) {
			if (i != n - 1) {
				if ((mas[i + 1].getop() != "+") && (mas[i + 1].getop() != "-") && (mas[i + 1].getop() != "*") && (mas[i + 1].getop() != "/") && (mas[i + 1].getop() != ")")) { return 1; }
			}
		}
		else {

			if (mas[i].getop() == "(")
			{
				j++;
				if (i == n - 1)
					return 7;
			}
			else if (mas[i].getop() == ")")
			{
				j--;
				if (i != n - 1)
					if ((mas[i + 1].is_num()) || ((mas[i + 1].getop() != "+") && (mas[i + 1].getop() != "-") && (mas[i + 1].getop() != "*") && (mas[i + 1].getop() != "/") && (mas[i + 1].getop() != ")")))
						return 3;
			}
			else
			{
				if (i == n - 1)
					return 7;
			}
			if (j < 0)
				return 5;
		}
	}
	if (j != 0)
		return 6;
	return 0;
}
double find_des(Lexem* mas, int n)
{
	TStack<Lexem> s;
	Lexem t;
	double x1, x2;
	for (int i = 0; i < n; i++)
	{
		if (mas[i].is_num())
		{
			s.push(mas[i]);
		}
		else
		{
			if (mas[i].getop() == "+")
			{
				x2 = (s.pop()).getn();
				x1 = (s.pop()).getn();
				t = x1 + x2;
			}
			if (mas[i].getop() == "-")
			{
				x2 = (s.pop()).getn();
				x1 = (s.pop()).getn();
				t = x1 - x2;
			}
			if (mas[i].getop() == "*")
			{
				x2 = (s.pop()).getn();
				x1 = (s.pop()).getn();
				t = x1 * x2;
			}
			if (mas[i].getop() == "/")
			{
				x2 = (s.pop()).getn();
				x1 = (s.pop()).getn();
				t = x1 / x2;
			}
			if (mas[i].getop() == "un-")
			{
				x2 = (s.pop()).getn();
				t = -1 * x2;
			}
			s.push(t);
		}
	}
	return (s.pop()).getn();
}