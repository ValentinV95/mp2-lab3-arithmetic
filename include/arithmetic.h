// объявление функций и классов для вычисления арифметических выражений

#ifndef _ARITHMETIC_H_
#define _ARITHMETIC_H_
#include <string>
#include <cmath>
#include "stack.h" 

class Lexem
{
private:
	double n;
	std::string op;
	bool chek;
public:
	Lexem() noexcept
	{

	}
	Lexem(double x) noexcept
	{
		n = x;
		chek = true;
	}
	Lexem(std::string s)
	{
		op = s;
		chek = false;
	}
	~Lexem() noexcept
	{

	}

	double getn() noexcept
	{
		return n;
	}

	std::string getop()
	{
		std::string s = "";
		s += op;
		return s;
	}

	bool is_num() noexcept
	{
		return chek;
	}

	bool is_op() noexcept
	{
		return !chek;
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
		else if (op == "sin") return 4;
		else if (op == "cos") return 4;
		else if (op == "ln") return 4;
		else if (op == "exp") return 4;
	}
	void operator= (double x)
	{
		n = x;
		chek = true;
	}
	void operator= (Lexem x)
	{
		if (x.is_num())
		{
			n = x.getn();
			chek = true;
		}
		else
		{
			op = x.getop();
			chek = false;
		}
	}
	void operator= (std::string x)
	{
		op = x;
		chek = false;
	}
};

double work(std::string s)
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
		else if ((s[i] == 's') && (s[i + 1] == 'i') && (s[i + 2] == 'n'))
		{
			if ((s[i + 3] == '('))
			{
				mas[j++] = "sin";
				i = i + 3;
			}
			else
				throw('missing or invalid argument')
		}
		else if ((s[i] == 'c') && (s[i + 1] == 'o') && (s[i + 2] == 's'))
		{
			if ((s[i + 3] == '('))
			{
				mas[j++] = "cos";
				i = i + 3;
			}
			else
				throw('missing or invalid argument')
		}
		else  if ((s[i] == 'l') && (s[i + 1] == 'n'))
		{
			if ((s[i + 2] == '('))
			{
				mas[j++] = "ln";
				i = i + 2;
			}
			else 
				throw('missing or invalid argument')
		}
		else  if ((s[i] == 'e') && (s[i + 1] == 'x') && (s[i + 2] == 'p'))
		{
			if (s[i + 3] == '(')
			{
				mas[j++] = "exp";
				i = i + 3;
			}
			else
				throw('missing or invalid argument')
		}
		else if (s[i] == 'x' && (s[i + 1] == '0'))
		{
			if (f1)
			{
				std::cout << "enter  x0" << std::endl;
				std::cin >> a0;
				f1 = false;
			}
			mas[j++] = a0;
			i = i + 2;
		}
		else if (s[i] == 'x' && (s[i + 1] == '1'))
		{
			if (f2)
			{
				std::cout << "enter  x1" << std::endl;
				std::cin >> a1;
				f2 = false;
			}
			mas[j++] = a1;
			i = i + 2;
		}
		else if (s[i] == 'x' && (s[i + 1] == '2'))
		{
			if (f3)
			{
				std::cout << "enter  x2" << std::endl;
				std::cin >> a2;
				f3 = false;
			}
			mas[j++] = a2;
			i = i + 2;
		}
		else if (s[i] == 'x' && (s[i + 1] == '3'))
		{
			if (f4)
			{
				std::cout << "enter  x3" << std::endl;
				std::cin >> a3;
				f4 = false;
			}
			mas[j++] = a3;
			i = i + 2;
		}
		else if (s[i] == 'x' && (s[i + 1] == '4'))
		{
			if (f5)
			{
				std::cout << "enter  x4" << std::endl;
				std::cin >> a4;
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

	if (cheking == 0)
	{
		std::cout << "GOOD" << std::endl;
		break;
	}
	else if ((cheking > 0) && (cheking < 9))
	{
		throw ("ERROR");
		std::cout << std::endl << "wrong symbol";
	}
	else
	{
		throw ("ERROR");
		std::cout << std::endl << "Unknown error";
	}
	
	switch (cheking(mas, j))
	{
	case 0:
	{
		std::cout << "GOOD" << std::endl;
		break;
	}
	case 1:
	{
		throw ("ERROR");
		std::cout << std::endl << "wrong symbol";
	}
	case 2:
	{
		throw ("ERROR");
		std::cout << std::endl << "wrong symbol";
	}
	case 3:
	{
		throw ("ERROR");
		std::cout << std::endl << "wrong symbol";
	}
	case 4:
	{
		throw ("ERROR");
		std::cout << std::endl << "wrong symbol";
	}
	case 5:
	{
		throw ("ERROR");
		std::cout << std::endl << "wrong symbol";
	}
	case 6:
	{
		throw ("ERROR");
		std::cout << std::endl << "wrong symbol";
	}
	case 7:
	{
		throw("ERROR");
		std::cout << std::endl << "wrong symbol";
	}
	case 8:
	{
		throw ("ERROR");
		std::cout << std::endl << "wrong symbol";
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
int cheking(Lexem* mas, int n)
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
				if ((mas[i + 1].is_op()) && ((mas[i + 1].getop() != "(") && (mas[i + 1].getop() != "sin") && (mas[i + 1].getop() != "cos") && (mas[i + 1].getop() != "ln") && (mas[i + 1].getop() != "exp") && (mas[i + 1].getop() != "un-")))
					return 2;
			}
			else if (mas[i].getop() == ")")
			{
				j--;
				if (i != n - 1)
					if ((mas[i + 1].is_num()) || ((mas[i + 1].getop() != "+") && (mas[i + 1].getop() != "-") && (mas[i + 1].getop() != "*") && (mas[i + 1].getop() != "/") && (mas[i + 1].getop() != ")")))
						return 3;
			}
			else if ((mas[i].getop() == "sin") || mas[i].getop() == "cos" || mas[i].getop() == "ln" || mas[i].getop() == "exp")
			{
				if (i == n - 1)
					return 7;
				else if (mas[i + 1].is_num() || (mas[i + 1].getop() != "("))
					return 8;
			}
			else
			{
				if (i == n - 1)
					return 7;
				else if ((mas[i + 1].is_op()) && ((mas[i + 1].getop() != "(") && (mas[i + 1].getop() != "un-") && (mas[i + 1].getop() != "cos") && (mas[i + 1].getop() != "sin") && (mas[i + 1].getop() != "ln") && (mas[i + 1].getop() != "exp")))
					return 4;
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
			if (mas[i].getop() == "sin")
			{
				x2 = (s.pop()).getn();
				t = sin(x2);
			}
			if (mas[i].getop() == "cos")
			{
				x2 = (s.pop()).getn();
				t = cos(x2);
			}
			if (mas[i].getop() == "ln")
			{
				x2 = (s.pop()).getn();
				t = log(x2);
			}
			if (mas[i].getop() == "exp")
			{
				x2 = (s.pop()).getn();
				t = exp(x2);
			}
			s.push(t);
		}
	}
	return (s.pop()).getn();
}
#endif _ARITHMETIC_H_