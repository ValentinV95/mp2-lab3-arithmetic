#include "arithmetic.h"
#include "stack.h"
#include <vector>
#include <string>
#include <set>
#include <map>
using namespace std;

TLexeme::TLexeme()
{
	type_elem = no_type;
}

TLexeme::TLexeme(char ch, int p)
{
	if (p == binary_operation && (ch == '*' || ch == '/' || ch == '+' || ch == '-'))
	{
		type_elem = binary_operation;
		value.oper = ch;
	}
	else if (p == unary_operation && ch == '-')
	{
		type_elem = unary_operation;
		value.oper = ch;
	}
	else if (ch == '(')
	{
		type_elem = op_bracket;
		value.oper = ch;
	}
	else if (ch == ')')
	{
		type_elem = cl_bracket;
		value.oper = ch;
	}
	else
	{
		type_elem = no_type;
	}
}

TLexeme::TLexeme(double a)
{
	value.elem = a;
	type_elem = number;
}

TLexeme::TLexeme(const TLexeme& a)
{
	value.elem = a.value.elem;
	value.oper = a.value.oper;
	type_elem = a.type_elem;
}

TLexeme& TLexeme::operator=(const TLexeme& a)
{
	value.elem = a.value.elem;
	value.oper = a.value.oper;
	type_elem = a.type_elem;
	return *this;
}

elem_or_oper TLexeme::GetValue() const
{
	return value;
}

int TLexeme::GetType() const
{
	return type_elem;
}

double Solver(const vector<TLexeme> &v)
{
	TStack<TLexeme> s;
	for (int i = 0; i < v.size(); i++)
	{
		TLexeme temp = v[i];
		if (temp.GetType() == number)
		{
			s.push(temp);
		}
		else if (temp.GetType() == unary_operation)
		{
			TLexeme t(s.pop());
			double ans;
			if (temp.GetValue().oper == '-')
			{
				ans = -t.GetValue().elem;
			}
			TLexeme a(ans);
			s.push(ans);
		}
		else if (temp.GetType() == binary_operation)
		{
			TLexeme t2(s.pop()), t1(s.pop());
			double ans;
			switch (temp.GetValue().oper)
			{
			case '+':
				ans = t1.GetValue().elem + t2.GetValue().elem;
				break;
			case '-':
				ans = t1.GetValue().elem - t2.GetValue().elem;
				break;
			case '*':
				ans = t1.GetValue().elem * t2.GetValue().elem;
				break;
			case '/':
				ans = t1.GetValue().elem / t2.GetValue().elem;
				break;
			}
			TLexeme a(ans);
			s.push(a);
		}
	}
	return s.pop().GetValue().elem;
}

double Сonverting_number(const string& s, int index, int sign)
{
	double ans;
	if (s[0] == '.')
	{
		pair<string, int> err("Incorrect number", index);
		throw err;
	}
	else if (s[s.size() - 1] == '.')
	{
		pair<string, int> err("Incorrect number", index + s.size() - 1);
		throw err;
	}
	else
	{
		ans = atof(s.c_str());
		if (sign == negative)
		{
			ans = -ans;
		}
	}
	return ans;
}

TLexeme Check_number(const string &s, int &i, const set<char>& num, int sign)
{
	string temp = "";
	int pos = i, k = i;
	while (!(num.find(s[k]) == num.end()) || s[k] == '.')
	{
		temp += s[k];
		k++;
	}
	i = k - 1;
	TLexeme p(Сonverting_number(temp, pos, sign));
	return p;
}

string New_line_without_spaces(const string &s)
{
	string temp = "";
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] != ' ')
		{
			temp += s[i];
		}
	}
	return temp;
}

vector<TLexeme> Create_lexeme_array(const string& str)
{
	string s = New_line_without_spaces(str);
	set<char> num;
	for (char i = '0'; i <= '9'; i++)
	{
		num.insert(i);
	}
	vector<TLexeme> v;
	for (int i = 0; i < s.size(); i++)
	{
		if (!(num.find(s[i]) == num.end()) || s[i] == '.')
		{
			TLexeme p = Check_number(s, i, num, positive);
			v.push_back(p);
		}
		else if (i == 0 && s[i] == '-' && i + 1 < s.size())
		{
			if (!(num.find(s[i + 1]) == num.end()))
			{
				i++;
				TLexeme p = Check_number(s, i, num, negative);
				v.push_back(p);
			}
			else if (s[i + 1] == '(')
			{
				TLexeme p('-', unary_operation);
				v.push_back(p);
			}
		}
		else if (i != 0 && s[i - 1] == '(' && s[i] == '-' && i + 1 < s.size() && !(num.find(s[i + 1]) == num.end()))
		{
			i++;
			TLexeme p = Check_number(s, i, num, negative);
			v.push_back(p);
		}
		else if (s[i] == '-' && i + 1 < s.size() && s[i + 1] == '(')
		{
			TLexeme p('-', unary_operation);
			v.push_back(p);
		}
		else if (s[i] == '-' || s[i] == '+' || s[i] == '*' || s[i] == '/' || s[i] == '(' || s[i] == ')')
		{
			TLexeme p(s[i]);
			v.push_back(p);
		}
		else
		{
			pair<string, int> err("Incorrect symbol", i);
			throw err;
		}
	}
	return v;
}

vector<TLexeme> Create_RPN_array(const vector<TLexeme>& v)
{
	map<pair<char, int>, int> m;
	m[make_pair('-', unary_operation)] = 3;
	m[make_pair('*', binary_operation)] = 2;
	m[make_pair('/', binary_operation)] = 2;
	m[make_pair('+', binary_operation)] = 1;
	m[make_pair('-', binary_operation)] = 1;
	m[make_pair('(', op_bracket)] = 0;
	TStack<TLexeme> s;
	vector<TLexeme> ans;
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i].GetType() == number)
		{
			ans.push_back(v[i]);
		}
		else if (v[i].GetValue().oper == '*' || v[i].GetValue().oper == '/' || v[i].GetValue().oper == '+' || v[i].GetValue().oper == '-')
		{
			int priority = m[make_pair(v[i].GetValue().oper, v[i].GetType())];
			if (s.isEmpty() || m[make_pair(s.front().GetValue().oper, s.front().GetType())] < priority)
			{
				s.push(v[i]);
			}
			else
			{
				while (!s.isEmpty() && m[make_pair(s.front().GetValue().oper, s.front().GetType())] >= priority)
				{
					ans.push_back(s.pop());
				}
				s.push(v[i]);
			}
		}
		else if (v[i].GetType() == op_bracket)
		{
			s.push(v[i]);
		}
		else if (v[i].GetType() == cl_bracket)
		{
			while (!s.isEmpty() && s.front().GetType() != op_bracket)
			{
				ans.push_back(s.pop());
			}
			s.pop();
		}
	}
	while (!s.isEmpty())
	{
		ans.push_back(s.pop());
	}
	return ans;
}