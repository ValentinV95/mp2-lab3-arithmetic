// реализация пользовательского приложения
#include "arithmetic.h"

int main()
{
	Solver a;
	string s;
	s = "-(-(1+2))";
	try
	{
		a.convert_string_to_lexeme(s);
		a.convert_to_RPN();
		cout << endl << a.solve();
	}
	catch (string err)
	{

	}
}
