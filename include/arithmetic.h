// объ€вление функций и классов дл€ вычислени€ арифметических выражений

// s   =  21 + (3 * 8 + 6):2 - 1

// res = |21|3|8|*|6|+|2|/|+|1|-|

#include <string>
#include <vector>
#include "stack.h"

using std::string;
using std::vector;

#define CONDITION (s[i] == zero[0]) || (s[i] == one[0]) || (s[i] == two[0]) || (s[i] == three[0]) || (s[i] == four[0]) || (s[i] == five[0]) || (s[i] == six[0]) || (s[i] == seven[0]) || (s[i] == eight[0]) || (s[i] == nine[0] || (s[i] == point[0]))

vector <string> stringToVector(string s) {
	vector <string> vect;
	vect.resize(100);
	int vectIndex = 0;
	string zero = "0", one = "1", two = "2", three = "3", four = "4",
		five = "5", six = "6", seven = "7", eight = "8", nine = "9", point = ".";
	unsigned i = 0;
	while (i < s.length()) {
		if (CONDITION) {
			while (CONDITION) {
				vect[vectIndex] += s[i];
				i++;
			}
			vectIndex++;
		}
		else {
			vect[vectIndex] = s[i];
			i++;
			vectIndex++;
		}
	}
	return vect;
}

void sToPostfix(vector <string> vect) {
	
}

enum Lexem {
	LBRACKET = '(', RBRACKET = ')', PLUS = '+', MINUS = '-', DIV = '/' , MULT = '*'
};

int priority(string s) {
	char c = s[0];
	switch (c) {
	case PLUS: case MINUS: return 0; break;
	case MULT: case DIV: return 1; break;
	default: return -1;
	}
}

double postfixToRes(vector <string> s) {
	Stack <string> stack;
	string stringOperand1, stringOperand2 , stringRes;
	double operand1, operand2, res;
	for (unsigned i = 0; i < s.size(); i++) {
		if ((s[i] != "*") && (s[i] != "-") && (s[i] != "+") && (s[i] != "/")) {
			stack.push(s[i]);
		}
		else {
			stringOperand2 = stack.pop();
			stringOperand1 = stack.pop();
			operand1 = stof(stringOperand1);
			operand2 = stof(stringOperand2);
			if (s[i] == "+") 
				res = operand1 + operand2;
			
			if (s[i] == "-") 
				res = operand1 - operand2;
			
			if (s[i] == "*") 
				res = operand1 * operand2;

			if (s[i] == "/") 
				res = operand1 / operand2;
			
			stringRes = std::to_string(res);
			stack.push(stringRes);
		}
	}
	string result = stack.pop();
	return stof(result);	
}
