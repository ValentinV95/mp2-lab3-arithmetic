// реализация пользовательского приложения

#include<iostream>
using namespace std;
#include <string> 
#include"arithmetic.h"






int main()
{
	string input;
	while (true)
	{
		cout << " enter expression (or exit): ";
		cin >> input;
		
		if (input == "exit")
			break;
		arithmetic W(input);
		string output;
		output =W.Process();
		if (output == "")
			cout<< " incorrect expression"<< endl;
		else {
			cout << output << endl;
			cout << W.calculat() << endl;
		}
		
	}
	
	return 0;
}

