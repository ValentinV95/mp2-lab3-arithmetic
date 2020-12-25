// объявление функций и классов для вычисления арифметических выражений
#ifndef _ARITHMETIC_H_
#define _ARITHMETIC_H_
#include <string>
#include <cmath>
#include "stack.h"
 
using namespace std;
enum Operator
{
	None = 0,

	Add,
	Del,
	Mult,
	Div,
	Negative,
	Sin,
	Cos,
	Ln,
	Exp,

	Open,
	Close
};
Operator GetOperator(string op)
{
	if (op == "+") return Operator::Add;
	if (op == "-") return Operator::Del;
	if (op == "*") return Operator::Mult;
	if (op == "/") return Operator::Div;
	if (op == "un-") return Operator::Negative;
	if (op == "sin") return Operator::Sin;
	if (op == "cos") return Operator::Cos;
	if (op == "ln") return Operator::Ln;
	if (op == "exp") return Operator::Exp;
	if (op == "(") return Operator::Open;
	if (op == ")") return Operator::Close;
	return Operator::None;
}

class Data
{
private:
	double n;
	Operator _op;
	bool isNum;
public:
	Data() noexcept { }
	Data(double x) noexcept { n = x; isNum = true; }
	Data(Operator op) noexcept { _op = op; isNum = false; }
	~Data() noexcept { }

	double getn() noexcept { return n; }
	Operator getop() { return _op; }
	bool is_num() noexcept { return isNum; }
	bool is_op()  noexcept { return !isNum; }

	int priority()
	{
		switch (_op)
		{
		case Add: return 2;
		case Del: return 2;
		case Mult: return 3;
		case Div: return 3;
		case Negative: return 4;
		case Sin: return 4;
		case Cos: return 4;
		case Ln: return 4;
		case Exp: return 4;
		case Open: return 1;
		case Close: return 0;
		default: throw exception("ERROR TYPE OPERATOR");
		}
	}
	void operator= (double x)
	{
		n = x;
		isNum = true;
	}
	void operator= (Data x)
	{
		if (x.is_num())
		{
			n = x.getn();
			isNum = true;
		}
		else
		{
			_op = x.getop();
			isNum = false;
		}
	}
	void operator= (Operator x)
	{
		_op = x;
		isNum = false;
	}
};

double find_des(Data* datas, int count);
int cheking(Data* datas, int n);

bool isCompare(string str, int index, string compare)
{
	int count = compare.size();
	for (int i = 0; i < count; i++)
		if (compare[i] != str[i + index])
			return false;
	return true;
}

