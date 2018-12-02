#ifndef __ARITHMETIC___H
#define __ARITHMETIC___H

#include <iostream>
#include "stack.h"
#include <string>
#include <cstdlib>

using namespace std;

struct Lex
{
	bool type;
	double num;
	char symbol;
};

double calculate(Stack<Lex>);

inline void error(char c, int place_error)
{
	switch (c)
	{
	case 1:
	{
		cout << "Space in position " << place_error << endl;
		break;
	}
	case 2:
	{
		cout << "The digit cannot be in position " << place_error << endl;
		break;
	}
	case 3:
	{
		cout << "The fractional part of the number is not initialized  on the position " << place_error << endl;
		break;
	}
	case 4:
	{
		cout << "Division by zero by position " << place_error << endl;
		break;
	}
	case 5:
	{
		cout << "The opening bracket cannot be positioned " << place_error << endl;
		break;
	}
	case 6:
	{
		cout << "The closing bracket cannot be positioned " << place_error << endl;
		break;
	}
	case 7:
	{
		cout << "The number cannot be positioned " << place_error << endl;
		break;
	}
	case 8:
	{
		cout << "Error at the end of an expression " << endl;
		break;
	}
	case 9:
	{
		cout << "Unary minus cannot be positioned " << place_error << endl;
		break;
	}
	case 10:
	{
		cout << "The number of opening brackets is not equal to the number of closing brackets" << endl;
		break;
	}
	case 11:
	{
		cout << ", cannot be positioned " << place_error << endl;
		break;
	}
	case 12:
	{
		cout << ": cannot be positioned " << place_error << endl;
		break;
	}
	}
}

inline char isDigit(char c)
{
	if (c >= '0' && c <= '9')
	{
		return c;
	}
	else
	{
		return c + 1;
	}
}

inline int priority(char c)
{
	switch (c) {
	    case '(':
	    {
		    return 1;
			break;			
	    }
	    case '+': case '-':
	    {
		    return 2;
			break;
	    }
	    case '*': case '/': 
	    {
		    return 3;
			break;
	    }
	    default: 
	    {
		    return 0;
			break;
	    }
	}
}

inline bool brackets_error(string str_in)
{
	int flag = 0;
	int count = 0;
	for (int i = 0; i < str_in.size(); i++)
	{
		if (str_in[i] == '(')
		{
			count++;
		}
		if (str_in[i] == ')')
		{
			count--;
		}
		if (count < 0)
		{
			error(6, i);
			flag++;
		}
	}
	if (count != 0)
	{
		flag++;
		error(10, 1);
	}
	if (flag > 0)
	{
		throw 1;
	}
	else
	{
		return false;
	}
}

inline int isvar(string str_in)
{
	string s = "abcde";
	for (int i = 0; i < str_in.size(); i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (str_in[i] == s[j])
			{
				for (int k = 0; k < 5; k++)
				{
					if (str_in[i + 1] == str_in[k])
					{
						cout << "variables are next" << endl;
						return 2;
					}
				}
				return 0;
			}
		}
	}
	return 1;
}

inline string initvar(string str_in)
{
	string str_out = str_in;
	string s = "abcde";
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < str_out.size(); i++)
		{
			int count = 0; 
			string str;
			if (str_out[i] == s[j])
			{
				count++;
				if (count == 1)
				{
					cin >> str;
				}
				str_out.replace(str_out.begin() + i, str_out.begin() + i + 1, str);
			}
		}
	}
	return str_out;
}

