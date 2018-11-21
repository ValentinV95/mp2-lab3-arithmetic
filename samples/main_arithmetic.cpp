// реализация пользовательского приложения
#include <iostream>
#include <string>
#include "arithmetic.h"

using namespace std;

int main()
{
	string expression;
	double res;
	cout << "Enter Infix(without " "): ";
	cin >> expression;
	TArithmetic arithmetic(expression);
	cout << expression << endl;
	cout << "Infix: " << arithmetic.GetInfix() << endl;
	arithmetic.ToArithmetic();
	cout << "Arithmetic: " << arithmetic.GetArithmetic() << endl;
	res = arithmetic.Calculate();
	cout << res << endl;

	return 0;
}