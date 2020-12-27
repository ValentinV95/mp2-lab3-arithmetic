// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#pragma once
#include "stack.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
struct Operation
{
	char op;
	int prior;
};
class Lexeme
{
private:
	double number;
	Operation op;
	int check;
	int amount_of_arg;
public:
	Lexeme() noexcept
	{}
	Lexeme(double num) noexcept
	{
		number = num;
		check = 1;
	}
	Lexeme(char oper, int arg = 2)
	{
		op.op = oper;
		if (oper == '(')
		{
			op.prior = 0;
		}
		else if (oper == ')')
		{
			op.prior = 1;
		}
		else if (oper == '+' || oper == '-')
		{
			op.prior = 2;
		}
		else if (oper == '*' || oper == '/')
		{
			op.prior = 3;
		}
		else
		{
			op.prior = -1; 
		}
		amount_of_arg = arg;
		check = 0;
	}
	bool can_go_next(vector <Lexeme>& a, int i)
	{
		if (a[i].is_number())
		{
			return a[i + 1].op.op != '('; 
		}
		else
		{
			if (a[i].is_op_br())
			{
				return (a[i + 1].is_number() || a[i + 1].is_op_br() || a[i + 1].is_unary());
			}
			else if (a[i].is_cl_br())
			{
				return (!a[i + 1].is_op_br() && !a[i + 1].is_number());
			}
			else
			{
				return !a[i + 1].is_cl_br();
			}
		}

	}
	char get_oper()
	{
		return op.op;
	}
	double get_number()
	{
		return number;
	}
	int get_prior()
	{
		return op.prior;
	}
	bool is_op()
	{
		return ((check == 0) && (op.prior != -1));
	}
	bool is_op_br()
	{
		return op.op == '(';
	}
	bool is_cl_br()
	{
		return op.op == ')';
	}
	bool is_number()
	{
		return check == 1;
	}
	bool is_unary()
	{
		return amount_of_arg == 1;
	}
};

