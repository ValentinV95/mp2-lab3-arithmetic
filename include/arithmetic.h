// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#ifndef _ARITHMETIC_H_
#define _ARITHMETIC_H_
#include <string>
#include <vector>
#include <set>
using namespace std;


class Lexeme
{
private:
	double number;
	char op;
	int flag;
public:
	Lexeme() {};
	Lexeme(char, int);
	Lexeme(double, int);
	void Set(char, int);
	void Set(double, int);
	void Print();
	int Flag() { return flag; };
	double Number() { return number; };
	char Op() { return op; };
	Lexeme& operator=(Lexeme&);
	~Lexeme() {};

};

Lexeme* Polish(string, int &);
int prt(char op);
double result(Lexeme*, int);

bool mistake(string);




#endif _ARITHMETIC_H_