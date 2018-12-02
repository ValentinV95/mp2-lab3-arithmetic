// объявление функций и классов для вычисления арифметических выражений

#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <map>
#include <string>
#include <vector>
#include "stack.h"

// Перечислимый тип "токен"
enum Token
{
	NUM, // Число
	VAR, // Переменная
	OP, // Оператор
	LP, // Левая скобка
	RP // Правая скобка
};

// Класс "лексема"
class Lexem
{
	std::string _value;
	Token _token;
public:
	Lexem(std::string value, Token token);
	std::string& value();
	Token token();
};

// Класс "выражение"
class Expression
{
	std::vector<Lexem> lexems; // Список лексем

public:
	// Конструктор
	Expression() {}

	// Приоритет операций
	static int priority(char op);

	// Ввод значений переменной
	static void input(std::map<std::string, double>& vars, std::string& op, double& d);

	// Перевод в обратную польскую запись
	std::string toRPN();

	// Вычисление значения по обратной польской записи
	double eval(std::string rpn);

	// Парсинг выражения
	bool parse(std::string expr, bool print = false);
};

#endif /* ARITHMETIC_H */



