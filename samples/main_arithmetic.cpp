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
	cout << endl << "1.New expression" << endl << "2.Exit" << endl;
	cin >> p;
	if (p == 1) {
		cout << endl << "Enter your expression:" << endl;
		cin >> stroka;
		cout << endl;
		while (!f) {
				try {
					bool a;
					a = errors(stroka);
					if (a)
					{
						Lexem *c = PolishRecord(stroka, k);
						double res = result(c, k);
						cout << endl << "res=" << res << endl;
					}
						goto again;
				}
				catch (int b) {
					cout << "Can not be divided by zero" << endl;
					goto again;
				}
			}
		}
	}