class Solver
{
private:
	vector <Lexeme> d;
public:
	void convert_string_to_lexeme(string& s)
	{
		int i = 0, count = 0;
		string temp;
		double num;
		for (int i = 0; i < s.size(); i++)
		{
			while (s[i] == ' ')
			{
				s.erase(i, 1);
			}
		}
		while (i < s.size())
		{
			if (s[i] >= '0' && s[i] <= '9')
			{
				bool dot = false;
				temp = "";
				while ((i < s.size()) && ((s[i] >= '0' && s[i] <= '9') || (s[i] == '.')))
				{
					if (s[i] == '.' && dot)
					{
						throw "1";
					}
					if (s[i] == '.')
					{
						dot = true;
					}
					temp += s[i];
					i++;
				}
				num = stod(temp, 0);
				Lexeme a(num);
				d.push_back(a);
				continue;
			}
			if (s[i] == '/')
			{
				Lexeme a('/');
				d.push_back(a);
				i++;
				continue;
			}
			if (s[i] == '*')
			{
				Lexeme a('*');
				d.push_back(a);
				i++;
				continue;
			}
			if (s[i] == '+')
			{
				Lexeme a('+');
				d.push_back(a);
				i++;
				continue;
			}
			if (s[i] == '(')
			{
				Lexeme a('(');
				d.push_back(a);
				i++;
				continue;
			}
			if (s[i] == ')')
			{
				Lexeme a(')');
				d.push_back(a);
				i++;
				continue;
			}
			if (s[i] == '-')
			{
				bool dot = false;
				bool unary = false;
				temp = "";
				count = 0;
				count++;
				if (i == 0)
				{
					unary = true;
				}
				else if (s[i - 1] == '(' || s[i - 1] == '/' || s[i - 1] == '*' || s[i - 1] == '+')
				{
					unary = true;
				}

				if (i + 1 < s.size())
				{

					while (i + 1 < s.size() && s[i + 1] == '-')
					{
						count++;
						i++;
					}

					if (count % 2 == 1 && !unary)
					{
						Lexeme a('-');
						d.push_back(a);
						i++;
						continue;
					}
					else if (count % 2 == 0 && !unary)
					{
						Lexeme a('+');
						d.push_back(a);
						i++;
						continue;
					}
					else if (count % 2 == 1 && unary)
					{
						temp = "-";
					}
					if (i + 1 < s.size() && s[i + 1] == '(')
					{
						Lexeme a('-', 1);
						d.push_back(a);
						i++;
						continue;
					}

					if (i + 1 < s.size() && s[i + 1] >= '0' && s[i + 1] <= '9')
					{
						i++;
						while ((i < s.size()) && ((s[i] >= '0' && s[i] <= '9') || (s[i] == '.')))
						{
							if (s[i] == '.' && dot)
							{
								throw "1";
							}
							if (s[i] == '.')
							{
								dot = true;
							}
							temp += s[i];
							i++;
						}
						num = stod(temp, 0);
						Lexeme a(num);
						d.push_back(a);
						continue;
					}
					else
					{
						throw "1";
					}
				}
				else
				{
					Lexeme a('-');
					d.push_back(a);
					i++;
					continue;
				}
			}
			else
			{
				throw "Incorrect symbol";
			}
		}
	}
	void convert_to_RPN()
	{
		int count = 0;
		for (int i = 0; i < d.size(); i++)
		{
			if (d[i].is_op_br())
			{
				count++;
			}
			if (d[i].is_cl_br())
			{
				count--;
			}
		}
		if (count != 0)
		{
			throw "Wrong amount of brackets";
		}
		if (d[0].is_op() && !d[0].is_op_br())
		{
			throw "Expression can not start with operations such as '+','*','/',')'";
		}
		for (int i = 0; i < d.size() - 1; i++)
		{
			if (!d[i].can_go_next(d, i))
			{
				throw "Wrong syntax";
			}
		}

		vector <Lexeme> input;
		TStack <Lexeme> b;
		for (int i = 0; i < d.size(); i++)
		{
			if (d[i].is_number())
			{
				input.push_back(d[i]);
			}
			else if (d[i].is_op())
			{
				if (d[i].is_op_br())
				{
					b.push(d[i]);
					continue;
				}
				if (d[i].is_cl_br())
				{
					while (!b.front().is_op_br())
					{
						input.push_back(b.pop());
					}
					b.pop();
				}
				if (b.is_empty() || b.front().get_prior() < d[i].get_prior())
				{
					if (!d[i].is_cl_br())
					{
						b.push(d[i]);
					}
				}
				else
				{
					while (!b.is_empty() && b.front().get_prior() >= d[i].get_prior())
					{
						input.push_back(b.pop());
					}
				}
			}
		}
		while (!b.is_empty())
		{
			input.push_back(b.pop());
		}
		d = input;
	}
	double solve()
	{
		TStack <Lexeme> b;
		Lexeme a, c;
		for (int i = 0; i < d.size(); i++)
		{
			if (d[i].is_number())
			{
				b.push(d[i]);
			}
			else
			{
				if (d[i].is_unary())
				{
					a = b.pop();
				}
				else
				{
					a = b.pop();
					c = b.pop();
				}
				switch (d[i].get_oper())
				{
				case '+':
				{
					Lexeme temp(c.get_number() + a.get_number());
					b.push(temp);
					break;
				}
				case '-':
				{
					if (d[i].is_unary())
					{
						Lexeme temp(-a.get_number());
						b.push(temp);
						break;
					}
					else
					{
						Lexeme temp(c.get_number() - a.get_number());
						b.push(temp);
						break;
					}
				}
				case '*':
				{
					Lexeme temp(c.get_number() * a.get_number());
					b.push(temp);
					break;
				}
				case '/':
				{
					if (a.get_number() == 0.0) // compare with eps. probably??
					{
						throw "Division by zero";
					}
					else
					{
						Lexeme temp(c.get_number() / a.get_number());
						b.push(temp);
						break;
					}
				}
				}
			}
		}
		d.clear();
		return b.pop().get_number();
	}
};