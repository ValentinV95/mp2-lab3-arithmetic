// объявление функций и классов для вычисления арифметических выражений

#include <string>
#include <cmath>
#include <stdexcept>
#include "stack.h" 
#include <iostream>

class Token
{
private:
	double n;
	std::string op;
	bool num;
public:
	Token() noexcept
	{

	}
	Token(double x) noexcept
	{
		n = x;
		num = true;
	}
	Token(std::string s)
	{
		op = s;
		num = false;
	}
	~Token() noexcept
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

	bool isNum() noexcept
	{
		return num;
	}

	bool isOp() noexcept
	{
		return !num;
	}

	int getPriority()
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
		num = true;
	}
	void operator= (Token x)
	{
		if (x.isNum())
		{
			n = x.getn();
			num = true;
		}
		else
		{
			op = x.getop();
			num = false;
		}
	}
	void operator= (std::string x)
	{
		op = x;
		num = false;
	}
};


double solve(Token* arr, int n) {
	Stack<Token> s;
	Token t;
	double x1, x2;
	for (int i = 0; i < n; i++) {
		if (arr[i].isNum()) {
			s.push(arr[i]);
		}
		else {
			if (arr[i].getop() == "+") {
				x2 = (s.pop()).getn();
				x1 = (s.pop()).getn();
				t = x1 + x2;
			}
			if (arr[i].getop() == "-") {
				x2 = (s.pop()).getn();
				x1 = (s.pop()).getn();
				t = x1 - x2;
			}
			if (arr[i].getop() == "*") {
				x2 = (s.pop()).getn();
				x1 = (s.pop()).getn();
				t = x1 * x2;
			}
			if (arr[i].getop() == "/") {
				x2 = (s.pop()).getn();
				x1 = (s.pop()).getn();
				t = x1 / x2;
			}
			if (arr[i].getop() == "un-") {
				x2 = (s.pop()).getn();
				t = -1 * x2;
			}
			if (arr[i].getop() == "sin") {
				x2 = (s.pop()).getn();
				t = sin(x2);
			}
			if (arr[i].getop() == "cos") {
				x2 = (s.pop()).getn();
				t = cos(x2);
			}
			if (arr[i].getop() == "ln") {
				x2 = (s.pop()).getn();
				t = log(x2);
			}
			if (arr[i].getop() == "exp") {
				x2 = (s.pop()).getn();
				t = exp(x2);
			}
			s.push(t);
		}
	}
	return (s.pop()).getn();
}

