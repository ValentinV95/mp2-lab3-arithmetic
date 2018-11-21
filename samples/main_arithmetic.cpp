// реализация пользовательского приложения
#include <arithmetic.h>
#include <iostream>
#include <string>
using namespace std;

int main()
{
	double value;
	int i;
	char end = '=';
	string af;
	cout << "Hello!Welcome to Calculator!" << endl;
 cout << "Some rules for entering expression:" << endl;
	cout << "1. Expression may begin wiht a minus (example: -7+8)" << endl;
	cout << "2.Graps are allowed in the expression" << endl;
	cout << "3.Real nunmbers are entered through a dot (example 1.2, not 1,2)" << endl;
l:	cout << "Enter expression:" << endl;
	cout << endl;

	cin.sync();
	getline(cin,af);

	char *func = new char[af.length()];
	strcpy( func, af.c_str() );
	cout<< endl;
	Computer a ;
	a.Check(func,end);
	a.Parse(func,end);
	value = a.Compute();
	cout << func<< "=" << value<< endl;

	cout << "Want to repeat?"<< endl;
	cout << "1 - Yes, 2 - No"<<endl;
	cin >> i;
	if (i == 1)
		goto l;
	else if (i == 2)
		cout << "It is sad. Bye!";
	else cout << "I didn't understand you. Bye!";
		return 0;
}
