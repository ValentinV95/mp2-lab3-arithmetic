
#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <iostream>
#include <string>
#include <map>

enum Lex_Type { OP, OB, CB, VALUE, FUNC, Perem, WR };

struct Lexem
{
	std::string s;
	Lex_Type tp;
	bool may_unary;
	int pos;
};

class Calculate
{
private:
	std::string input;
	Lexem *lex;
	int size;
public:
	Calculate(const std::string& inp);
	bool is_op(char c);
	bool delim(char c);
	bool is_digit(char c);
	bool Prover1();
	bool Prover2();
	bool Prover3();
	double val_func(std::string c, int i);
	bool is_function(const std::string& c);
	void Razb();
	void PerevodVPol();
	double calc();
	int priority(char op);
	double oper(double a, double b, char m, int i);
};

#endif ARITHMETIC_H
