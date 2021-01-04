// реализация пользовательского приложения
#include "arithmetic.h"
 using namespace std;

int main()
{
setlocale(LC_ALL, "Russian");
string s;
cout << "введите выражение" << endl;
cin >> s;
cout << work(s) <<endl;
return 0;
}
