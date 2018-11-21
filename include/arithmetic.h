// объявление функций и классов для вычисления арифметических выражений
#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"

using namespace std;

class TPostfix
{
	string infix;
	string postfix;
	int Priority(char c);
	int IsDigit(char c);
	int CheckOp(char c);
public:

	TPostfix(string _infix) // Конструктор
	{
		infix = _infix;
	}
	string GetInfix() { return infix; }
	int FormulaChecker(int bracket[], int &Size); // Проверка правильности
	string GetPostfix() { return postfix; }
	string ToPostfix();
	double Calculate(string postfix); // Ввод переменных, вычисление по постфиксной форме
};

#endif
