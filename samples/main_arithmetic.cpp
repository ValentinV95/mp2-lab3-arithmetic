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
	cout << "Введите выражение которое хотите перевести в польскую запись и вычислить. Ввод осуществляйте без пробелов. Доступные символы: цифры от 0 до 9, +, -, *, /, точка, символы для обозначения переменных: x, y, z." << endl;
	
	try
	{
		double res;
		string s;
		getline(cin, s);
		PolishNotation v(s);
		v.TranslationToPolishNotation();
		v.PrintPolishNotation();
		res = v.PolishNotationCalculate();
		cout << res << endl;
	}
	catch (const char *ex)
	{
		cout << ex << endl;
	}
	catch (const int ex)
	{
		cout << "ERROR! THE PARENTHESIS ON POSITION " << ex << " HAS NO MATCHING PARENTHESIS!";
	}
}
