// реализация функций и классов для вычисления арифметических выражений

#include "../include/arithmetic.h"
#include <algorithm>
#include <iostream>

Lexem::Lexem(std::string value, Token token)
{
	_value = value;
	_token = token;
}

std::string& Lexem::value()
{
	return _value;
}

Token Lexem::token()
{
	return _token;
}

int Expression::priority(char op)
{
	switch (op)
	{
		case '(': // У открывающей скобки наименьший приоритет
			return 1;
		case '+': // У + и - выше
		case '-':
			return 2;
		case '*': // У * и / самый высокий приоритет
		case '/':
			return 3;
		default:
			return 0;
	}
}

// Ввод значений переменной
void Expression::input(std::map<std::string, double>& vars, std::string& op, double& d)
{
	if (isalpha(op[0]) || (op[0] == '-' && isalpha(op[1]))) // Если строка - переменная
	{
		if (vars.find(op) == vars.end()) // Если не содержится в ассоциативном массиве
		{
			std::cout << "Введите значение переменной " << ((op[0] == '-') ? op.substr(1) : op) << ": ";
			std::cin >> vars[op]; // Ввод значения в ассоциативный массив
			if (op[0] == '-') // Если вначале минус
				vars[op] *= -1; // То умножаем на -1
			d = vars[op]; // Запись в переменную
		}
	}
	else // Иначе
		d = std::atof(op.c_str()); // Преобразование строки в число
}

// Перевод в обратную польскую запись
std::string Expression::toRPN()
{
	std::string rpn; // Результирующая строка
	Stack<std::string> operands; // Стек для операндов
	for (size_t i = 0; i < lexems.size(); i++) // Цикл по всем элементам
	{
		Token token = lexems[i].token();
		std::string value = lexems[i].value();
		if (token == Token::VAR || token == Token::NUM) // Если токен - переменная или число
			rpn += value + " "; // То просто добавляем в строку
		else if (token == Token::OP) // Если токен - оператор
		{
			if (operands.IsEmpty()) // Если стек пуст
				operands.push(value); // То просто добавляем в стек
			else
			{
				// Пока стек не пуст и приоритет вершинного элемента стека выше текущего
				while (!operands.IsEmpty() && priority(operands.Value()[0]) >= priority(value[0]))
					rpn += operands.pop() + " "; // То добавляем в строку из стека
				operands.push(value); // Добавляем оператор в стек
			}
		}
		else if (token == Token::LP) // Если токен - левая скобка
			operands.push(value); // Добавляем скобку в стек
		else // Если токен - правая скобка
		{
			while (operands.Value() != "(") // Пока не найдена левая скобка
				if (operands.Value() != ")") // Все нескобочные элементы добавляем в строку
					rpn += operands.pop() + " ";
			operands.pop(); // Удаляем левую скобку
		}
	}

	while (!operands.IsEmpty()) // Остаток стека добавляем в строку
		rpn += operands.pop() + " ";

	rpn.pop_back();
	return rpn;
}

// Вычисление значения по обратной польской записи
double Expression::eval(std::string rpn)
{
	size_t cur = 0; // Текущий индекс
	Stack<std::string> st; // Стек переменных и чисел
	std::map<std::string, double> vars; // Массив пар "переменная-значение"
	while (cur < rpn.size()) // Пока строка не закончилась
	{
		if (rpn[cur] == ' ') // Если найден пробел
			cur++; // То переходим на следующий символ
		else if (isdigit(rpn[cur]) || (rpn[cur] == '-' && isdigit(rpn[cur + 1]))) // Если найдено число
		{
			std::string number;
			while (isdigit(rpn[cur]) || rpn[cur] == '.' || rpn[cur] == '-') // Собираем число
				number += rpn[cur++];
			st.push(number); // Добавляем в стек число
		}
		else if (isalpha(rpn[cur]) || (rpn[cur] == '-' && isalpha(rpn[cur + 1]))) // Если найдена переменная
		{
			std::string variable;
			while (isalpha(rpn[cur]) || rpn[cur] == '-') // Собираем переменную
				variable += rpn[cur++];
			st.push(variable); // Добавляем в стек переменную
		}
		else
		{
			std::string op2 = st.pop(), // Получаем два операнда
				op1 = st.pop();
			double d1, d2;
			input(vars, op2, d2); // Если переменные, получаем их значения
			input(vars, op1, d1);

			switch (rpn[cur]) // Выполняем текущую операцию
			{
				case '+':
					st.push(std::to_string(d1 + d2));
					break;
				case '-':
					st.push(std::to_string(d1 - d2));
					break;
				case '*':
					st.push(std::to_string(d1 * d2));
					break;
				case '/':
					st.push(std::to_string(d1 / d2));
					break;
			}
			cur++;
		}
	}
	
	if (isalpha(st.Value()[0]))
	{
		double d;
		input(vars, st.Value(), d);
		return d;
	}
	else
		return std::atof(st.pop().c_str());
}

