#include "../include/arithmetic.h"
void Arithmetic::stringToTerm(string &expression)
{
	unsigned length = expression.length();
	string stringForNumber;
	double doubleNumber;
	unsigned i = 0;
	while (i < length) {
		if (expression[i] == ' ') i++; // пропускаем пробелы
		if (expression[i] == '+' || expression[i] == '*' || expression[i] == '/') { // обработка плюс, минус, деление
			Term operation(expression[i]);
			terms.push_back(operation);
			i++;
		}
		else if (expression[i] == '-') {
			if (i == 0) {
				Term unary_minus('_');
				terms.push_back(unary_minus);
				i++;
				continue;
			}
			if (i > 0) {
				if (terms[i - 1].getOperation() != ')' && terms[i - 1].getType() == false) {
					Term unary_minus('_');
					terms.push_back(unary_minus);
					i++;
				}
				else {
					Term minus('-');
					terms.push_back(minus);
					i++;
				}
			}
		}
		else if (expression[i] >= '0' && expression[i] <= '9' || (expression[i] == '.')) { // обработка чисел
			int pointCounter = 0;
			while (expression[i] >= '0' && expression[i] <= '9' || (expression[i] == '.')) {
				stringForNumber += expression[i];
				i++;
				if (expression[i] == '.') {
					pointCounter++;
				}
				if (pointCounter > 1) {
					throw "You have more than one point in the number";
				}
			}
			doubleNumber = stof(stringForNumber);
			Term number(doubleNumber);
			terms.push_back(number);
			stringForNumber.clear(); // очищаем строку для будущих значений
		}
		else if (expression[i] == ')' || expression[i] == '(') {
			Term bracket(expression[i]);
			terms.push_back(bracket);
			i++;
		}
	}
}
void Arithmetic::termToPostfix()
{
	unsigned size = terms.size();
	vector <Term> postfix;
	Stack <Term> operations;
	for (unsigned i = 0; i < size; i++) {
		if (terms[i].getType() == true) { // если нам встретилось число
			postfix.push_back(terms[i]); // помещаем число в выходную строку в виде Term
		}
		// если встретилась операция
		else {
			if (terms[i].getOperation() == '(') {
				operations.push(terms[i]);
				continue;
			}
			else if (terms[i].getOperation() == ')') {
				while (operations.getTop().getOperation() != '(') {
					postfix.push_back(operations.pop());
				}
				operations.pop(); // pop '('
				continue;
			}
			
			if (i > 0 && terms[i].getOperation() == '_' && terms[i].getOperation() == '_') {
				operations.push(terms[i]);
			}
			else {
				while (!operations.isEmpty() && operations.getTop().priority() >= terms[i].priority()) {
					postfix.push_back(operations.pop());
				}
				operations.push(terms[i]);
			}
		}
	}
	while (!operations.isEmpty()) {
		postfix.push_back(operations.pop());
	}
	terms = postfix;
}
double Arithmetic::calculate()
{
	Stack <Term> stack;
	Term termOperand1, termOperand2;
	double operand1, operand2, res;
	for (unsigned i = 0; i < terms.size(); i++) {
		if (terms[i].getType() == true) {
			stack.push(terms[i].getValue());
		}
		else if (terms[i].getOperation() == '_') {
			res = (-1)*stack.pop().getValue();
			stack.push(res);
			continue;
		}
		else {
			termOperand2 = stack.pop();
			termOperand1 = stack.pop();
			operand1 = termOperand1.getValue();
			operand2 = termOperand2.getValue();
			if (terms[i].getOperation() == '+')
				res = operand1 + operand2;
			if (terms[i].getOperation() == '-')
				res = operand1 - operand2;
			if (terms[i].getOperation() == '*')
				res = operand1 * operand2;
			if (terms[i].getOperation() == '/') {
				if (operand2 == 0) throw "Division by the zero";
				res = operand1 / operand2;
			}

			stack.push(res);
		}
	}
	Term result = stack.pop();
	return result.getValue();
}
bool checkBrackets(const string &s)
{
	bool flag = true;
	int count = 0, stringSize = s.length();
	for (int i = 0; i < stringSize; i++) {
		if (s[i] == '(') {
			count++;
			flag = false;
			if (i < stringSize && s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == '*' || s[i + 1] == '/') {
				throw "Operation after opening bracket";
			}
			if (i > 0 && s[i - 1] >= '0' && s[i] <= '9') {
				throw "Number before opening bracket";
			}
		}
		if (s[i] == ')') {
			count--;
			flag = true;
		}
	}
	return (flag == true && count == 0);
}
bool checkSymbols(const string &s)
{
	bool flag = false;
	int stringSize = s.length(), allowedTermsSize = allowedTerms.length();
	for (int i = 0; i < stringSize; i++) {
		for (int j = 0; j < allowedTermsSize; j++) {
			if (s[i] != allowedTerms[j]) {
				flag = false;
				continue;
			}
			else {
				flag = true;
				break;
			}
		}
		if (flag)
			continue;
		else return false;
	}
	return true;
}
bool isCorrect(const string &s)
{
	if (!checkBrackets(s)) {
		throw "Bracket in your expression are wrong";
	}
	else if (!checkSymbols(s)) {
		throw "You should use only allowed symbols: 0123456789.()+-/* ";
	}
	else if (s[0] == '+' || s[0] == '*' || s[0] == '/') {
		throw "Operation is on the first place in the expression";
	}
	else if (s[s.length() - 1] == '+' || s[s.length() - 1] == '-' || s[s.length() - 1] == '*' || s[s.length() - 1] == '/') {
		throw "Operation is at the end of the expression";
	}
	else return true;
}
int Term::priority()
{
	if (operation == '(' || operation == ')') { return 0; }
	else if (operation == '+' || operation == '-') { return 1; }
	else if (operation == '*' || operation == '/') { return 2; }
	else if (operation == '_') { return 3; }
	else throw "Priority problem";
}