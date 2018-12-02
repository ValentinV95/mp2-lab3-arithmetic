// реализация пользовательского приложения
#include <arithmetic.h>

using namespace std;

int main()
{
	string s;
	for (int i = 0; i < 100; i++) {
		try {
			getline(cin, s);
			isCorrect(s);
			Arithmetic res;
			res.stringToTerm(s);
			res.print();
			cout << endl;
			res.termToPostfix();
			res.print();
			cout << endl;
			double result = res.calculate();
			cout << "Result: " << result;
			cout << endl;
		}
		catch (char* smth) {
			cout << smth << endl;
		}
		cout << endl;
	}
	return 0;
}