// Парсинг выражения
bool Expression::parse(std::string expr, bool print)
{
	std::string::iterator end_pos = std::remove(expr.begin(), expr.end(), ' '); // Удаление пробелов
	expr.erase(end_pos, expr.end());
	lexems.clear();

	size_t cur = 0; // Текущий индекс
	std::string number; // Строка для числа и переменной
	Stack<int> indexes; // Стек индексов
	bool isParsed = true; // Корректна ли строка
	while (cur < expr.size()) // Пока строка не закончилась
	{
		if (expr[cur] == '(' || expr[cur] == ')'
			|| expr[cur] == '+' || expr[cur] == '*' || expr[cur] == '/')
		{
			if (expr[cur] == '(') // Если прочитана открывающая скобка
			{
				// Если начало строки или предыдущий токен - оператор или (
				if (lexems.size() == 0 || lexems[lexems.size() - 1].token() == Token::OP
					|| lexems[lexems.size() - 1].token() == Token::LP)
				{
					lexems.push_back(Lexem("(", Token::LP));
					indexes.push(cur); // Добавляем в стек индекс
				}
				else // Иначе сообщение об ошибке
				{
					if (print)
						std::cout << "Символ " << cur + 1 << ": " << "пропущен оператор!\n";
					isParsed = false;
				}
			}
			else if (expr[cur] == ')') // Если прочитана закрывающая скобка
			{
				// Если не начало строки и предыдущий токен - число, переменная или )
				if (lexems.size() > 0 && (lexems[lexems.size() - 1].token() == Token::NUM
					|| lexems[lexems.size() - 1].token() == Token::VAR
					|| lexems[lexems.size() - 1].token() == Token::RP))
				{
					if (indexes.IsEmpty()) // Если стек пуст
					{
						// Сообщение об ошибке
						if (print)
							std::cout << "Символ " << cur + 1 << ": " << "неверный порядок скобок!\n";
						isParsed = false;
					}
					else // Иначе
					{
						indexes.pop(); // Удаление из стека
						lexems.push_back(Lexem(")", Token::RP));
					}
				}
				else // Иначе сообщение об ошибке
				{
					if (print)
						std::cout << "Символ " << cur + 1 << ": " << "пропущено число или переменная!\n";
					isParsed = false;
				}
			}
			else // Иначе если оператор + * /
			{
				// Если начало строки или предыдущий токен - оператор
				if (lexems.size() == 0 || (lexems[lexems.size() - 1].token() == Token::OP))
				{
					// Сообщение об ошибке
					if (print)
						std::cout << "Символ " << cur + 1 << ":" << "пропущено число, переменная или скобка!\n";
					isParsed = false;
				}
				lexems.push_back(Lexem(std::string() + expr[cur], Token::OP));
			}
			cur++;
		}
		else if (expr[cur] == '-') // Если прочитан -
		{
			if (cur < expr.size() - 1 && expr[cur + 1] == '(')
			{
				lexems.push_back(Lexem("-1", Token::NUM));
				lexems.push_back(Lexem("*", Token::OP));
			}
			else if (lexems[lexems.size() - 1].token() == OP || lexems[lexems.size() - 1].token() == LP)
				number.push_back('-');
			else
				lexems.push_back(Lexem(std::string() + expr[cur], Token::OP));
			cur++;
			
			while (cur < expr.size() - 1 && expr[cur] == '-' && expr[cur + 1] == '-')
				cur += 2;
		}
		else if (isdigit(expr[cur])) // Если прочитана цифра
		{
			// Если начало строки или предыдущий токен - оператор или (
			if (lexems.size() > 0 && lexems[lexems.size() - 1].token() != Token::LP
				&& lexems[lexems.size() - 1].token() != Token::OP)
				//tokens.push_back(Token::NUM); // Добавляем токен число
				//else
			{
				// Иначе сообщение об ошибке
				if (print)
					std::cout << "Символ " << cur + 1 << ":" << "пропущена правая скобка или оператор!\n";
				isParsed = false;
			}

			int count = 0; // Количество точек
			while (isdigit(expr[cur]) || expr[cur] == '.') // Пока цифра или точка
			{
				if (expr[cur] == '.') // Если точка
				{
					count++;
					if (count == 2) // Если больше одной точки, то ошибка
						isParsed = false;
				}
				number.push_back(expr[cur++]); // Добавление цифры в число
			}

			lexems.push_back(Lexem(number, Token::NUM));
			number = ""; // Очистка строки
		}
		else if (isalpha(expr[cur])) // Если прочитана буква
		{
			// Если начало строки или предыдущий токен - оператор или (
			if (lexems.size() > 0 && lexems[lexems.size() - 1].token() != Token::LP
				&& lexems[lexems.size() - 1].token() != Token::OP)
			{
				if (print)
					std::cout << "Символ " << cur + 1 << ": " << "пропущена правая скобка или оператор!\n";
				isParsed = false;
			}

			while (isalpha(expr[cur]) || isdigit(expr[cur]))
				number.push_back(expr[cur++]);// Добавление цифры в число

			lexems.push_back(Lexem(number, Token::VAR));
			number = ""; // Очистка строки
		}
		else if (expr[cur++] == '.')
		{
			number = "0.";
		}
		else // Иначе сообщение об ошибке
		{
			if (print)
				std::cout << "Символ " << cur + 1 << ": " << "недопустимый символ!\n";
			isParsed = false;
			cur++;
		}
	}

	if (!indexes.IsEmpty()) // Если стек скобок не пуст, то ошибка
	{
		if (print)
			std::cout << "Символ " << cur << ": " << "неверный порядок скобок!\n";
		isParsed = false;
	}

	return isParsed;
}