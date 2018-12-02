#include <string>
#include <vector>
#include <iostream>
#include "stack.h"

using std::string;
using std::vector;

const string allowedTerms = "0123456789.()+-/* ";

class Term
{
private:
	char operation;
	double value;
	bool type;
public:
	Term() = default;
	Term(const double &_value) {
		value = _value;
		type = true;
	}
	Term(const char &_operation) {
		operation = _operation;
		type = false;
	}
	void printTerm() {
		if (type) {
			std::cout << value;
		}
		else {
			std::cout << operation;
		}
	}
	double getValue() { return value; }
	char getOperation() { return operation; }
	bool getType() { return type; }

	int priority();
};

class Arithmetic 
{
private:
	vector<Term> terms;
public:
	Arithmetic() = default;

	void stringToTerm(string &expression);
	void termToPostfix();
	double calculate();
	void print() {
		for (size_t i = 0; i < terms.size(); i++) {
			Term lexeme(terms[i]);
			lexeme.printTerm();
		}
	}
};

bool checkBrackets(const string &s);
bool checkSymbols(const string &s);
bool isCorrect(const string &s);
