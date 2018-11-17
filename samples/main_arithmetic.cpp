#include <iomanip>
#include <iostream>
#include "arithmetic.h"
using namespace std;

int main()
{
	cout << "+----------------------------------------------------------------+" << endl;
	cout << "|              Instructions for using the program:               |" << endl;
	cout << "+----------------------------------------------------------------+" << endl;
	cout << "| 1) Real numbers must be separated by a point.                  |" << endl;
	cout << "| 2) You can use such mathematical operations as +, -, *, /.     |" << endl;
	cout << "| 3) You can write as many spaces as you like, they are ignored. |" << endl;
	cout << "| 4) You can use 26 types of parameters as a, b, ... , z.        |" << endl;
	cout << "+----------------------------------------------------------------+" << endl;

	bool key1 = false;
	do
	{
		cout << endl << "Enter a math expression: ";
		string str;
		getline(cin, str);
		double ans;
		try
		{
			if (str == "")
			{
				getline(cin, str);
			}
			ans = Calculate(str);
			cout << "Answer: ";
			cout << fixed << setprecision(10) << ans << endl;
			key1 = true;
		}
		catch (pair<int, int> err)
		{
			cout << endl << Error_output(err) << err.second + 1 << endl;
			cout << "Please, re-enter the math expression." << endl;
		}
		catch (string str)
		{
			cout << str << endl;
			cout << "Please, re-enter the math expression." << endl;
		}
	} 
	while (!key1);
	return 0;
}
