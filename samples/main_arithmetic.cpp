// реализация пользовательского приложения

#include <iostream>
#include <string>
#include "arithmetic.h"
#include "stack.h"
using namespace std;
int main()
{
	double res;
	string expression;
	TPostfix postfix("((1+2*3)/4+6)*8");
	setlocale(LC_ALL, "Russian");
	cout << "Enter arithmetic expression: ";
	cin >> expression;
	cout << expression << endl;
	postfix.SetInfix(expression);
	cout << "Arithmetic expression: " << postfix.GetInfix() << endl;
	postfix.ToPostfix();
	cout << "Postfix form:  " << postfix.GetPostfix() << endl;
	res = postfix.Calculate();
	cout <<"Result: " << res << endl;
	return 0;
}