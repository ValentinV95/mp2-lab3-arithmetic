// объявление функций и классов для вычисления арифметических выражений

#ifndef _ARITHMETIC_
#define _ARITHMETIC_

#include <vector>
#include <map>
#include "string"
using namespace std;

enum  TTag { NUMBER, OPERATION, BRACKET, VARIABLE };

class Lexeme
{
	TTag Type;
	double Value;
	string Name;

public:

	Lexeme();
	Lexeme(TTag, double);
	Lexeme(TTag, string, double = 0.0);
	~Lexeme();
	TTag GetType();
	double GetValue();
	string GetName();
	void SetValue(double);
	bool operator==(const Lexeme&)const;
	bool operator!=(const Lexeme&)const;
};

class Error
{
	string err;

public:

	Error();
	Error(string);
	~Error();
	void Print();

};

extern void Set_values(vector<Lexeme>& exp);
extern double Expression_result(vector<Lexeme> postf);
extern vector<Lexeme> Convert_to_postfix_notation(vector<Lexeme> pars_exp);
extern bool Checking_correctness(vector<Lexeme> exp);
extern vector<Lexeme> Convert_to_lexeme_array(string exp);

#endif