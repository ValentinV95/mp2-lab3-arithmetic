// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#pragma once
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "stack.h"

using namespace std;
struct Lexem
{
	int priority; // приоритет лексемы
	string type; // тип лексемы
	string lexm; // значение лексемы

	Lexem& operator = (const Lexem& other)
	{
		this->priority = other.priority;
		this->lexm = other.lexm;
		this->type = other.type;

		return *this;
	}
};

class PolishNotation
{
private:
	string formula;//выражение, вводимое пользователем
	vector <Lexem> polish;//вектор дл€ польской нотации
	vector <Lexem> l;//вектор дл€ хранени€ промежуточного массива лексем
public:
	PolishNotation(string s);
	void CorrectionChecker(string s);
	double BinaryCalculate(double a, double b, string s);
	void TranslationToPolishNotation();
	void PrintPolishNotation();
	double PolishNotationCalculate();
}; 