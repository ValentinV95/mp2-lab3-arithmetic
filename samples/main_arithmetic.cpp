#include "arithmetic.h"

int main()
{
	Solver a;
	int k;
	string s;
	bool exit = false;
	cout << "Hello." << endl;
	again:
	cout << "Enter the expression to calculate: ";
	getline(cin,s);
	while (!exit)
	{
		try
		{
			a.convert_string_to_lexeme(s);
			a.convert_to_RPN();
			cout << "Expression result: " << a.solve() << endl;
			cout << "1.Enter new expression to calculate" << endl << "2.Exit" << endl;
			cin >> k;
			if (k == 1)
			{				
				goto again;
			}
			else
			{
				exit = true;
			}
		}
		catch (string err)
		{
			cout << err << endl;
			cout << "Please, type the expression in the right way" << endl;
			goto again;
		}
	}
}
