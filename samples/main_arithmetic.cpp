#include "arithmetic.h"
int main()
{
	string s;
	int t = 0;
	bool check = true;
	priority_creation();
	cout.precision(10);
	cout << "Arithmetic_expressions_interpreter_3.2" << endl;
	cout << endl;
	cout << "Expression may contain:" << endl;
	cout << "Double numbers separated by point: 3.14" << endl;
	cout << "Math operations: + - * /" << endl;
	cout << "Up to 26 different parameters: from a to z" << endl;
	cout << "Math functions: ln() exp() sin() cos() sqrt()" << endl;
	cout << endl;
	do {
		vector <Lexem> str;
		do { 
			try{
			    cout << "Enter your data" << endl;
			    cin >> s;
			    from_string_to_vector(s, str);
			}
			catch(int er)
			{
				cout << error_message(er) << endl;
				check = false;
			}
			catch(pair<int, int> er)
			{
				 cout << error_message(er.first) << er.second  << ")" << endl;
				 check = false;
			}
			catch(pair<int, string> er)
			{
				cout << error_message(er.first) << er.second  << endl;
				check = false;
			}
			if(!check)
			{
				cout << "Please, re-enter data" << endl;
				str.clear();
			}
		} while (!check);
		do{
			try{
				if(check_parameters())
				{
          			vector<double> param;
				  	param = enter_parameters();
          			set_parameters(str,param);
					cout << endl;
				}
				cout << "Answer = " << calc(str) << endl;
				cout << endl;
			}
			catch(double er)
			{
				cout << error_message(11) << er << "/0" << endl;
			}
			catch(pair<int, double> er)
			{
				cout << error_message(er.first) << er.second << ")" << endl;
			}
			cout << "New expression - 1    ";
			if(check_parameters())
			{
				cout << "New parameters - 2    ";
			}
			cout << "Exit - 0" << endl;
			cin >> t;
			cout << endl;
		} while(t == 2 && check_parameters());
    clear_parameters();
	} while (t);
	return 0;
}
