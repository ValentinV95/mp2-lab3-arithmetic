// реализация пользовательского приложения
#include "arithmetic.h"


void main()
{
	vector<Lexem> Primer, Pol;
	double Rezz, value;
	std::string s;

	int react2, react1;
	cout << "Welcome to RPN! Please type your execushion" << endl;
	std::getline(std::cin, s);
	cout << "Tap 1 for typing your own string\nTap any key for running test block " << endl;
	cin >> react1;
	if (react1 == 1)
	{
		cout << "Do you use values? Press 1 if true" << endl;
		cin >> react2;
		while (!Checking_Block(s,react2))
		{
			cout << "Wrong syntaxis, check your string" << endl;
			getline(cin, s);
		} 
		

			Primer = Parsing(s);
			if (react2 == 1)
			{
				cout << "Please, put your val" << endl;
				if (value)
				Primer = PutVal(value, Primer);
			}
			cout << "Your string:   " << Primer << endl;
			Pol = Polish(Primer);
			cout <<"Your lexeme massive\n"<< Pol ;
			Rezz = Calc(Pol);
			cout << "Your rezult"<< Rezz;
		
		
	}
	else 
	{
		string test1 = "3))+", test2 = "2+3+4+5+", test3 = "a+b-(2--4)", test4 = "2+(3-(5+7)-1)-2", test5 = "-2+d+(d-5)";

		cout << "test1	" << test1 << endl;
		cout << "test2	" << test2 << endl;
		cout << "test3	" << test3 << endl;
		cout << "test4	" << test4 << endl;
		cout << "test5	" << test5 << endl;


		if (!Checking_Block(test1, 0))
			cout << "test 1 end"<<endl;
		if (!Checking_Block(test2, 0))
			cout << "test 2 end" << endl;
		if (!Checking_Block(test3, 1))
			cout << "test 3 end" << endl;
		if (Checking_Block(test4, 0))
		{
			Primer = Parsing(test4);
			Pol = Polish(Primer);
			cout << "test 4 answer:" << Pol << endl;

			Rezz = Calc(Pol);
			cout << "test 4 answer:" << Rezz << endl;
		}
		if (Checking_Block(test5, 1))
		{
			Primer = Parsing(test5);
			Primer = PutVal(4,Primer);
			cout << "test value 4" << endl;
			Pol = Polish(Primer);
			Rezz = Calc(Pol);
			cout << "test 4 answer:     " << Rezz << endl;
		}
	}
	
	system("pause");
}

