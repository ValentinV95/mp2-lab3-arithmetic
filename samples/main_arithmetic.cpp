// реализация пользовательского приложения


#include "arithmetic.h"
#include <iostream>


using namespace std;


int main()
{
	
	
	string c;

	cout << "Rules for entering a mathematical samples: "<< endl;
	cout << "1)Sample must not contain spaces " << endl;
	cout << "2)Print your negative numbers or samples in brackets " << endl;
	cout << "3)The integer and fractional parts of the number are separated '.' " << endl;
	cout << "4)If the integer part of the number is 0, the point must be preceded by 0  " << endl;
	cout << "5)if the fractional part of the number is 0 and you want to write not as an integer, then after the point should be 0  " << endl;
	cout << "7)Sample must contain at least one action" << endl;
	cout << "8)For example: 12.2/(-(11.2+1))"<< endl;
	cout << "Enter your sample" << endl;
	
	cin >> c;
	char* c1;
	c1 = new char[c.length()];
	for (int i = 0;i < c.length();i++)
	{
		c1[i] = c[i];

	}
	c1[c.length()] = '\0';

	Lexeme a(c1);
	cout << a.Answer(a.RPN()) << std::endl;
  return 0;
}
