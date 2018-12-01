// реализация пользовательского приложения

#include "stack.h"
#include "arithmetic.h"
#include "vector"
#include "iostream"
using namespace std;

int main()
{
	string s;
	bool cor, rep, start;
	int stop;
	vector<Lexeme> v;

	do
	{
		start = true;
		cor = false;
		cout << "Enter arithmetic expression:" << endl;

		do 
		{
			cin >> s;

			try
			{
				v = Convert_to_lexeme_array(s);
				Checking_correctness(v);
				cor = true;
			}
			catch (Error a)
			{
				a.Print();
			}

			if (!cor)
			{
				cout << "Repeat input" << endl << endl;
			}

		} while (!cor);

		cor = false;
		v = Convert_to_postfix_notation(v);
		Set_values(v);

		cout << "Result: " << Expression_result(v) << endl;
		cout << "Do you want to finish the program?" << endl;

		do
		{
			cout << "Enter 1 to continue or 0 to finish work" << endl;
			cin >> stop;
			rep = true;

			switch (stop)
			{
			case 0:
				rep = false;
				start = false;
				break;
			case 1:
				rep = false;
				break;
			default:
				cout << "Incorrect expression. Repeat input " << endl;
				break;
			}

		} while (rep);

	} while (start);

  return 0;

}