double work(std::string s)
{
	int i = 0, j = 0;
	double tmp, x, d, a0, a1, a2, a3, a4;
	Data datas[100];
	bool f1 = true, f2 = true, f3 = true, f4 = true, f5 = true;
	if (s[i] == '-')
	{
		datas[j++] = -1;
		datas[j++] = Operator::Mult;
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
			datas[j] = x;
			j++;
		}
		else if (isCompare(s, i, "sin"))
		{
			datas[j++] = Operator::Sin;
			i = i + 3;
		}
		else if (isCompare(s, i, "cos"))
		{
			datas[j++] = Operator::Cos;
			i = i + 3;
		}
		else if (isCompare(s, i, "ln"))
		{
			datas[j++] = Operator::Ln;
			i = i + 2;
		}
		else if (isCompare(s, i, "exp"))
		{
			datas[j++] = Operator::Exp;
			i = i + 3;
		}
		else if (isCompare(s, i, "x0"))
		{
			if (f1)
			{
				std::cout << "enter  x0" << std::endl;
				std::cin >> a0;
				f1 = false;
			}
			datas[j++] = a0;
			i = i + 2;
		}
		else if (isCompare(s, i, "x1"))
		{
			if (f2)
			{
				std::cout << "enter  x1" << std::endl;
				std::cin >> a1;
				f2 = false;
			}
			datas[j++] = a1;
			i = i + 2;
		}
		else if (isCompare(s, i, "x2"))
		{
			if (f3)
			{
				std::cout << "enter  x2" << std::endl;
				std::cin >> a2;
				f3 = false;
			}
			datas[j++] = a2;
			i = i + 2;
		}
		else if (isCompare(s, i, "x3"))
		{
			if (f4)
			{
				std::cout << "enter  x3" << std::endl;
				std::cin >> a3;
				f4 = false;
			}
			datas[j++] = a3;
			i = i + 2;
		}
		else if (isCompare(s, i, "x4"))
		{
			if (f5)
			{
				std::cout << "enter  x4" << std::endl;
				std::cin >> a4;
				f5 = false;
			}
			datas[j++] = a4;
			i = i + 2;
		}
		else if (s[i] == '+')
		{
			datas[j] = Operator::Add;
			j++;
			i++;
		}
		else if (s[i] == '*')
		{
			datas[j] = Operator::Mult;
			j++;
			i++;
		}
		else if (s[i] == '/')
		{
			datas[j] = Operator::Div;
			j++;
			i++;
		}
		else if (s[i] == '-')
		{
			if (datas[j - 1].is_op() && datas[j - 1].getop() != Operator::Close)
			{
				datas[j++] = Operator::Negative;
				i++;
			}
			else
			{
				datas[j] = Operator::Del;
				j++;
				i++;
			}
		}
		else if (s[i] == '(')
		{
			datas[j] = Operator::Open;
			j++;
			i++;
		}
		else if (s[i] == ')')
		{
			datas[j] = Operator::Close;
			j++;
			i++;
		}
		else
		{
			throw exception("ERROR");
		}
	}
	int dat;
	if ((dat = cheking(datas, j)) == 0) std::cout << "GOOD" << std::endl;
	else throw exception("ERROR");

	Data* _datas;
	_datas = new Data[j];
	TStack<Data> t;
	int l = 0;

	for (int k = 0; k < j; k++)
	{
		if (datas[k].is_num()) _datas[l++] = datas[k];
		else if (t.isempty()) t.push(datas[k]);
		else if (datas[k].priority() == 1) t.push(datas[k]); 
		else
		{
			while (!(t.isempty()) && (datas[k].priority() <= t.show().priority()))
			{
				if (t.show().priority() == 1)
				{
					t.pop();
					break;
				}
				_datas[l] = t.pop();
				l++;
			}
			if (datas[k].priority() != 0) t.push(datas[k]);
		}
	}
	while (!(t.isempty()))
	{
		_datas[l] = t.pop();
		l++;
	}
	return find_des(_datas, l);
}
int cheking(Data* datas, int n)
{
	int j = 0;
	for (int i = 0; i < n; i++) {
		if (datas[i].is_num()) {
			if (i != n - 1) {
				switch (datas[i + 1].getop())
				{
					case Add:
					case Del:
					case Mult:
					case Div:
					case Close:
						break;
					default:
						return 1;
				}
			}
		}
		else {
			switch (datas[i].getop())
			{
				case Open:
					j++;
					if (i == n - 1) return 7;
					switch (datas[i + 1].is_op() ? datas[i + 1].getop() : Operator::None)
					{
						case None:
						case Open:
						case Sin:
						case Cos:
						case Ln:
						case Exp:
						case Negative:
							break;
						default:
							return 2;
					}
					break;
				case Close:
					j--;
					if (i == n - 1) break;
					if (datas[i + 1].is_num()) return 3;
					switch (datas[i + 1].getop())
					{
						case Add:
						case Del:
						case Mult:
						case Div:
						case Close:
							break;
						default:
							return 3;
					}
					break;
				case Sin:
				case Cos:
				case Ln:
				case Exp:
					if (i == n - 1) return 7;
					if (datas[i + 1].is_num() || (datas[i + 1].getop() != Operator::Open)) return 8;
					break;
				default:
					if (i == n - 1) return 7;
					if (!datas[i + 1].is_op()) break;
					switch (datas[i + 1].getop())
					{
						case Open:
						case Sin:
						case Cos:
						case Ln:
						case Exp:
						case Negative:
							break;
						default:
							return 4;
					}
					break;
			}
			if (j < 0) return 5;
		}
	}
	return j == 0 ? 0 : 6;
}
double find_des(Data* datas, int count)
{
	TStack<Data> stack;
	Data data;
	double x1, x2;
	for (int i = 0; i < count; i++)
	{
		if (datas[i].is_num())
		{
			stack.push(datas[i]);
			continue;
		}
		switch (datas[i].getop())
		{
			case Add:
				x2 = (stack.pop()).getn();
				x1 = (stack.pop()).getn();
				data = x1 + x2;
				break;
			case Del:
				x2 = (stack.pop()).getn();
				x1 = (stack.pop()).getn();
				data = x1 - x2;
				break;
			case Mult:
				x2 = (stack.pop()).getn();
				x1 = (stack.pop()).getn();
				data = x1 * x2;
				break;
			case Div:
				x2 = (stack.pop()).getn();
				x1 = (stack.pop()).getn();
				data = x1 / x2;
				break;
			case Negative:
				x2 = (stack.pop()).getn();
				data = -1 * x2;
				break;
			case Sin:
				x2 = (stack.pop()).getn();
				data = sin(x2);
				break;
			case Cos:
				x2 = (stack.pop()).getn();
				data = cos(x2);
				break;
			case Ln:
				x2 = (stack.pop()).getn();
				data = log(x2);
				break;
			case Exp:
				x2 = (stack.pop()).getn();
				data = exp(x2);
				break;
			default:
				break;
		}
		stack.push(data);
	}
	return (stack.pop()).getn();
}
