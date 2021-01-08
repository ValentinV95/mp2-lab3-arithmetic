// реализация пользовательского приложения

#include <iostream>
#include <string>
#include "arithmetic.h"
#include "math.h"

using namespace std;

int main()
{
  string expression;
   double res;
  cout << "write arithmetic expression: ";
  cin >> expression;
  cout << expression << endl;
  TPostfix postfix(expression);
  cout << "You wrote: " << postfix.GetInfix() << endl;
  postfix.ToPostfix();
  cout << "Postfix: "<<postfix.GetPostfix() << endl;
  res = postfix.Calculate();
  cout << res << endl;
  return 0;
}
