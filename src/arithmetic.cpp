// реализация функций и классов для вычисления арифметических выражений
#include "arithmetic.h"

bool Lexeme::is_unary()
{
	return amount_of_arg == 1;
}

char Lexeme::get_oper()
{
	return op.op;
}

double Lexeme::get_number()
{
	return number;
}

int Lexeme::get_prior()
{
	return op.prior;
}

bool Lexeme::is_op()
{
	return ((check == 0) && (op.prior != -1));
}

bool Lexeme::is_number()
{
	return check == 1;
}

bool Lexeme::is_op_br()
{
	return op.op == '(';
}

bool Lexeme::is_cl_br()
{
	return op.op == ')';
}

bool Lexeme::can_go_next(vector <Lexeme>& a, int i) 
{
	// max i = a.size() - 1
	if (a[i].is_number())
	{
		return a[i + 1].op.op != '('; //((a[i + 1].is_op()) && (a[i + 1].op.op != '('));
	}
	else 
	{
		if (a[i].is_op_br())
		{
			return (a[i + 1].is_number() || a[i + 1].is_op_br() || a[i+1].is_unary());
		}
		else if(a[i].is_cl_br())
		{
			return (!a[i + 1].is_op_br() && !a[i + 1].is_number());
		}
		else // clear operation:'+','-','*','/'
		{
			return a[i + 1].is_op_br() || a[i+1].is_number() || a[i+1].is_unary();
		}
	}

}

void Solver::convert_string_to_lexeme(string& s)
{
	int i = 0,count = 0;
	string temp;
	double num;
	for (int i = 0;i < s.size();i++) //deleting spaces
	{
		while (s[i] == ' ')
		{
			s.erase(i, 1);
		}
	}
	while (i < s.size())
	{
		if (s[i]>='0' && s[i]<='9')
		{
			bool dot = false;
			temp = "";
			while ((i < s.size()) && ((s[i] >= '0' && s[i] <= '9') || (s[i] == '.')))
			{
				if (s[i] == '.' && dot)
				{
					string err;
					err = "Number has two or more dots in it";
					d.clear();
					throw err;
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
			if (i == 0) // -
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
				// - : '(',number,'-'
				if (i + 1 < s.size() && s[i + 1] == '(') // "..-(.."
				{
					Lexeme a('-',1); //unary minus
					d.push_back(a);
					i++;
					continue;
				}
				
				if (i + 1 < s.size() && s[i + 1] >= '0' && s[i + 1] <= '9') // "..-2.34.."
				{
					i++;
					while ((i<s.size()) && ((s[i] >= '0' && s[i] <= '9') || (s[i] == '.')))
					{
						if (s[i] == '.' && dot)
						{
							string err;
							err = "Number has two or more dots in it";
							d.clear();
							throw err;
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
					string err;
					err = "Wrong operation order after minus (no number or bracket)";
					d.clear();
					throw err ; // 2---- or 2----/
				}
			}
			//else
			//{
			//	// throw actually
			//	Lexeme a('-');
			//	d.push_back(a);
			//	i++;
			//	continue;
			//}
		}
		else
		{
			string err;
			err = "Incorrect symbol";
			d.clear();
			throw err;
		}
	}
}

void Solver::convert_to_RPN()
{
	int count = 0;

	// brackets check
	for (int i = 0;i < d.size();i++) 
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
		string err;
		err = "Wrong amount of brackets";
		d.clear();
		throw err;
	}

	//syntax check
	if (d[0].is_op() && !d[0].is_op_br() && !d[0].is_unary())
	{
		string err;
		err = "Expression can not start with operations such as '+','*','/',')'";
		d.clear();
		throw err;
	}
	if (d.back().is_op())
	{
		if (!d.back().is_cl_br())
		{
			string err;
			err = "Binary operation in the end of the expression";
			d.clear();
			throw err;
		}
	}
	for (int i = 0;i < d.size() - 1;i++)
	{
		if (!d[i].can_go_next(d, i))
		{
			string err = "";
			if (d[i].is_number())
			{
				err += d[i].get_number();
				err += " can't go before ";
				err += d[i + 1].get_oper();
				d.clear();
				throw err;
			}
			else if (d[i].is_op())
			{
				err += d[i].get_oper();
				err += " can't go before ";
				if (d[i + 1].is_number())
				{
					err += d[i + 1].get_number();
				}
				else if (d[i+1].is_op())
				{
					err += d[i + 1].get_oper();
				}
				d.clear();
				throw err;
			}
			
		}
	}

	vector <Lexeme> input;
	TStack <Lexeme> b;
	for (int i = 0;i < d.size();i++)
	{
		if (d[i].is_number())
		{
			input.push_back(d[i]);		
		} else if (d[i].is_op())
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
				b.pop();  //pop '('
			}
			gh:
			if (b.is_empty() || b.front().get_prior() < d[i].get_prior() || d[i].is_unary())
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
				goto gh; 
			}
		}
	}
	while (!b.is_empty())
	{
		input.push_back(b.pop());
	}
	d = input;
}

double Solver::solve()
{
	TStack <Lexeme> b;
	Lexeme a,c;
	for (int i = 0;i < d.size();i++)
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
						string err;
						err = "Division by zero";
						d.clear();
						throw err;
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





