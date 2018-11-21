// реализация пользовательского приложения

#include<string>
#include "arithmetic.h"
#include "stack.h"
using namespace std;


void main()
{
	int l;
	bool res;
	do {
		cout << '\n' << "Choose one of the items:" << '\n';
		char*d[3] = { "1. Enter the expression ","2. Exit" };
		for (int i = 0; i < 2; i++)
			cout << d[i] << '\n';
		cout << '\n' << "Input a menu number:";
		cin >> l;
		if (l == 2) break;
		int k = 0;
		string s;
		cin >> s;
		bool fl;
		fl = mistake(s);
		if (fl) {
			Lexeme *c = Polish(s, k);
			double res;
			try {
				res = result(c, k);
				cout << '\n' << res;
			}
			catch (int a) {
				/*if (a == 1)*/
				cout << '\n' << "DIV 0";
			}
		}


	} while (l < 2);
}