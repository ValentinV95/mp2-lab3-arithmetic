// реализация функций и классов для вычисления арифметических выражений

#include "../include/arithmetic.h"

PolishNotation::PolishNotation(string s)
{
	formula = s;
}

void PolishNotation::CorrectionChecker(string s)
{
	int i = 0;
	int last = s.length() - 1;
	int er = 0;
	int open = 0, closed = 0; // количсетво открывающих и закрывающих скобок соответственно
	vector <int> opening; //вектор для хранения индексов лишних открывающих скобок

	while (i < s.length())
	{
		if ((s[i] != '+') && (s[i] != '-') && (s[i] != '/') && (s[i] != '*') && (s[i] != 'x') && (s[i] != 'y') && (s[i] != 'z') && (s[i] != '.') && (s[i] != '(') && (s[i] != ')') && ((s[i] < '0') || (s[i] > '9')))
		{
			throw "ERROR! INVALID SYMBOL IN EXPRESSION!";
		}


		if (s[i] == '(')
		{
			open++;
			opening.push_back(i);
		}

		if ((s[i] == ')') && (open == closed))
		{
			er = i + 1;
			throw er;
		}

		if ((s[i] == ')') && (open > closed))
		{
			closed++;
			opening.pop_back();
		}

		i++;
	}

	if (open > closed)
	{
		throw opening[0];
	}
}


double PolishNotation::BinaryCalculate(double a, double b, string s)
{
	double res;

	if (s == "+")
	{
		res = a + b;
	}

	if (s == "-")
	{
		res = a - b;
	}

	if (s == "*")
	{
		res = a * b;
	}

	if (s == "/")
	{
		res = a / b;
	}

	return res;
}

void PolishNotation::TranslationToPolishNotation()
{
	CorrectionChecker(formula);
	
	int i = 0; 
	int j = 0; 
	int k = 0;

	while (i < formula.length())
	{
		l.push_back(Lexem());

		if ((formula[i] <= '9' && formula[i] >= '0') || (formula[i] == '.'))
		{
			k = i;
			while ((formula[k] <= '9' && formula[k] >= '0') || (formula[k] == '.'))
			{
				l[j].lexm.push_back(formula[k]);

				k++;
			}

			l[j].type = "operand";
			l[j].priority = 0;

			i = k;
		}

		if ((formula[i] == '-') && (i == 0))
		{
			l[j].lexm.push_back(formula[i]);
			l[j].type = "operation";
			l[j].priority = 4;
		}

		if (formula[i] == '+')
		{
			l[j].lexm.push_back(formula[i]);
			l[j].type = "operation";
			l[j].priority = 2;
		}

		if (formula[i] == '(')
		{
			l[j].lexm.push_back(formula[i]);
			l[j].type = "operation";
			l[j].priority = 1;
		}

		if (formula[i] == ')')
		{
			l[j].lexm.push_back(formula[i]);
			l[j].type = "operation";
			l[j].priority = 0;
		}

		if ((formula[i] == '*') || (formula[i] == '/'))
		{
			l[j].lexm.push_back(formula[i]);
			l[j].type = "operation";
			l[j].priority = 3;
		}

		if ((formula[i] == '-') && (i != 0))
		{
			if ((formula[i - 1] == '(') || (formula[i - 1] == '+') || (formula[i - 1] == '-') || (formula[i - 1] == '/') || (formula[i - 1] == '*'))
			{
				l[j].lexm.push_back(formula[i]);
				l[j].type = "operation";
				l[j].priority = 4;
			}

			else
			{
				l[j].lexm.push_back(formula[i]);
				l[j].type = "operation";
				l[j].priority = 2;
			}
		}

		if ((formula[i] == 'x') || (formula[i] == 'y') || (formula[i] == 'z'))
		{
			l[j].lexm.push_back(formula[i]);
			l[j].type = "variable";
			l[j].priority = 0;
		}

		i++;
		j++;
	}

	for (int m = 0; m < l.size(); m++)
	{
		int c = 0;

		for (i = 0; i < l[m].lexm.length(); i++)
		{
			if ((l[m].lexm[i] == '.') && (i == 0))
			{
				throw "ERROR! IN SOME OPERAND DOT IS FIRST SYMBOL (MAYBE YOU MISSED OPERATION OR NUMBER)!";
			}

			if ((l[m].lexm[i] == '.') && (i == (l[m].lexm.length() - 1)))
			{
				throw "ERROR! IN SOME OPERAND DOT IS LAST SYMBOL (MAYBE YOU MISSED OPERATION OR NUMBER)!";
			}

			if (l[m].lexm[i] == '.')
			{
				c++;
			}

			if (c > 1)
			{
				throw "ERROR! THERE ARE MORE THAN 1 DOT IN SOME OPERAND!";
			}
		}
	}

	TStack <Lexem> st(l.size());
	i = 0;
	j = 0;

	while(i < l.size())
	{
		polish.push_back(Lexem());

		if ((l[i].type == "operand")||(l[i].type == "variable"))
		{
			polish[j++] = l[i];
		}

		if (l[i].lexm == "(")
		{
			st.Push(l[i]);
		}

		if (l[i].lexm == ")")
		{
			while (st.GetHeadElement().lexm != "(")
			{
				polish[j++] = st.GetHeadElement();
				st.Pop();
			}
			st.Pop();
		}

		if ((l[i].lexm == "+") || (l[i].lexm == "/") || (l[i].lexm == "*"))
		{
			if (st.IsEmpty())
			{
				st.Push(l[i]);
			}
			else
			{
				while ((!st.IsEmpty()) && (l[i].priority <= st.GetHeadElement().priority))
				{
					polish[j++] = st.GetHeadElement();
					st.Pop();
				}
				st.Push(l[i]);
			}
		}

		i++;
	}
}

