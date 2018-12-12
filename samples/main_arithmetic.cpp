// реализация пользовательского приложения

#include <iostream>
#include <string>
#include "arithmetic.h"
#include "stack.h"
using namespace std;
int main()
{
	int a = 0;
	setlocale(LC_CTYPE, "Russian");
	string expression;
m:cout << "Введите арифметическое выражение(без пробелов)" << endl;
	cout << "Для выделения дробной части используйте '.' Например: 5.2" << endl;
	cout << "Разрешается использование переменных, название произвольное и не ограничено в длине. Пример: res+sum" << endl;
	cin >> expression;
	TPostfix postfix(expression);
n:if (!postfix.IsCorrect())
{
	cout << "Выражение не корректно, повторите." << endl;
	goto m;
}
  postfix.ToPostfix();
k:postfix.ReadArguments();
  cout << "Результат вычисления: " << postfix.Calculate() << endl;
  cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
  cout << "Выберите дальнейшнее действие:" << endl;
  cout << "1. Ввести другое арифметическое выражение" << endl;
  cout << "2. Ввести другие значения переменных(если они присутствуют)" << endl;
  cout << "3. Выйти из программы" << endl;
  cin >> a;
  switch (a)
  {
  case 1:
  {
	  cin >> expression;
	  postfix.ChangeInfix(expression);
	  goto n;
	  break;
  }
  case 2:
  {
	  goto k;
	  break;
  }
  case 3: break;
  }
  return 0;
}