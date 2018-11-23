// реализация пользовательского приложения
#include <iostream>
#include <arithmetic.h>

int main()
{
	string s = "12.34+4.56+(7+8*(9.+5))";
	vector <string> vect;
	vect = stringToVector(s);

	for (unsigned i = 0; i < vect.size(); i++) {
		std::cout << vect[i] << " ";
	}

	return 0;
}
