// реализация пользовательского приложения
#include<string>
#include "arithmetic.h"
void main()
{
	int k = 0 ;
	int p;
	bool f = false;
	string stroka;
again:
	cout << "1.New expression" << endl << "2.Exit" << endl;
	cin >> p;
	if (p == 1) {
		cout << endl << "Enter your expression:" << endl;
		cin >> stroka;
		cout << endl;
		while (!f) {
			bool a;
			a = errors(stroka);
			if (a) {
				Lexem *c = PolishRecord(stroka, k);
				try {
					double res = result(c, k);
					cout << "res=" << res << endl;
					goto again;
				}
				catch (int b) {
					cout << "Can not be divided by zero" << endl;
					goto again;
				}
			}
		}
	}
}
