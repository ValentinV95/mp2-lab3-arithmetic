// реализация пользовательского приложения
#include "arithmetic.h"


void main()
{
	vector<Lexem> Primer, Pol;
	string s="2+((5-2)-10)";
	Primer=Parsing(s);
	cout << Primer<<endl;
	Pol = Calc(Primer);
	cout << Pol;
	system("pause");
}
