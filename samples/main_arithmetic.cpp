// реализация пользовательского приложения

#include <algorithm>
#include <iostream>
#include <string>
#include "../include/arithmetic.h"

int main(int argc, char *argv[])
{
	setlocale(LC_CTYPE, "Russian");

	std::cout << "Введите выражение: ";
	std::string expr;
	std::getline(std::cin, expr); // Ввод выражения
	std::string::iterator end_pos = std::remove(expr.begin(), expr.end(), ' '); // Удаление пробелов
	expr.erase(end_pos, expr.end());
	std::cout << "Выражение: " << expr << std::endl;

	Expression e;
	if (e.parse(expr, true)) // Если строка корректна
	{
		// Вычисление выражения 
		std::string rpn = e.toRPN();
		std::cout << "Обратная польская запись: " << rpn << std::endl;
		std::cout << "Результат выражения: " << e.eval(rpn) << std::endl;
	}

	return 0;
}