double translationToRPE(std::string s)
{
	int i = 0, j = 0;
	int lBrackets = 0;
	int rBrackets = 0;
	Token* tokens = new Token[s.length()];
	double tmp, x, d;

	struct variable {
		bool avail = false;
		double val;
	};
	struct variable sX;
	struct variable sY;
	struct variable sZ;
	struct variable sK;
	struct variable sN;
	struct variable sT;

	if (s[i] == '-')
	{
		tokens[j++] = -1;
		tokens[j++] = "*";
		i++;
	}
	while (s[i] != '\0') //конец строки
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
			tokens[j] = x;
			j++;
		}
		else if ((s[i] == 's') && (s[i + 1] == 'i') && (s[i + 2] == 'n'))
		{
			if (s[i + 3] != '(')
				throw("Arguments of mathematical functions must be written in parentheses");
			tokens[j++] = "sin";
			i = i + 3;
		}
		else if ((s[i] == 'c') && (s[i + 1] == 'o') && (s[i + 2] == 's'))
		{
			if (s[i + 3] != '(')
				throw("Arguments of mathematical functions must be written in parentheses");
			tokens[j++] = "cos";
			i = i + 3;
		}
		else  if ((s[i] == 'l') && (s[i + 1] == 'n'))
		{
			if (s[i + 2] != '(')
				throw("Arguments of mathematical functions must be written in parentheses");
			tokens[j++] = "ln";
			i = i + 2;
		}
		else  if ((s[i] == 'e') && (s[i + 1] == 'x') && (s[i + 2] == 'p'))
		{
			if (s[i + 3] != '(')
				throw("Arguments of mathematical functions must be written in parentheses");
			tokens[j++] = "exp";
			i = i + 3;
		}
		else if (s[i] == 'x') {
			if (sX.avail == true)
				tokens[j++] = sX.val;
			else {
				std::cout << "input " << s[i] << std::endl;
				double value;
				std::cin >> value;

				sX.val = value;
				sX.avail = true;
				tokens[j++] = value;
			}
		}
		else if (s[i] == 'y') {
			if (sY.avail == true)
				tokens[j++] = sY.val;
			else {
				std::cout << "input " << s[i] << std::endl;
				double value;
				std::cin >> value;

				sY.val = value;
				sY.avail = true;
				tokens[j++] = value;
			}
		}
		else if (s[i] == 'z') {
			if (sZ.avail == true)
				tokens[j++] = sZ.val;
			else {
				std::cout << "input " << s[i] << std::endl;
				double value;
				std::cin >> value;

				sZ.val = value;
				sZ.avail = true;
				tokens[j++] = value;
			}
		}
		else if (s[i] == 'k') {
			if (sK.avail == true)
				tokens[j++] = sK.val;
			else {
				std::cout << "input " << s[i] << std::endl;
				double value;
				std::cin >> value;

				sK.val = value;
				sK.avail = true;
				tokens[j++] = value;
			}
		}
		else if (s[i] == 'n') {
			if (sN.avail == true)
				tokens[j++] = sN.val;
			else {
				std::cout << "input " << s[i] << std::endl;
				double value;
				std::cin >> value;

				sN.val = value;
				sN.avail = true;
				tokens[j++] = value;
			}
		}
		else if (s[i] == 't') {
			if (sT.avail == true)
				tokens[j++] = sT.val;
			else {
				std::cout << "input " << s[i] << std::endl;
				double value;
				std::cin >> value;

				sT.val = value;
				sT.avail = true;
				tokens[j++] = value;
			}
		}
		else if (s[i] == '+')
		{
			tokens[j] = "+";
			j++;
			i++;
		}
		else  if (s[i] == '*')
		{
			tokens[j] = "*";
			j++;
			i++;
		}
		else  if (s[i] == '/')
		{
			tokens[j] = "/";
			j++;
			i++;
		}
		else if (s[i] == '-')
		{
			if (tokens[j - 1].isOp() && tokens[j - 1].getop() != ")")
			{
				tokens[j++] = "un-";
				i++;
			}
			else
			{
				tokens[j] = "-";
				j++;
				i++;
			}
		}
		else if (s[i] == '(')
		{
			if(s[i+1] == ')') 
				throw std::logic_error("Error with brackets");
			tokens[j] = "(";
			j++;
			i++;
			lBrackets++;
		}
		else if (s[i] == ')')
		{
			if(s[i + 1] != '\0')
				if((s[i + 1] != '+') && (s[i + 1] != '-') && (s[i + 1] != '*') && (s[i + 1] != '/') & (s[i + 1] != ')'))
					throw std::logic_error("Invalid token after the brackets");
			tokens[j] = ")";
			j++;
			i++;
			rBrackets++;
		}
		else
		{
			throw ("ERROR");
		}
	}
	if (lBrackets != rBrackets) {
		throw ("Error with brackets");
	}

	Token* arr;           // перевод в ОПЗ
	arr = new Token[j];
	Stack<Token> t;
	int l = 0;

	for (int k = 0; k < j; k++)
	{
		if (tokens[k].isNum())
		{
			arr[l] = tokens[k];
			l++;
		}
		else
			if (t.IsEmpty())
			{
				t.push(tokens[k]);
			}
			else
			{
				if (tokens[k].getPriority() == 1)
				{
					t.push(tokens[k]);
				}
				else
				{
					while (!(t.IsEmpty()) && (tokens[k].getPriority() <= t.value().getPriority()))
					{
						if (t.value().getPriority() == 1)
						{
							t.pop();
							break;
						}
						else
						{
							arr[l] = t.pop();
							l++;
						}
					}
					if (tokens[k].getPriority() != 0)
					{
						t.push(tokens[k]);
					}
				}
			}
	}
	while (!(t.IsEmpty()))
	{
		arr[l] = t.pop();
		l++;
	}
	return solve(arr, l);
}

