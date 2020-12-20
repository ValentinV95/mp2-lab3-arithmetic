//объ€вление функций и классов дл€ вычислени€ арифметических выражений

#include <string>
#include <iostream>
#include <cstdlib>

#include <vector>
#include <unordered_map>

#include "stack.h"

using namespace std;

class Term
{
public:	
	Term() = default;

	Term(double _num);
	Term(char _operation);
	Term(string _alternating);

	double getNumber();
	char getOperation();
	string getAlternating();
	size_t getTypeLexeme();

	size_t getPriorityOperation();

	void printT();

private:
	double number;
	char operation;
	string alternating;
	size_t typeLexeme;
};

class Arithmetic
{
public:
	void translateStrToTerm(string str);
	void TermToPolishNote();
	void calculate();

	void PrintVectP();
	void PrintVecT();

	double GetResult();

private:
	double result = 0;
	vector<Term> term;
	vector<Term> polishNote;
};
