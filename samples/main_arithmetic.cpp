// реализация пользовательского приложения

#include"arithmetic.h"

int main()
{
	double ans = 0.0;
	bool k =false;

	cout << "The program for calculating arithmetic expressions." << endl;
	cout << "It is acceptable to use unary minus and binary operations: +-*/ " << endl;
	cout << "Enter an arithmetic expression" << endl;
	//первый ввод строки
	//Primer.Write();

	//пользователь вводит строчку до тех пор, пока она не будет корректной
	while (!k)
	{
		TFormula Primer;
		Primer.Write();
		k = Primer.Checker();
		if(!k)
			cout << "This expression is incorrect and cannot be evaluated!" << endl;
		else ans=Primer.Calculator();
	}
	cout << "The expression entered is correct." << endl;
	cout << endl << "This arithmetic expression is equal to " << ans << endl;
	system("pause");
	return 0;
}