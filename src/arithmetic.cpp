#include "arithmetic.h"
#include <map>
using namespace std;

TLexeme::TLexeme()
{
	type_elem = no_type;
}

TLexeme::TLexeme(char ch, int p)
{
	if ((p != binary_operation && p != unary_operation) || (ch != '*' && ch != '/' && ch != '+' && ch != '-' && ch != ')' && ch != '('))
	{
		throw "Incorrect initialization";
	}
	else if (p == binary_operation && (ch == '*' || ch == '/' || ch == '+' || ch == '-'))
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

double Solver(const vector<pair<TLexeme, int>> &v)
{
	TStack<TLexeme> s;
	for (int i = 0; i < v.size(); i++)
	{
		TLexeme temp = v[i].first;
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
				if (abs(t2.GetValue().elem) < 1e-7)
				{
					pair<int, int> err(division_by_zero, v[i].second);
					throw err;
				}
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
	int k = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '.')
		{
			k++;
		}
		if (k > 1)
		{
			pair<int, int> err(incorrect_point, index + i);
			throw err;
		}
	}
	double ans;
	if (s[0] == '.')
	{
		pair<int, int> err(incorrect_point, index);
		throw err;
	}
	else if (s[s.size() - 1] == '.')
	{
		pair<int, int> err(incorrect_point, index + s.size() - 1);
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

TLexeme Check_number(const string &s, int &i, int sign)
{
	string temp = "";
	int pos = i, k = i;
	while ((s[k] >= '0' && s[k] <= '9') || s[k] == '.')
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

pair<bool, int> Check_unary_minus(const string& s, int &i)
{
	if (i == 0)
	{
		if (s[0] == '-' && s.size() > 1)
		{
			if (s[1] >= '0' && s[1] <= '9')
			{
				i++;
				return make_pair(true, 1);
			}
			else if (s[1] == '(')
			{
				return make_pair(true, 2);
			}
			else if (s[1] == '-')
			{
				int k = 0;
				while (s[i] == '-')
				{
					k++;
					i++;
				}
				if (s[i] >= '0' && s[i] <= '9')
				{
					if (k & 1)
					{
						return make_pair(true, 1);
					}
					else
					{
						return make_pair(true, 0);
					}
				}
				else if (s[i] == '(')
				{
					return make_pair(true, 3);
				}
			}
		}
		return make_pair(false, -1);
	}
	else if (i + 1 < s.size())
	{
		if ((s[i - 1] == '(' || s[i - 1] == '+' || s[i - 1] == '-' || s[i - 1] == '*' || s[i - 1] == '/') && s[i] == '-' && (s[i + 1] >= '0' && s[i + 1] <= '9'))
		{
			i++;
			return make_pair(true, 1);
		}
		else if (s[i] == '-' && s[i + 1] == '(')
		{
			return make_pair(true, 2);
		}
		else if (s[i] == '-' && s[i + 1] == '-')
		{
			int k = 0;
			while (s[i] == '-')
			{
				k++;
				i++;
			}
			if (s[i] >= '0' && s[i] <= '9')
			{
				if (k & 1)
				{
					return make_pair(true, 1);
				}
				else
				{
					return make_pair(true, 0);
				}
			}
			else if (s[i] == '(')
			{
				if (k & 1)
				{
					return make_pair(true, 3);
				}
				else
				{
					return make_pair(true, 4);
				}
			}
		}
		return make_pair(false, -1);
	}
	else
	{
		return make_pair(false, -1);
	}
}

vector<pair<TLexeme, int>> Create_lexeme_array(const string& str)
{
	string s = New_line_without_spaces(str);
	vector<pair<TLexeme, int>> v;
	int i = 0;
	pair<bool, int> temp = Check_unary_minus(s, i);
	if (temp.first)
	{
		if (temp.second == 0)
		{
			TLexeme p0('+');
			v.push_back(make_pair(p0, i - 1));
			TLexeme p = Check_number(s, i, positive);
			v.push_back(make_pair(p, i));
		}
		else if (temp.second == 1)
		{
			TLexeme p = Check_number(s, i, negative);
			v.push_back(make_pair(p, i - 1));
		}
		else if (temp.second == 2)
		{
			TLexeme p('-', unary_operation);
			v.push_back(make_pair(p, i));
		}
		else if (temp.second == 3)
		{
			TLexeme p0('-', unary_operation);
			v.push_back(make_pair(p0, i - 1));
			TLexeme p('(');
			v.push_back(make_pair(p, i));
		}
		else if (temp.second == 4)
		{
			TLexeme p0('+');
			v.push_back(make_pair(p0, i - 1));
			TLexeme p('(');
			v.push_back(make_pair(p, i));
		}
		i++;
	}
	for (; i < s.size(); i++)
	{
		temp = Check_unary_minus(s, i);
		if (temp.first)
		{
			if (temp.second == 0)
			{
				TLexeme p0('+');
				v.push_back(make_pair(p0, i - 1));
				TLexeme p = Check_number(s, i, positive);
				v.push_back(make_pair(p, i));
			}
			else if (temp.second == 1)
			{
				TLexeme p = Check_number(s, i, negative);
				v.push_back(make_pair(p, i - 1));
			}
			else if (temp.second == 2)
			{
				TLexeme p('-', unary_operation);
				v.push_back(make_pair(p, i));
			}
			else if (temp.second == 3)
			{
				TLexeme p0('-', unary_operation);
				v.push_back(make_pair(p0, i - 1));
				TLexeme p('(');
				v.push_back(make_pair(p, i));
			}
			else if (temp.second == 4)
			{
				TLexeme p0('+');
				v.push_back(make_pair(p0, i - 1));
				TLexeme p('(');
				v.push_back(make_pair(p, i));
			}
		}
		else if (s[i] == '-' || s[i] == '+' || s[i] == '*' || s[i] == '/' || s[i] == '(' || s[i] == ')')
		{
			TLexeme p(s[i]);
			v.push_back(make_pair(p, i));
		}
		else if ((s[i] >= '0' && s[i] <= '9') || s[i] == '.')
		{
			TLexeme p = Check_number(s, i, positive);
			v.push_back(make_pair(p, i));
		}
		else
		{
			pair<int, int> err(unknown_symbol, i);
			throw err;
		}
	}
	return v;
}

vector<pair<TLexeme, int>> Create_RPN_array(const vector<pair<TLexeme, int>>& v)
{
	map<pair<char, int>, int> m;
	m[make_pair('-', unary_operation)] = 3;
	m[make_pair('*', binary_operation)] = 2;
	m[make_pair('/', binary_operation)] = 2;
	m[make_pair('+', binary_operation)] = 1;
	m[make_pair('-', binary_operation)] = 1;
	m[make_pair('(', op_bracket)] = 0;
	TStack<pair<TLexeme, int>> s;
	vector<pair<TLexeme, int>> ans;
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i].first.GetType() == number)
		{
			ans.push_back(v[i]);
		}
		else if (v[i].first.GetValue().oper == '*' || v[i].first.GetValue().oper == '/' || v[i].first.GetValue().oper == '+' || v[i].first.GetValue().oper == '-')
		{
			int priority = m[make_pair(v[i].first.GetValue().oper, v[i].first.GetType())];
			if (s.isEmpty() || m[make_pair(s.front().first.GetValue().oper, s.front().first.GetType())] < priority)
			{
				s.push(v[i]);
			}
			else
			{
				while (!s.isEmpty() && m[make_pair(s.front().first.GetValue().oper, s.front().first.GetType())] >= priority)
				{
					ans.push_back(s.pop());
				}
				s.push(v[i]);
			}
		}
		else if (v[i].first.GetType() == op_bracket)
		{
			s.push(v[i]);
		}
		else if (v[i].first.GetType() == cl_bracket)
		{
			while (!s.isEmpty() && s.front().first.GetType() != op_bracket)
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

bool Type_checking(const vector<int>& v, int type)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] == type)
		{
			return 1;
		}
	}
	return 0;
}

