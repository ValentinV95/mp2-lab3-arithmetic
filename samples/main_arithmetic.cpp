#include <iostream>
#include <string>
#include "arithmetic.h"
using namespace std;

int main()
{
	cout << " Calculator   " << endl;
	cout << "In-Rules:                        " << endl;
	cout << " 1.Space not allowed                     " << endl;
	cout << " 2.Unary minus is written as (-5) " << endl;
	cout << " 3.Operations +, -, *, /                 " << endl;
	cout << " 4.Permitted up to 5 variables  " << endl;
	cout << "   a, b, c, d, e                       " << endl;
	
	cout << " Enter expression                     " << endl;
	string s;
	cin >> s;

	if (isvar(s))
	{
		cout << " You entered an expression with variables      " << endl;
		while (true)
		{
			cout << " Variable initialization              " << endl;
			string str = initvar(s);
			string str_in = error_checking(str);
			if (brackets_error(str_in) || str_in == "0")
			{
				cout << " Input errors, counting not possible      " << endl;
				break;
			}
			else
			{
				double result = calculate(convertPpn(str_in));
				cout << "= " << result << endl;
			}
			cout << " We continue to work with the expression ? 0-y, 1-n   " << endl;
			int flag;
			cin >> flag;
			if (flag == 1)
			{
				break;
			}
		}
	}
	else
	{
		string str = error_checking(s);
		if (brackets_error(s) || str == "0")
		{
			cout << " Input errors, counting not possible " << endl;
		}
		else
		{
			double result = calculate(convertPpn(str));
			cout << "= " << result << endl;
		}
	}
    return 0;
}
