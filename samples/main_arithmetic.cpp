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
			getline(cin, s);
			if (s == "")
			{
				getline(cin, s);
			}
			
			bool fl;
			for (int i = s.length() - 1; i >= 0; --i)
			{
				if (s[i] == ' ')
					s.erase(i, 1);
			}
			
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
	