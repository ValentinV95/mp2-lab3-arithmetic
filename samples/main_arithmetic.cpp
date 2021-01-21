#include <iostream>
#include "arithmetic.h"
#include <string>
using namespace std;
int main()
{
	bool res = true;
	while (res)
	{
			string tmp;
			cout << "Enter expression:";
			cin.ignore();
			getline(cin, tmp);
			cout << tmp << endl;
			Arithmetic x(tmp);
			cout << endl;
			if (x.Error())
			{
				cout << x.ToPostfix() << endl;
				cout << x.Calculator() << endl;
			}

			else
			{
				cout << "try again" << endl;
			}
	}return 0;
};