inline string error_checking(string str_in)
{
	int flag = 0;
	if (str_in[0] == '+')
	{
		str_in.erase(str_in.begin());
	}
	if (str_in[0] == '-')
	{
		str_in.insert(str_in.begin(), '0');
	}
	if (str_in[0] == ' ')
	{
		error(1, 0);
		flag++;
	}
	if (str_in[0] == ',')
	{
		error(11, 0);
		flag++;
	}
	if (str_in[0] == ':')
	{
		error(12, 0);
		flag++;
	}
	if (str_in[0] == '*' || str_in[0] == '/' || str_in[0] == ',' || str_in[0] == '.')
	{
		error(2, 0);
		flag++;
	}
	for (int i = 1; i < str_in.size() - 1; i++)
	{
		if (str_in[i] == ' ')
		{
			error(1, 0);
			flag++;
		}
		if (str_in[i] == ',')
		{
			error(11, 0);
			flag++;
		}
		if (str_in[i] == ':')
		{
			error(12, 0);
			flag++;
		}
		else
		{
			char c = str_in[i];
			
			switch (c)
			{
			    case '+':
			    {
					switch (str_in[i - 1])
					{
					    case '.':
						{
							error(3, i - 1);
							flag++;
							break;
						}
						case '+':
						{
							str_in.erase(str_in.begin() + i);
							i--;
							break;
						}
						case '-':
						{
							str_in.erase(str_in.begin() + i);
							i--;
							break;
						}
						case '/':
						{
							break;
						}
						case '*':
						{
							break;
						}
						default :
						{
							if (str_in[i - 1] != isDigit(str_in[i - 1]) && str_in[i - 1] != ')')
							{
								error(2, i);
								flag++;
							}
							break;
						}
					}
					break;
			    }
				case '-':
				{
					switch (str_in[i - 1])
					{
					    case '(':
						{
							if (str_in[i + 1] != isDigit(str_in[i + 1]))
							{
								error(9, i);
								flag++;
							}
							break;
						}
						case '.':
						{
							error(3, i - 1);
							flag++;
							break;
						}
						case '+':
						{
							str_in[i - 1] = '-';
							str_in.erase(str_in.begin() + i);
							i--;
							break;
						}
						case '-':
						{
							str_in[i - 1] = '+';
							str_in.erase(str_in.begin() + i);
							i--;
							break;
						}
						case '/':
						{
							break;
						}
						case '*':
						{
							break;
						}
						default:
						{
							if (str_in[i - 1] != isDigit(str_in[i - 1]) && str_in[i - 1] != ')')
							{
								error(2, i);
								flag++;
							}
							break;
						}
					}
					break;
				}
				case '*':
				{
					switch (str_in[i - 1])
					{
					    case '.':
					    {
							 error(3, i - 1);
						     flag++;
						     break;
					    }
						default:
						{
							if (str_in[i - 1] != isDigit(str_in[i - 1]) && str_in[i - 1] != ')')
							{
								error(2, i);
								flag++;
							}
							break;
						}
					}
					break;
				}
				case '/':
				{
					if (str_in[i - 1] == '.')
					{
						error(3, i - 1);
						flag++;
					}
					if (str_in[i - 1] != isDigit(str_in[i - 1]) && str_in[i - 1] != ')')
					{
						error(2, i);
						flag++;
					}
					if (str_in[i + 1] == '0')
					{
						if ((i + 2) != str_in.size())
						{
							if (str_in[i + 2] == '.')
							{
								error(4, i + 1);
								flag++;
							}
						}
						else
						{
							error(4, i + 1);
							flag++;
						}
					}
					break;
				}
				case '(':
				{
					if (str_in[i - 1] == '.')
					{
						error(3, i - 1);
						flag++;
					}
					if (str_in[i - 1] == isDigit(str_in[i - 1]))
					{
						error(5, i);
						flag++;
					}
					break;
				}
				case ')':
				{
					if (str_in[i - 1] == '.')
					{
						error(3, i - 1);
						flag++;
					}
					if (str_in[i - 1] != isDigit(str_in[i - 1]) && str_in[i - 1] != '(')
					{
						error(6, i);
						flag++;
					}
					break;
				}
				case '.':
				{
					if (str_in[i - 1] != isDigit(str_in[i - 1]))
					{
						error(3, i);
						flag++;
					}
					break;
				}
				default :
				{
					if (str_in[i - 1] == ')')
					{
						error(7, i);
						flag++;
					}
					break;
				}
			}
		}
	}
	if (str_in[str_in.size() - 1] == '('
		|| str_in[str_in.size() - 1] == '+'
		|| str_in[str_in.size() - 1] == '-'
		|| str_in[str_in.size() - 1] == '*'
		|| str_in[str_in.size() - 1] == '/'
		|| str_in[str_in.size() - 1] == '.'
		|| str_in[str_in.size() - 1] == ','
		|| str_in[str_in.size() - 1] == ':')
	{
		error(8, str_in.size() - 1);
		flag++;
	}

	if (flag > 0)
	{
		throw "0";
		return "0";
	}
	else
	{
		return str_in;
	}
}

