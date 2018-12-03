// реализация пользовательского приложения

#include"arithmetic.h"
//#include "locale.h"




int main()
{
	double ans=0.0;
	TFormula Primer;

	setlocale(LC_ALL, "Russian");

	cout << "Программа для вычисления арифметических выражений. " << endl;
	cout << "Допустимо использование унарного минуса и бинарных оперций : +-*/ " << endl; 
	cout << "Введите арифметическое выражение" << endl;
	cout << "enter an arithmetic expression" << endl;

	//первый ввод строки
	Primer.Write();
	
	//пользователь вводит строчку до тех пор, пока она не будет корректной
	while (!Primer.Checker())
	{
		cout << "Данное выражение некорректно и не может быть вычислено!" << endl;
		Primer.Write();
	}
	cout << "Введенное выражение корректно." << endl;

	ans=Primer.Calculator();
	cout <<endl<<"Данное арифметическое выражение равно "<<ans << endl;

	system ("pause");
	return 0;
}
