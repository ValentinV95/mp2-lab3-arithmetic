// реализация пользовательского приложения
#include <arithmetic.h>

using namespace std;

int main()
{

	try {
		string s = "1+2+3";
		isCorrect(s);
		Arithmetic res;
		res.stringToTerm(s);
		res.print();
		cout << endl;
		res.termToPostfix();
		res.print();
		cout << endl;
		res.calculate();
		res.print();
		cout << endl;
	}
	catch (string smth) {
		cout << smth << endl;
	}
	return 0;
}
