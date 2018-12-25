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
	/////////////expression = "1+20*3*4+(5-6)*(7*8+9)";
	//expression = "1/-5";
	//expression = "1/---5*6";
	string expr_p;
	TPostfix P(expression);
	//int counter = P.FormulaChecker(bracket, Size);
	//if (!counter)
	{
		//P.Process();
		cout << "Expression: " << P.GetInfix() << endl;
		expr_p = P.ToPostfix();
		cout << "Postfix form: " << expr_p << endl;
		cout << "Rezult: " << P.Calculate(expr_p) << endl;
	}
	/*else
	{
	cout << "Brackets error!" << endl;
	}*/
	system("pause");
	return 0;
}