void Error_checking(const vector<pair<TLexeme, int>>& v)
{
	map<int, vector<int>> m;
	vector<int> a1 = { binary_operation, cl_bracket };
	m[number] = a1;
	vector<int> a2 = { op_bracket, number, unary_operation };
	m[op_bracket] = a2;
	vector<int> a3 = { cl_bracket, binary_operation };
	m[cl_bracket] = a3;
	vector<int> a4 = { op_bracket, number, unary_operation };
	m[unary_operation] = a4;
	vector<int> a5 = { op_bracket, number, unary_operation };
	m[binary_operation] = a5;

	TStack<pair<TLexeme, int>> s;
	if (v[0].first.GetType() == cl_bracket || v[0].first.GetType() == binary_operation)
	{
		pair<int, int> err(incorrect_first_symbol, v[0].second);
		throw err;
	}
	else if (v[v.size() - 1].first.GetType() == unary_operation || v[v.size() - 1].first.GetType() == binary_operation || v[v.size() - 1].first.GetType() == op_bracket)
	{
		pair<int, int> err(incorrect_last_symbol, v[v.size() - 1].second);
		throw err;
	}
	for (int i = 0; i < v.size() - 1; i++)
	{
		if (v[i].first.GetType() == op_bracket)
		{
			s.push(v[i]);
		}
		else if (v[i].first.GetType() == cl_bracket)
		{
			if (!s.isEmpty() && s.front().first.GetType() == op_bracket)
			{
				s.pop();
			}
			else
			{
				pair<int, int> err(wrong_bracket_sequence, v[i].second);
				throw err;
			}
		}
		vector<int> t = m[v[i].first.GetType()];
		if (Type_checking(t, v[i + 1].first.GetType()))
		{
			continue;
		}
		else
		{
			pair<int, int> err(missed_operation_or_operand, v[i].second);
			throw err;
		}
	}
	if (v[v.size() - 1].first.GetType() == op_bracket)
	{
		s.push(v[v.size() - 1]);
	}
	else if (v[v.size() - 1].first.GetType() == cl_bracket)
	{
		if (!s.isEmpty() && s.front().first.GetType() == op_bracket)
		{
			s.pop();
		}
		else
		{
			pair<int, int> err(wrong_bracket_sequence, v[v.size() - 1].second);
			throw err;
		}
	}
	if (!s.isEmpty())
	{
		pair<int, int> err(wrong_bracket_sequence, v[v.size() - 1].second);
		throw err;
	}
}

double Calculate(const string& s)
{
	vector<pair<TLexeme, int>> v = Create_lexeme_array(s);
	Error_checking(v);
	double ans = Solver(Create_RPN_array(v));
	return ans;
}

string Error_output(pair<int, int> err)
{
	string temp;
	switch (err.first)
	{
	case division_by_zero:
		temp = "Division by zero in symbol: ";
		break;
	case incorrect_point:
		temp = "Incorrect point in symbol: ";
		break;
	case unknown_symbol:
		temp = "Unknown symbol: ";
		break;
	case incorrect_first_symbol:
		temp = "Incorrect first symbol: ";
		break;
	case incorrect_last_symbol:
		temp = "Incorrect last symbol: ";
		break;
	case wrong_bracket_sequence:
		temp = "Wrong bracket sequence: ";
		break;
	case missed_operation_or_operand:
		temp = "Missed operration or opperand: ";
		break;
	default:
		temp = "Unknown error: ";
	}
	return temp;
}