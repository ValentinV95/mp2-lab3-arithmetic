// реализация пользовательского приложения
#include "arithmetic.h"
#include <iostream>

int main()
{
	std::string s;
	std::cout << "Enter an expression" << std::endl;
	std::cin >> s;
	std::cout << translationToRPE(s) << std::endl;
}
