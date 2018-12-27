#include<string>
#include "arithmetic.h"
void main()
{
	int k = 0;
	int tmp;
	bool f = false;
	string stroka;
	cout << endl << "Hi! Welcome to the program. Let's choose the surgery" << endl;
again:
	cout << endl << "1.Enter expression" << endl << "2.Exit the program" << endl;
	cin >> tmp;
	if (tmp == 1)
	{
		cout << endl << "Enter a composed expression" << endl;
		cin >> stroka;
		cout << endl;
		while (!f)
		{
			try
			{
				bool a;
				a = errors(stroka);
				if (a)
				{
					Lexem *c = PolishRecord(stroka, k);
					double res = result(c, k);
					cout << endl << "Result of your operation =" << res << endl;
				}
				goto again;
			}
			catch (int b)
			{
				cout << "ERROR Can not be divided by zero" << endl;
				goto again;
			}
		}
	}
}