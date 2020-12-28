// реализация пользовательского приложения

#include <iostream>
#include "stack.h"
#include "arithmetic.h"
#include <cstdlib>

using namespace std;

int main()
{
	string exp;
	Arithmetic calc;
	cout << "Vvedite vyrazenie: " << endl;
	cin >> exp;
	calc.SetFormula(exp);
	try
	{
		cout << "Ishodnoe vyrazenie: " << calc.GetInfix() << endl;
		calc.ToPostfix();
		cout << "Rezult: " << calc.CalcPostfix() << endl;
	}
	catch (const char* n) { std::cout << n << std::endl; }

	system("pause");
	return 0;
}