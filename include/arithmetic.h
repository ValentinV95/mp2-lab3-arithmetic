// объявление функций и классов для вычисления арифметических выражений

#include <string>
#include <cmath>
#include <stdexcept>
#include "stack.h" 

class Token {
private:
	double n;
	std::string op;
	int priority;
	// 0 = ")"
	// -1 - константа

	int checkPriority() {
		if (op == ")")  priority = 0;
		else if (op == "(") priority = 1;
		else if (op == "-") priority = 2;
		else if (op == "+") priority = 2;
		else if (op == "*") priority = 3;
		else if (op == "/") priority = 3;
		else if (op == "sin") priority = 4;
		else if (op == "cos") priority = 4;
		else if (op == "ln") priority = 4;
		else if (op == "exp") priority = 4;
		else throw std::logic_error(op);
	}
public:
	Token() {
		throw std::logic_error("Unexpected token");
	}

	Token(double x) {
		n = x;
		priority = -1;
	}

	Token(std::string s) {
		op = s;
		priority = checkPriority();
	}

	double getn()
	{
		return n;
	}

	std::string getop()
	{
		std::string s = "";
		s += op;
		return s;
	}


	bool isNum() {
		if (priority == -1)
			return true;
		return false;
	}

	bool isOp() {
		if (priority == -1)
			return false;
		return true;
	}

	int getPriority() {
		return priority;
	}


	void operator= (double x)
	{
		n = x;
		priority = -1;
	}
	void operator= (Token x)
	{
		if (x.isNum()) {
			n = x.getn();
			priority = -1;
		}
		else {
			op = x.getop();
			priority = checkPriority();
		}
	}
	void operator= (std::string x)
	{
		op = x;
		priority = checkPriority();
	}
};

Token* translationToRPE(std::string s) {
	// Разбиение на лексемы
	int i = 0, j = 0;
	int lBracket = 0;
	int rBracket = 0;
	Token tokens[s.length()];

	struct variable{
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

	while (s[i] != '\0') {
		if (s[i] == ' ')
			continue;
		if ((s[i] >= '0') && (s[i] <= '9')) {
			int x = 0;
			int d = 10;
			int tmp = 0;
			while ((s[i] >= '0') && (s[i] <= '9')) {
				tmp = (double)(s[i] - '0');
				x = x * 10 + tmp;
				i++;
			}
			if (s[i] == '.') {
				i++;
				while ((s[i] >= '0') && (s[i] <= '9')) {
					if ((s[i] >= '0') && (s[i] <= '9')) {
						tmp = (double)(s[i] - '0');
						x = x + tmp / d;
						i++;
						d = d * 10;
					}
				}
			}
			if ((s[i] >= '0') && (s[i] <= '9')) {
				x = 0;
				d = 10;
				while ((s[i] >= '0') && (s[i] <= '9')) {
					tmp = (double)(s[i] - '0');
					x = x * 10 + tmp;
					i++;
				}
				if (s[i] == '.') {
					i++;
					while ((s[i] >= '0') && (s[i] <= '9')) {
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
		}
		else if ((s[i] == 's') && (s[i + 1] == 'i') && (s[i + 2] == 'n')) {
			tokens[j++] = "sin";
			i = i + 3;
		}
		else if ((s[i] == 'c') && (s[i + 1] == 'o') && (s[i + 2] == 's')) {
			tokens[j++] = "cos";
			i = i + 3;
		}
		else  if ((s[i] == 'l') && (s[i + 1] == 'n')) {
			tokens[j++] = "ln";
			i = i + 2;
		}
		else  if ((s[i] == 'e') && (s[i + 1] == 'x') && (s[i + 2] == 'p')) {
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
		else if(s[i] == 'y') {
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
		else if(s[i] == 'z'){
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
		else  if (s[i] == '+') {
			tokens[j] = "+";
			j++;
			i++;
		}
		else  if (s[i] == '*') {
			tokens[j] = "*";
			j++;
			i++;
		}
		else  if (s[i] == '/') {
			tokens[j] = "/";
			j++;
			i++;
		}
		else if (s[i] == '-') {
			if (tokens[j - 1].isOp() && tokens[j - 1].getop() != ")") {
				tokens[j++] = "un-";
				i++;
			}
			else {
				tokens[j] = "-";
				j++;
				i++;
			}
		}
		else if (s[i] == '(') {
			tokens[j] = "(";
			j++;
			i++;
		}
		else if (s[i] == ')') {
			tokens[j] = ")";
			j++;
			i++;
		}
		else 
		throw std::logic_error("unexpected expression");
	}
	return tokens;

	// Перевод в ОПЗ
	Token* arr;
	arr = new Token[j];
	Stack<Token> t;
	int l = 0;

	for (int k = 0; k < j; k++)
	{
		if (arr[k].isNum())
		{
			arr[l] = arr[k];
			l++;
		}
		else
			if (t.IsEmpty())
			{
				t.push(arr[k]);
			}
			else
			{
				if (arr[k].getPriority() == 1)
				{
					t.push(arr[k]);
				}
				else
				{
					while (!(t.IsEmpty()) && (arr[k].getPriority() <= t.show().getPriority()))
					{
						if (t.show().getPriority() == 1)
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
					if (arr[k].getPriority() != 0)
					{
						t.push(arr[k]);
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


