#include "arithmetic.h"
int main()
{
	string s;
	int t = 0;
	bool check_er = true;
	priority_creation();
	cout.precision(5);
	do {
      try
      {
		  vector <Lexem> str;
		  do {
			  cout << "Enter your data" << endl;
			  cin >> s;
			  from_string_to_vector(s, str);
			  if (!check_er)
			  {
				  cout << "Please, re-enter data" << endl;
				  str.clear();
			  }
		  } while (!check_er);
		  cout << calc(str) << endl;
      }
      catch(int er)
      {
        cout << error_message(er) << endl;
      }
      catch(double er)
      {
        cout << error_message(11) << er << "/0" << endl;
      }
      catch(pair<int, int> er)
      {
        cout << error_message(er.first) << er.second  << ")" << endl;
      }
      catch(pair<int, double> er)
      {
        cout << error_message(er.first) << er.second << ")" << endl;
      }
      catch(pair<int, string> er)
      {
        cout << error_message(er.first) << er.second  << endl;
      }
	} while (!t);
	return 0;
}
