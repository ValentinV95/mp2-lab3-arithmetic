// реализация функций и классов для вычисления арифметических выражений
#include "../include/arithmetic.h"

map<string, double> variables;

bool isDot(const char& ch)
{
	bool flag = (ch == '.');
	return flag;
}

bool isOperation(const char& ch)
{
	bool flag = (ch == '+' || ch == '*' ||
		ch == '-' || ch == '/');
	return flag;
}

bool isOperation(const Token& tok)
{
	bool flag = (tok == MUL) || (tok == PLUS) ||
		(tok == MINUS) || (tok == DIV);
	return flag;
}

bool isBracket(const char& ch)
{
	bool flag = (ch == '(' || ch == ')');
	return flag;
}

bool isFunction(const string& name)
{
	bool flag = (name == "sin") || (name == "cos") ||
		(name == "exp") || (name == "log");
	return flag;
}

bool isFunction(const Token& tok)
{
	bool flag = (tok == SIN) || (tok == COS) ||
		(tok == EXP) || (tok == LOG) || (tok == UNARY_MINUS);
	return flag;
}

int getPriority(const Token& tok)
{
	int priority;
	if (tok == PLUS || tok == MINUS) 
	{
		priority = 0;
	}
	else if (tok == MUL || tok == DIV)
	{
		priority = 1;
	}
	else if (tok == RP || tok == LP) 
	{
		priority = -1;
	}
	else if (isFunction(tok)) 
	{
		priority = 2;
	}
	else {
		throw Exception("cannot return priority");
	}
	return priority;
}

double stringToDouble(string str, size_t* pos)
{
	string strNumber; 

	while (isdigit(str[*pos])) 
	{
		strNumber.push_back(str[(*pos)++]);
	}

	if (isDot(str[(*pos)])) 
	{
		strNumber.push_back(str[(*pos)++]);
		
		while (isdigit(str[(*pos)])) 
		{
			strNumber.push_back(str[(*pos)++]);
		}
	}

	double res = atof(strNumber.c_str());

	(*pos)--; // теперь pos указывает на последную цифру в числе

	return res;
}

Lexems convertToArrayLexem(string str)
{
	Lexems lexemsArray;
	size_t length = str.length();

	for (size_t i = 0; i < length; i++)
	{
		if (isspace(str[i]))
		{
			continue;
		}
		else if (isdigit(str[i]) || isDot(str[i])) 
		{
			// если i-ый символ строки - цифра
			// добавляем в поле tokens значение NUMBER
			lexemsArray.tokens.push_back(NUMBER);

			double val = stringToDouble(str, &i);

			lexemsArray.values.push(val);
		}
		else if (isOperation(str[i]) || isBracket(str[i])) 
		{
			// преобразовываем char в Token и добавляем в tokens
			Token tok = Token(str[i]);

			if (str[i] == '-' && !lexemsArray.tokens.empty())
			{
				// обрабатываем случай унарного минуса
				if (lexemsArray.tokens.back() == LP || isOperation(lexemsArray.tokens.back())) 
				{
					tok = UNARY_MINUS;
				}
			}
			else if (str[i] == '-' && i == 0) 
			{
				tok = UNARY_MINUS;
			}

			lexemsArray.tokens.push_back(tok);
		}
		else if (isalpha(str[i])) 
		{
			string name;

			while (isalnum(str[i])) 
			{
				name.push_back(str[i++]);
				if (i >= length) 
				{
					break;
				}
				else if (isFunction(name)) 
				{
					break;
				}
			}
			i--;

			if (name == "sin") 
			{
				lexemsArray.tokens.push_back(SIN);
			}
			else if (name == "cos")
			{
				lexemsArray.tokens.push_back(COS);
			}
			else if (name == "exp")
			{
				lexemsArray.tokens.push_back(EXP);
			}
			else if (name == "log")
			{
				lexemsArray.tokens.push_back(LOG);
			}
			else
			{
				double val;
				if (variables.count(name) >= 1) 
				{
					val = variables[name];
				}
				else 
				{
					cout << "enter variable value " << name << " = ";
					cin >> val;
					variables[name] = val;
				}

				lexemsArray.tokens.push_back(NUMBER);
				lexemsArray.values.push(val);
			}

		}
		else 
		{
			string error = "invalid character";
			error += " '";
			error += str[i];
			error += "'";
			throw Exception(error);
		}
	}

	return lexemsArray;
}

