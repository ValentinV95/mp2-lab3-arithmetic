#include "C:/Users/Роман/Documents/Lab3/mp2-lab3-arithmetic/include/arithmetic.h"

struct MINUS {
	bool unary;
	char operation = '-';
};

void Arithmetic::stringToTerm(string &expression) {
	unsigned length = expression.length();
	string stringForNumber;
	double doubleNumber;
	unsigned i = 0; 
	while (i < length) {
		if (expression[i] == ' ') i++; // пропускаем пробелы
		if (expression[i] == '+' || expression[i] == '*' || expression[i] == '/') {
			Term operation(expression[i]);
			terms.push_back(operation);
			i++;
		}
		else if (expression[i] == '-') { 
			Term next(expression[i + 1]); // понадобиться в будущем
			if (expression[i + 1] == '-') { // решение ситуации, когда много минусов подряд
				int iterator = i; // чтобы не потерять нужную индексацию, создаем новый итератор
				int count = 0;
				while (expression[iterator] == '-') {
					count++;
				}
				if (!(count % 2)) { // если количество минусов четное, то можно заменить все на плюс
					expression[i] = '+';
				}
				// если количество минусов нечетное, то просто оставляем минус и запробеливаем остальные
				for (int k = i; k < iterator; k++) { // заменяем все ненужные минусы на пробелы, они все равно будут пропущены
					expression[k] = ' ';
				}
			}
			else if (next.getType() == true) { // если после минуса идет число 
				Term operation('-');
				terms.push_back(operation);
			}
		}
		else if (expression[i] >= '0' && expression[i] <= '9' || (expression[i] == '.')) {
			int pointCounter = 0;
			while (expression[i] >= '0' && expression[i] <= '9' || (expression[i] == '.')) {
				stringForNumber += expression[i];
				i++;
				if (expression[i] == '.') {
					pointCounter++;
				}
				if (pointCounter > 1) {
					throw (string)"You have more than one point in the number";
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

void Arithmetic::termToPostfix() {
	unsigned size = terms.size();
	vector <Term> postfix;
	Stack <Term> operations;
	for (unsigned i = 0; i < size; i++) {
		if (terms[i].getType() == true) { // если нам встретилось число
			postfix.push_back(terms[i]); // помещаем число в выходную строку в виде Term
		}
		else if (terms[i].getType() == false) { // если встретилась операция
		compare:
			if (operations.isEmpty() || terms[i].priority() > operations.front().priority()) {
				operations.push(terms[i]); //  помещаем операцию в стэк в виде Term
			}
			else if (terms[i].priority() <= operations.front().priority()) {
				while (terms[i].priority() <= operations.front().priority()) {
					postfix.push_back(operations.pop());
				}
				goto compare;
			}
			if (terms[i].getOperation() == '(') {
				operations.push(terms[i]);
			}
			if (terms[i].getOperation() == ')') {
				while (operations.isEmpty() && operations.front().getOperation() != '(') {
					postfix.push_back(operations.pop());
				}
			}
			
			
		}
	}
	while (!operations.isEmpty()) {
		postfix.push_back(operations.pop());
	}
	terms = postfix;
}

double Arithmetic::calculate() {
	Stack <Term> stack;
	Term termOperand1, termOperand2, stringRes;
	double operand1, operand2, res;

	for (unsigned i = 0; i < terms.size(); i++) {
		if (terms[i].getType() == true) {
			stack.push(terms[i].getValue());
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

			if (terms[i].getOperation() == '/')
				res = operand1 / operand2;

			stack.push(res);
		}
	}
	Term result = stack.pop();
	return result.getValue();
}

bool checkBrackets(const string &s) {
	bool flag = true;
	int count = 0, stringSize = s.length();
	for (int i = 0; i < stringSize; i++) {
		if (s[i] == '(') {
			count++;
			flag = false;
		}
		if (s[i] == ')') {
			count--;
			flag = true;
		}
	}
	return (flag == true && count == 0);
}

bool checkSymbols(const string &s) {
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

bool isCorrect(const string &s) {
	if (!checkBrackets(s)) {
		throw (string)"Bracket in your expression are wrong";
	}
	else if (!checkSymbols(s)) {
		throw (string)"You should use only allowed symbols: 0123456789.()+-/* ";
	}
	else return true;
}

int Term::priority() {
	if ((operation == '+') || (operation == '-')) { return 1; }
	else if ((operation == '*') || (operation == '/')) { return 2; }
	else if ((operation == '(') || (operation == ')')) { return 0; }
	else throw (string)"Priorty problem";
}