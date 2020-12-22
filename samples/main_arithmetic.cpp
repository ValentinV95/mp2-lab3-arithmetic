// реализация пользовательского приложения
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "stack.h"
#include "arithmetic.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
	cout << "Enter your expression, no spaces. Allowed symbols: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ., x, y, z, /, *, -, +" << endl;
	
	try
	{
		double res;
		string s;
		getline(cin, s);
		PolishNotation v(s);
		v.TranslationToPolishNotation();
		cout << "Polish notation:" << endl;
		v.PrintPolishNotation();
		res = v.PolishNotationCalculate();
		cout << endl << "Result:" << endl << res << endl;
	}
	catch (const char *ex)
	{
		cout << endl << ex << endl;
	}
	catch (const int ex)
	{
		cout << endl << "ERROR! THE PARENTHESIS ON POSITION " << ex << " HAS NO MATCHING PARENTHESIS!";
	}
}
