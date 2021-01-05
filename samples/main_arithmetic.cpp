// реализация пользовательского приложения

#include <string>
#include "arithmetic.h"

using namespace std;

int main()
{
	int k = 0;
	bool f = false;
	string stroka;
	cout << "Enter a composed expression" << endl;
	cin >> stroka;
	bool a;
	a = errors(stroka);
	if (a)
	{
		Lexem* c = PolishRecord(stroka, k);
		double res = result(c, k);
		cout << "Result of your operation =" << res << endl;
	}
	else
	{
		cout << "Error detected"
	}
}