bool isCorrect(const Lexems& lexemsArray)
{
	int counterBracket = 0;

	Token first = lexemsArray.tokens.front();

	if (first == RP) {
		throw Exception("closing bracket cannot be at the beginning");
	}
	else if (isOperation(first))
	{
		throw Exception("operation cannot be at the beginning");
	}

	Token last = lexemsArray.tokens.back();

	if (isOperation(last)) 
	{
		throw Exception("operation cannot be at the end");
	}
	else if (last == LP)
	{
		throw Exception("opening bracket cannot be at the end");
	}
	else if (last == UNARY_MINUS) 
	{
		throw Exception("unary minus cannot be at the end");
	}

	for (size_t i = 0; i < lexemsArray.tokens.size() - 1; i++) 
	{

		Token curr = lexemsArray.tokens[i];
		Token next = lexemsArray.tokens[i + 1];

		if ((curr == NUMBER) && (next == LP)) 
		{
			throw Exception("'(' cannot be after number");
		}
		else if ((curr == NUMBER) && (next == NUMBER)) 
		{
			throw Exception("number cannot be after number");
		}
		else if ((curr == NUMBER) && isFunction(next)) 
		{
			throw Exception("function cannot be after number");
		}

		if (isFunction(curr) && (curr != UNARY_MINUS) && (next != LP))
		{
			throw Exception("after funciton can be only '('");
		}
		else if ((curr == UNARY_MINUS) && (next != NUMBER) && (next != LP)) 
		{
			throw Exception("after unary minus can be only number or '('");
		}

		if (isOperation(curr) && (next == RP)) {
			throw Exception("')' cannot be after operation");
		}
		else if (isOperation(curr) && isOperation(next)) 
		{
			throw Exception("operation cannot be after operation");
		}

		if ((curr == RP) && ((next != RP) && !isOperation(next))) 
		{
			throw Exception("after ')' can be only operation or ')'");
		}

		if ((curr == LP) && (next == RP)) 
		{
			throw Exception("')' cannot be after '('");
		}
		else if ((curr == LP) && isOperation(next)) {
			throw Exception("operation cannot be after '('");
		}

		if (next == RP) 
		{
			counterBracket++;
		}
		else if (curr == LP) 
		{
			counterBracket--;
		}
	}

	if (counterBracket > 0) 
	{
		throw Exception("closing brackets more than opening brackets");
	}
	else if (counterBracket < 0) 
	{
		throw Exception("opening brackets more than closing brackets");
	}

	return true;
}

Lexems convertToRpn(const Lexems& lexemArray)
{
	Lexems rpn; // результирующий массив лексем 

	TStack<Token> operations; 
	queue<double> vals = lexemArray.values; 

	for (auto it : lexemArray.tokens) 
	{

		if (it == NUMBER) 
		{
			// если встретилось число, добавляем его в результирующий массив
			rpn.tokens.push_back(NUMBER);
			// извлкаем из очереди число
			double val = vals.front();
			vals.pop();
			// добавляем число в очередь значений 
			rpn.values.push(val);
		}
		else if ((it == LP) || isFunction(it)) 
		{
			operations.push(it);
		}
		else if (it == RP) 
		{
			Token top = operations.getTop();
			while (top != LP) 
			{
				rpn.tokens.push_back(operations.pop());
				top = operations.getTop();
			}

			operations.pop();
		}
		else if (isOperation(it)) 
		{
			while (!operations.isEmpty())
			{
				Token top = operations.getTop();

				if (getPriority(top) < getPriority(it)) 
				{
					break;
				}

				rpn.tokens.push_back(operations.pop());
			}

			operations.push(it);
		}
		else 
		{
			throw Exception("cannot convert to rpn. Invalid lexem");
		}

	}

	// записываем в опз, операции которые оставлись в стеке
	while (!operations.isEmpty()) 
	{
		rpn.tokens.push_back(operations.pop());
	}

	return rpn;
}



double calcBinaryOperation(const double& op1, const double& op2, const Token& tok)
{
	if (tok == PLUS) 
	{
		return op1 + op2;
	}
	else if (tok == MINUS)
	{
		return op1 - op2;
	}
	else if (tok == MUL)
	{
		return op1 * op2;
	}
	else if (tok == DIV) 
	{
		if (op2 == 0.0) 
		{
			throw Exception("divide by null");
		}
		return op1 / op2;
	}
	else
	{
		throw Exception("non-existent operation");
	}
}


double calcFunc(const double& arg, const Token& tok)
{
	if (tok == SIN) 
	{
		return sin(arg);
	}
	else if (tok == COS) 
	{
		return cos(arg);
	}
	else if (tok == EXP) 
	{
		return exp(arg);
	}
	else if (tok == LOG)
	{
		return log(arg);
	}
	else if (tok == UNARY_MINUS) 
	{
		return (-1.0)*arg;
	}
	else 
	{
		throw Exception("cannot calculate function: invalid function");
	}
}

double computeResult(const Lexems& rpn)
{
	TStack<double> operands; 
	Lexems lexemRpn;
	lexemRpn.tokens = rpn.tokens;
	lexemRpn.values = rpn.values;

	for (auto it : lexemRpn.tokens) 
	{
		if (it == NUMBER) 
		{
			double val = lexemRpn.values.front();
			lexemRpn.values.pop();
			operands.push(val);
		}
		else if (isFunction(it)) 
		{
			double arg = operands.pop();

			double fx = calcFunc(arg, it);

			operands.push(fx);
		}
		else 
		{
			double op2 = operands.pop();
			double op1 = operands.pop();

			double res = calcBinaryOperation(op1, op2, it);
			operands.push(res);
		}
	}

	// возращаем результат, который лежит на вершине стека
	return operands.pop();
}