void PolishNotation::PrintPolishNotation()
{
	int i = 0;

	while (i < polish.size())
	{
		cout << polish[i].lexm << "\t";
	}
}

double PolishNotation::PolishNotationCalculate()
{
	double result;
	TStack <double> st(polish.size());
	int i = 0;

	while (i < polish.size())
	{
		if (polish[i].type == "operand")
		{
			double k;
			stringstream ss(polish[i].lexm);
			ss >> k;
			st.Push(k);
		}

		if (polish[i].type == "variable")
		{
			double s;
			cout << "Enter variable value " << polish[i].lexm << endl;
			cin >> s;
			st.Push(s);
		}

		if ((polish[i].lexm == "-") && (polish[i].priority == 4))
		{
			if (st.IsEmpty())
			{
				throw "ERROR! NOT ENOUGH OPERANDS FOR SOME UNARY OPERATION!";
			}
			double a = st.Pop();
			double res = -a;
			st.Push(res);
		}

		if ((polish[i].lexm == "+") || (polish[i].lexm == "*") || (polish[i].lexm == "/"))
		{
			if (st.GetCount() < 2)
			{
				throw "ERROR! NOT ENOUGH OPERANDS FOR SOME BINARY OPERATION!";
			}
			double b = st.Pop();
			double a = st.Pop();
			double res = BinaryCalculate(a, b, polish[i].lexm);
			st.Push(res);
		}

		if ((polish[i].lexm == "-") && (polish[i].priority == 2))
		{
			if (st.GetCount() < 2)
			{
				throw "ERROR! NOT ENOUGH OPERANDS FOR SOME BINARY OPERATION!";
			}
			double b = st.Pop();
			double a = st.Pop();
			double res = BinaryCalculate(a, b, polish[i].lexm);
			st.Push(res);
		}

		i++;
	}

	if (st.GetCount() > 1)
	{
		throw "ERROR! YOU MISSED OPERATION!";
	}

	result = st.GetHeadElement();
	
	return result;
}