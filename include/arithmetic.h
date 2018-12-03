
// объявление функций и классов для вычисления арифметических выражений
#pragma once
#include <iostream>
#include "cstdlib"
#include <string>
#include <vector>
#ifndef arithmetic_H
#define arithmetic_H


#include "cstdio"
#include "Stack.h"



enum operation {PLUS, MINUS, MULT, DIV, O_BRACE, C_BRACE,UN_MINUS};

typedef operation Op;

struct Lecsema
{
	bool isNum;//k=1 число, если k=0  операция
	double a;//число
	Op b;//операция
};

class TFormula
{
private:
	string formula;//выражение
	vector <Lecsema> lecs;//вектор лексем
	vector <Lecsema> rev_lecs;//обратная польская запись
	int n;//количество лексем в выражении

public:
	TFormula();//конструктор
	TFormula(string s);//конструктор с параметром
	~TFormula();//деструктор
	void Write();//запись выражения пользователем
	bool Checker();//проверка корректности вводимого выражения
	void Converter();//разбор выражения на вектор лексем
	void Postfix_Entry();//перевод в обратную польскую запись
	double Calculator();//вычисление выражения
};

#endif // !arithmetic_H