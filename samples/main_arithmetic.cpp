// реализация пользовательского приложения
#include <iostream>
#include <string>
#include "arithmetic.h"
#define MAXSIZE 100
using namespace std;

int main()
{
	string expression;
	double res;
	int bracket[MAXSIZE];
	int Size = 0;
	cout << "Enter expression: ";
	cin >> expression;
	cout << expression << endl;
	TPostfix postfix(expression);
	int counter = postfix.FormulaChecker(bracket, Size);
	if (!counter)
	{
		cout << "Expression: " << postfix.GetInfix() << endl;
		cout << "Postfix form: " << postfix.ToPostfix() << endl;
		cout << postfix.Calculate(postfix.ToPostfix()) << endl;
	}
	else
		cout << "Brackets error!" << endl;
}
