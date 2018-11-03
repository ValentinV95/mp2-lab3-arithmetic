#include "arithmetic.h"
int main()
{
	string s;
	int t = 0;
	bool check_er = true;
	priority_creation();
	cout.precision(5);
	do {
		vector <Lexem> str;
		do {
			cout << "Enter your data" << endl;
			cin >> s;
			from_string_to_vector(s, str, check_er);
			if (!check_er)
			{
				cout << "Please, re-enter data" << endl;
				str.clear();
			}
		} while (!check_er);
		cout << calc(str) << endl;
	} while (!t);
	return 0;
}
