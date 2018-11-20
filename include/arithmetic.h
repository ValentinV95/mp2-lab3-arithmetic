// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#ifndef __POSTFIX_H__
#define __POSTFIX_H__
#include <string>
#include "stack.h"
using namespace std;
class TPostfix {
	string infix;
	string postfix;
	TStack<string> _T;
	string trimString(string source);
	string convertString(string source);
	double decodeVal(string value);
	string getVal(string& source, size_t start);
	void ToPostfixIteration(TStack<string>& _T, string source);
public:
	TPostfix(string base = "") : _T(100) 
	{
		infix = convertString(base);
		postfix = ToPostfix();
	}
	TPostfix(TPostfix& c) : _T(100) 
	{
		infix = c.infix;
		postfix = ToPostfix();
	}
	string GetInfix()
	{ 
		return infix; 
	}
	string GetPostfix() 
	{ 
		return postfix;
	}
	string ToPostfix(string source = "\0");
	double Calculate(string source = "\0");
	void SetInfix(string base);
};
#endif