inline Stack<Lex> convertPpn(string str_in)
{
	Stack<Lex> ppn;
	Stack<char> temp;
	for (int i = 0; i < str_in.size(); i++)
	{
		switch (str_in[i])
		{
		    case '+': case '*': case '/':
			{
				while (priority(temp.spop()) >= priority(str_in[i]))
				{
					Lex op;
					op.symbol = temp.pop();
					op.type = true;
					ppn.push(op);
				}
				temp.push(str_in[i]);
				break;
			}
			case '-':
			{
				if (str_in[i + 1] == '(')
				{
					int j = i + 2;
					string temp;
					while (str_in[j] != ')')
					{
						temp = temp + str_in[j];
						str_in.erase(str_in.begin() + j);
					}
					str_in.erase(str_in.begin() + j);
					double res = calculate(convertPpn(temp));
					temp = to_string(res);
					const char *s = temp.c_str();
					str_in.replace(str_in.begin() + i + 1, str_in.begin() + i + 2, temp);
				}
				if (str_in[i + 1] >= '0' && str_in[i + 1] <= '9' && (str_in[i - 1] == '+' || str_in[i - 1] == '-' || str_in[i - 1] == '*' || str_in[i - 1] == '/' || str_in[i - 1] == '('))
				{
					string d = "-";
					i++;
					while (str_in[i] == isDigit(str_in[i]) || str_in[i] == '.')
					{		
						d = d + str_in[i];
						i++;
					}
					i--;
					Lex dou;
					const char *str = d.c_str();
					dou.num = atof(str);
					dou.type = false;
					ppn.push(dou);
				}
				else
				{
					while (priority(temp.spop()) >= priority(str_in[i]))
					{
						Lex op;
						op.symbol = temp.pop();
						op.type = true;
						ppn.push(op);
					}
					temp.push('-');
				}
				break;
			}
			case '(':
			{
				temp.push(str_in[i]);
				break;
			}
			case ')':
			{
				while (temp.spop() != '(')
				{
					Lex op;
					op.symbol = temp.pop();
					op.type = true;
					ppn.push(op);
				}
				temp.pop();
				break;
			}
			default :
			{
					string d;
					while (str_in[i] == isDigit(str_in[i]) || str_in[i] == '.')
					{
						d = d + str_in[i];
						i++;
					}
					i--;
					Lex dou;
					const char *str = d.c_str();
					dou.num = atof(str);
					dou.type = false;
					ppn.push(dou);
					break;
			}
		}
	}
	while (temp.istop() != 0)
	{
		Lex op;
		op.symbol = temp.pop();
		op.type = true;
		ppn.push(op);
	}
	return ppn;
}

inline double calculate(Stack<Lex> ppn)
{
	Stack<Lex> reverseppn;
    while(ppn.istop() != 0)
	{
		Lex ppp = ppn.pop();
		reverseppn.push(ppp);
	}
	Stack<double> temp;
	Lex val1 = reverseppn.pop(), val2;
	while (reverseppn.istop() != 0)
	{
		val2 = reverseppn.pop();
		if (val2.type == false)
		{
			temp.push(val1.num);
			val1 = val2;
		}
		else
		{
			double res = temp.pop();
			switch (val2.symbol)
			{
			    case '+':
				{
					res = res + val1.num;
					break;
				}
				case '-':
				{
					res = res - val1.num;
					break;
				}
				case '*':
				{
					res = res * val1.num;
					break;
				}
				case '/':
				{
					res = res / val1.num;
					break;
				}
			}
			val1.num = res;
		}
		
	}
	return val1.num;
}
#endif 