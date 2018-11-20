
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <map>
#include <set>
#include "arithmetic.h"
#include "stack.h"

Calculate::Calculate(const std::string& inp)
{
	input = inp;
	lex = new Lexem[inp.size()];
	size = 0;
	Razb();
}

bool Calculate::is_op(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

bool Calculate::delim(char c)
{
	return c == ' ';
}

bool Calculate::is_function(const std::string &c)
{
	return c == "sin" || c == "cos" || c == "tan" || c == "arctan" || c == "log" || c == "sqrt";
}

bool Calculate::is_digit(char c)
{
	if (c >= '0' && c <= '9') return true;
	else return false;
}

double Calculate::val_func(std::string temp, double ans , int i)
{

	if (temp == "sin")
	{
		return sin(ans);
	}
	else if (temp == "cos")
	{
		return cos(ans);
	}
	else if (temp == "tan")
	{
		return tan(ans);
	}
	else if (temp == "arctan")
	{
		return atan(ans);
	}
	else if (temp == "log")
	{
		if (ans <= 0)
		{
			std::pair<std::string, int> error = { "scope not met", i };
			throw(error);
		}
		return log(ans);
	}
	else
	{
		if (ans < 0)
		{
			std::pair<std::string, int> error = {"scope not met", i};
			throw(error);
		}
		return sqrt(ans);
	}
}

bool Calculate::Prover1()
{
	for (int i = 0; i < size; i++)
	{
		if (lex[i].tp == WR)
		{
			std::pair<std::string, int> error = { "invalid_character ", lex[i].pos };
			throw(error);
		}
	}
	for (int i = 0; i < size; i++)
	{
		if (lex[i].tp == VALUE)
		{
			int temp = 0;
			int posi = 0;
			for (unsigned j = 0; j < lex[i].s.size(); j++)
			{
				if (lex[i].s[j] == '.')
				{
					temp++;
					posi = lex[i].pos;
				}
			}
			if (temp > 1)
			{
				std::pair<std::string, int> error = {"too many points", posi };
				throw(error);
			}
		}
	}
	return true;
}

bool Calculate::Prover2()
{
	Stack <std::pair<char, int>> temp(size);
	for (int i = 0; i < size; i++)
	{
		if (lex[i].tp == OB)
		{
			temp.push(std::make_pair('(', lex[i].pos));
		}
		else if (lex[i].tp == CB)
		{
			if (!temp.IsEmpty())
			{
				temp.pop();
			}
			else
			{
				std::pair<std::string, int> error = {"not enough open bracket", lex[i].pos};
				throw(error);
			}
		}
	}
	if (!temp.IsEmpty())
	{
		std::pair<std::string, int> error = { "too many close bracket", temp.front().second };
		throw(error);
	}
	return true;
}

bool Calculate::Prover3()
{
	if (lex[0].tp == OP && lex[0].s[0] != '-')
	{
		std::pair<std::string, int> error = { "Incorect input", lex[0].pos };
		throw(error);
	}
	for (int i = 0; i < size - 1; i++)
	{
		if (lex[i].tp == VALUE && lex[i + 1].tp == VALUE)
		{
			std::pair<std::string, int> error = { "Incorect input", lex[i].pos };
			throw(error);
		}
		else if (lex[i].tp == VALUE && lex[i + 1].tp == OB)
		{
			std::pair<std::string, int> error = { "Incorect input", lex[i].pos };
			throw(error);;
		}
		else if (lex[i].tp == CB && lex[i + 1].tp == VALUE)
		{
			std::pair<std::string, int> error = { "Incorect input", lex[i].pos };
			throw(error);
		}
		else if (lex[i].tp == OB && lex[i + 1].tp == OP && lex[i + 1].s[0] != '-')
		{
			std::pair<std::string, int> error = { "Incorect input", lex[i].pos };
			throw(error);
		}
		else if (lex[i].tp == OB && lex[i + 1].tp == CB)
		{
			std::pair<std::string, int> error = { "Incorect input", lex[i].pos };
			throw(error);
		}
		else if (lex[i].tp == OP && lex[i + 1].tp == CB)
		{
			std::pair<std::string, int> error = { "Incorect input", lex[i].pos };
			throw(error);
		}
		else if (lex[i].tp == OP && lex[i + 1].tp == OP)
		{
			if (lex[i].s[0] == '-' && lex[i + 1].s[0] == '-')
			{
				continue;
			}
			else if (lex[i].tp == OP && lex[i + 1].s[0] == '-')
			{
				continue;
			}
			else
			{
				std::pair<std::string, int> error = { "Incorect input", lex[i].pos };
				throw(error);
			}
		}
		else if (lex[i].tp == Perem && lex[i + 1].tp == OB)
		{
			std::pair<std::string, int> error = { "Incorect input", lex[i].pos };
			throw(error);
		}
		else if (lex[i].tp == CB && lex[i + 1].tp == Perem)
		{
			std::pair<std::string, int> error = { "Incorect input", lex[i].pos };
			throw(error);
		}
		else if (lex[i].tp == Perem && lex[i + 1].tp == FUNC)
		{
			std::pair<std::string, int> error = { "Incorect input", lex[i].pos };
			throw(error);
		}
		else if (lex[i].tp == FUNC && lex[i + 1].tp == Perem)
		{
			std::pair<std::string, int> error = { "Incorect input", lex[i].pos };
			throw(error);
		}
		else if (lex[i].tp == VALUE && lex[i + 1].tp == FUNC)
		{
			std::pair<std::string, int> error = { "Incorect input", lex[i].pos };
			throw(error);
		}
		else if (lex[i].tp == FUNC && lex[i + 1].tp == VALUE)
		{
			std::pair<std::string, int> error = { "Incorect input", lex[i].pos };
			throw(error);
		}
		else if (lex[i].tp == VALUE && lex[i + 1].tp == Perem)
		{
			std::pair<std::string, int> error = { "Incorect input", lex[i].pos };
			throw(error);
		}
		else if (lex[i].tp == Perem && lex[i + 1].tp == VALUE)
		{
			std::pair<std::string, int> error = { "Incorect input", lex[i].pos };
			throw(error);
		}
	}
	if (lex[size - 1].tp == OP)
	{
		std::pair<std::string, int> error = { "Incorect input", lex[size - 1].pos };
		throw(error);
	}
	return true;
}

void Calculate::Razb()
{
	for (unsigned i = 0; i < input.size(); i++)
	{
		char v = input[i];
		if (delim(v)) continue;
		if (is_op(v))
		{
			if (v == '-' && i == 0)
			{
				lex[size].tp = OP;
				lex[size].s = v;
				lex[size].may_unary = true;
				lex[size].pos = i;
				++size;
			}
			else if (v == '-' && (lex[size - 1].tp == OP || lex[size - 1].tp == OB))
			{
				lex[size].tp = OP;
				lex[size].s = v;
				lex[size].may_unary = true;
				lex[size].pos = i;
				++size;
			}
			else {
				lex[size].tp = OP;
				lex[size].s = v;
				lex[size].may_unary = false;
				lex[size].pos = i;
				++size;
			}
		}
		else if (v == '(')
		{
			lex[size].tp = OB;
			lex[size].may_unary = false;
			lex[size].pos = i;
			++size;
		}
		else if (v == ')')
		{
			lex[size].tp = CB;
			lex[size].may_unary = false;
			lex[size].pos = i;
			++size;
		}
		else if (is_digit(v))
		{
			unsigned j = i;
			std::string temp;
			while (j < input.size())
			{
				if (is_digit(input[j]) || input[j] == '.')
				{
					temp += input[j];
					j++;
				}
				else
				{
					break;
				}
			}
			i = j - 1;
			lex[size].s = temp;
			lex[size].tp = VALUE;
			lex[size].pos = i;
			lex[size].may_unary = false;
			++size;
		}
		else
		{
			unsigned j = i;
			std::string temp;
			while (j < input.size())
			{
				if (input[j] >= 'a' && input[j] <= 'z')
				{
					temp += input[j];
					j++;
				}
				else
				{
					break;
				}
			}
			if (is_function(temp))
			{
				lex[size].tp = FUNC;
				lex[size].may_unary = true;
				lex[size].pos = i;
				lex[size].s = temp;
				i = j - 1;
				++size;
			}
			else if (temp.size() == 1)
			{
				lex[size].s = temp;
				lex[size].may_unary = false;
				lex[size].tp = Perem;
				lex[size].pos = i;
				++size;
			}
			else {
				lex[size].tp = WR;
				lex[size].may_unary = false;
				lex[size].pos = i;
				++size;
			}
		}
	}
}

int Calculate::priority(char op)
{
	return
		op == '+' || op == '-' || op == 'l' || op == 's' || op == 'a' || op == 't' || op == 'c' ? 1 :
		op == '*' || op == '/' ? 2 :
		-1;
}

void Calculate::PerevodVPol()
{
	Stack <Lexem> s(size);
	Stack <Lexem> s1(size);
	for (int i = 0; i < size; i++)
	{
		Lex_Type t = lex[i].tp;
		if (t == VALUE)
		{
			s1.push(lex[i]);
		}
		else if (t == CB)
		{
			while (s.front().tp != OB)
			{
				s1.push(s.front());
				s.pop();
			}
			s.pop();
		}
		else if (t == FUNC)
		{
			s.push(lex[i]);
		}
		else if (t == Perem)
		{
			s.push(lex[i]);
		}
		else
		{
			if (s.IsEmpty())
			{
				s.push(lex[i]);
			}
			else if (lex[i].may_unary)
			{
				s.push(lex[i]);
			}
			else
			{
				char a = lex[i].s[0], b = s.front().s[0];
				if (lex[i].tp == OB || lex[i].tp == CB || s.front().tp == OB || s.front().tp == CB)
				{
					s.push(lex[i]);
					continue;
				}
				while (priority(a) <= priority(b))
				{
					s1.push(s.front());
					if (s.IsEmpty())
					{
						break;
					}
					s.pop();
					if (s.IsEmpty())
					{
						break;
					}
					b = s.front().s[0];
				}
				s.push(lex[i]);
			}
		}
	}
	while (!s.IsEmpty())
	{
		s1.push(s.front());
		s.pop();
	}
	int i = s1.size_stack() - 1;
	size = i + 1;
	while (!s1.IsEmpty())
	{
		lex[i] = s1.front();
		s1.pop();
		--i;
	}
}

double Calculate::oper(double a, double b, char t, int i)
{
	if (t == '-') return a - b;
	else if (t == '+') return a + b;
	else if (t == '/')
	{
		if (b == 0)
		{
			std::pair<std::string, int> error = { "Divide by 0", i};
			throw(error);
		}
		else
		{
			return a / b;
		}
	}
	else  return a*b;
}

double Calculate::calc()
{
	std::map<std::string, int> perem;
	std::set<std::string> was;
	Prover1();
	Prover2();
	Prover3();
	PerevodVPol();
	Stack <double> calculate(size);
	for (int i = 0; i < size; i++)
	{
		Lex_Type v = lex[i].tp;
		if (v == VALUE)
		{
			std::stringstream temp;
			temp << lex[i].s;
			double ans;
			temp >> ans;
			calculate.push(ans);
		}
		else if (v == Perem)
		{
			if (was.find(lex[i].s) == was.end())
			{
				std::cout << "Enter the variable value " << lex[i].s << " : ";
				double x;
				std::cin >> x;
				calculate.push(x);
				was.insert(lex[i].s);
				perem[lex[i].s] = x;
			}
			else
			{
				calculate.push(perem[lex[i].s]);
			}
		}
		else
		{
			if (lex[i].may_unary)
			{
				if (v == FUNC)
				{
					double a = calculate.front();
					calculate.pop();
					calculate.push(val_func(lex[i].s, a, lex[i].pos));
				}
				else
				{
					double a = calculate.front();
					calculate.pop();
					calculate.push((-1)*a);
				}
			}
			else {
				double a = calculate.front();
				calculate.pop();
				double b = calculate.front();
				calculate.pop();
				char temp = lex[i].s[0];
				calculate.push(oper(b, a, temp, lex[i].pos));
			}
		}
	}
	return calculate.front();
}

