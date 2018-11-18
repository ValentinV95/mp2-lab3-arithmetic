// реализация пользовательского приложения
#include <iostream>
#include <string>
#include "arithmetic.h"

int main() {
	while (true)
	{
		try
		{
			std::string s;
			getline(std::cin, s);
			if (s == "")
			{
				getline(std::cin, s);
			}
			Calculate ans(s);
			std::cout << ans.calc() << std::endl;
		}
		catch (std::pair<std::string, int> error)
		{
			std::cout << error.first << " " << error.second + 1 << std::endl;
		}
	 }
}