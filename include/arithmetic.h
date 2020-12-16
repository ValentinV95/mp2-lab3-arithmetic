// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "stack.h"


struct Lexem
{
	int priority; // приоритет лексемы
	std::string type; // тип лексемы
	std::vector <char> lex; // значение лексемы
};

class PolishNotation
{
private:
	std::string formula;//выражение, вводимое пользователем
	std::vector <Lexem> l;//вектор дл€ польской нотации
public:
	PolishNotation(std::string s);
	std::vector <Lexem> TranslationToPolishNotation(std::string s);
	bool CorrectionChecker(std::string s);
	double PolishNotationCalculate(vector <Lexem> v);
}; 