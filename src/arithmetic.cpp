// реализация функций и классов для вычисления арифметических выражений
#include "arithmetic.h"

void Lexem::Parsing(string a)
{
	int i = 0, k=0;
	
	while (a[i]!='\0')
	{
		if (a[i] == ' ')
			i++;
		else if ((a[i] >= '0') && (a[i] <= '9'))
		{
			double dd = 0.0;

			PrePolish.push_back(dd);
			i++;
		}

		else if ((a[i] == '+') || (a[i] == '-') || (a[i] == '/') || (a[i] == '(') || (a[i] == ')'))
		{

			PrePolish.push_back(a[i]);
			Lexem A = PrePolish.back();
			PrePolish.pop_back();
			A.Putprior(2);

			if (a[i] == '-')
			{
				if (!(PrePolish.empty()))
				{
					Lexem B = PrePolish.back();
					if (!(B.GetType()))
						A.Unar();
					A.Putprior(0);
				}
				else {
					A.Unar();
					A.Putprior(0);
				}

			
	
				PrePolish.push_back(A);
				i++;
			}
			if ((a[i] == '*') || (a[i] == '/'))

			{
				A.Putprior(1);
				PrePolish.push_back(A);
				i++;
			}
			if (a[i] == '+')
			{
				A.Putprior(2);
			PrePolish.push_back(A);
			i++;
			}
		
		}
		else if ((a[i] >= 'a') && (a[i] <= 'z'))
		{
			PrePolish.push_back(a[i]);
			i++;
		}
	}
}



bool Skobki(string s)
{
	TStack<char> rez;
	for (int i = 0; i < (int)s.length(); i++)
	{
		if (s[i] == '(' )
		{
			rez.Push(s[i]);
		}
		else if (s[i] == ')')
		{
			if(rez.Empty() || ((s[i] == ')') ^ (rez.CheckLast() == '(')))
			{
				cout << "Wrong sintaxis" << endl;
				return false;
			}
			rez.Pop();
		}
	}

	return rez.Empty();
}

bool CheckSequence(string s)
{
	if ((s[1] == '*') || (s[1] == '/') || (s[1] == '+'))
	{
		cout << "Wrong first element" << endl;
		return false;
	}
	if ((s[s.size() - 1] == '-') || (s[s.size() - 1] == '+') || (s[s.size() - 1] == '*') || (s[s.size() - 1] == '/'))
	{
		cout << "Wrong last element" << endl;
		return false;
	}
	for (int i = 0; i < (int)s.length(); i++)
	{
		if ((s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i]=='(') && (s[i + 1] == '+' || s[i + 1] == '*' || s[i + 1] == '/' || s[i+1]==')')) {
			cout << "operation after operation" << endl;
			return false;

		}
		if ((s[i] == '/') && (s[i + 1] == '0'))
		{
			cout << "division by 0" << endl;
			return false;
		}
	}
}




bool ValisOne(string s)
{
	string qq;
	for (int i = 0; i < (int)s.length(); i++)
	{
		if ((s[i] >= 'a') && (s[i] <= 'z'))
			qq += s[i];
	}
	for (int i = 0; i < (int)qq.length(); i++)
	{
		if (qq[1] != qq[i])
		{
			cout << "Wrong value name" << endl;
			return false;
		}
	}
	return true;

}

