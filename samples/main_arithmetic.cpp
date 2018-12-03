// реализация пользовательского приложения

#include"arithmetic.h"

int main()
{
	double ans = 0.0;
	TFormula Primer;
	setlocale(LC_ALL, "Russian");
	cout << "The program for calculating arithmetic expressions." << endl;
	cout << "It is acceptable to use unary minus and binary operations: +-*/ " << endl;
	cout << "Enter an arithmetic expression" << endl;
	//первый ввод строки
	Primer.Write();

	//пользователь вводит строчку до тех пор, пока она не будет корректной
	while (!Primer.Checker())
	{
		cout << "This expression is incorrect and cannot be evaluated!" << endl;
		Primer.Write();
	}
	cout << "The expression entered is correct." << endl;
	ans = Primer.Calculator();
	cout << endl << "This arithmetic expression is equal to " << ans << endl;
	system("pause");
	return 0;
}