// реализация функций и классов для вычисления арифметических выражений
#include "arithmetic.h"
#include "stack.h"
using namespace std;

bool IsOperation(char elem);
bool IsOperationForCorrect(char elem);
int Priority(char elem);
double Result(double op1, double op2, char operat);
bool IsNumber(char elem);

TPostfix::TPostfix(string _infix) : infix(_infix), postfix(""), value(nullptr) {}
string TPostfix::GetInfix()
{
	return infix;
}
string TPostfix::GetPostfix()
{
	return postfix;
}
void TPostfix::ChangeInfix(string _infix)
{
	infix = _infix;
	postfix.clear();
}
bool TPostfix::IsCorrect() 
{
	int flag = 0;
	stackOperation.Clear();
	if (IsOperationForCorrect(infix[0]) || IsOperationForCorrect(infix[infix.size() - 1]))
		return false;
	for (int i = 1; i < infix.size() - 1; i++) 
		if (IsOperationForCorrect(infix[i]) && IsOperationForCorrect(infix[i + 1]))
			return false;
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == '(')
			stackOperation.Push(1);
		if (infix[i] == ')')
		{
			if (stackOperation.IsEmpty())
				flag = 1;
			stackOperation.Erase();
		}
	}
	if (flag)
		return false;
	return (stackOperation.IsEmpty()) ? true : false;
}
void TPostfix::ToPostfix() 
{
	stackOperation.Clear();
	int a = 0;
	for (int i = 0; i < infix.size(); i++)
	{
		if (!IsOperation(infix[i]))
		{
			postfix += infix[i];
			if (i == infix.size() - 1 || IsOperation(infix[i + 1]))
				postfix += ' ';
		}
		else
		{
			if (infix[i] != ')')
			{
				if (Priority(infix[i]) == 0 || stackOperation.IsEmpty() || Priority(infix[i]) > Priority(stackOperation.PopWithoutDelete()))
					stackOperation.Push(infix[i]);
				else
				{
					a = stackOperation.Length();
					for (int j = 0; j < a; j++)
					{
						if (Priority(stackOperation.PopWithoutDelete()) >= Priority(infix[i]))
						{
							postfix += stackOperation.Pop();
							postfix += ' ';
						}
						else
							break;
					}
					stackOperation.Push(infix[i]);
				}
			}
			else
			{
				a = stackOperation.Length();
				for (int j = 0; j < a; j++)
				{
					if (stackOperation.PopWithoutDelete() != '(')
					{
						postfix += stackOperation.Pop();
						postfix += ' ';
					}
					else
					{
						stackOperation.Erase();
						break;
					}
				}
			}
		}
	}
	a = stackOperation.Length();
	for (int j = 0; j < a; j++)
	{
		postfix += stackOperation.Pop();
		if (j != a - 1)
			postfix += ' ';
	}
}
void TPostfix::ReadArguments() 
{
	stackArguments.Clear();
	stackValue.Clear();
	string ss;
	for (int i = infix.size() - 1; i >= 0; i--)
		if (!IsOperation(infix[i]) && !IsNumber(infix[i]) && infix[i] != '.')
		{
			ss += infix[i];
			if (i != 0 && !IsOperation(infix[i - 1]) && !IsNumber(infix[i - 1]))
				continue;
			reverse(ss.begin(), ss.end());
			stackArguments.Push(ss);
			ss.clear();
		}
	int res = stackArguments.Length();
	value = new double[res];
	if (res)
		cout << "Введите значения переменных." << endl;
	for (int i = 0; i < res; i++)
	{
		cout << stackArguments.Pop() << "=";
		cin >> value[i];
	}
	for (int i = res - 1; i >= 0; i--)
		stackValue.Push(value[i]);
}
double TPostfix::Calculate() 
{
	stackValuePostfix.Clear();
	double tmp = 0;
	string ss;
	for (int i = 0; i < postfix.size(); i++)
	{
		if (postfix[i] != ' ')
		{
			if (!IsOperation(postfix[i]) && !IsNumber(postfix[i]) && postfix[i] != '.')
			{
				if (i != postfix.size() - 1 && postfix[i + 1] != ' ')
					continue;
				stackValuePostfix.Push(stackValue.Pop());
			}
			else if (IsNumber(postfix[i]) || postfix[i] == '.')
			{
				ss += postfix[i];
				if (i != postfix.size() - 1 && IsNumber(postfix[i + 1]))
					continue;
				if (postfix[i + 1] == '.')
					continue;
				tmp = stod(ss);
				stackValuePostfix.Push(tmp);
				ss.clear();
			}
			else
			{
				tmp = Result(stackValuePostfix.Pop(), stackValuePostfix.Pop(), postfix[i]);
				stackValuePostfix.Push(tmp);
			}
		}
		else continue;
	}
	return stackValuePostfix.Pop();
}

bool IsOperation(char elem)
{
	return (elem == '(' || elem == ')' || elem == '+' || elem == '-' || elem == '*' || elem == '/') ? true : false;
}

bool IsOperationForCorrect(char elem)
{
	return (elem == '+' || elem == '-' || elem == '*' || elem == '/') ? true : false;
}

int Priority(char elem)
{
	if (!IsOperation(elem))
		throw "data is not correct";
	if (elem == '(')
		return 0;
	else if (elem == ')')
		return 1;
	else if (elem == '+' || elem == '-')
		return 2;
	return 3;
}

double Result(double op1, double op2, char operat)
{
	if (operat == '+')
		return op1 + op2;
	else if (operat == '-')
		return op1 - op2;
	else if (operat == '*')
		return op1 * op2;
	else
		return op1 / op2;
}

bool IsNumber(char elem)
{
	for (char i = '0'; i <= '9'; i++)
		if (elem == i)
			return true;
	return false;
}