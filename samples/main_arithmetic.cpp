// реализация пользовательского приложения
#include "arithmetic.h"

int main()
{
	Solver a;
	int k=0;
	string s;
	bool exit = false;
again:
	cout << "1.Enter new expression to calculate" << endl << "2.Exit" << endl;
	cin >> k;
	if (k == 1)
	{
		cout << "Enter the expression to calculate: ";
		cin >> s;
		while (!exit)
		{
			try
			{
				a.convert_string_to_lexeme(s);
				a.convert_to_RPN();
				cout << "Expression result: " << a.solve() << endl;
				goto again;
			}
			catch (string err)
			{
				cout << err << endl;
				cout << "Please, type the expression in the right way" << endl;
				goto again;
			}
		}
	}
	else
	{
		exit = true;
	}
}
