// реализация функций и классов для вычисления арифметических выражений
#include "arithmetic.h"


map<char, int> priority;


vector<Lexem> Parsing(string a)
{
	vector<Lexem> PrePolish;

	int i = 0;
	
	while (a[i]!='\0')
	{
		if (a[i] == ' ')
			i++;
		else if ((a[i] >= '0') && (a[i] <= '9'))
		{
			double dd = 0.0;
			double ff = 0.0;
			while ((a[i] >= '0') && (a[i] <= '9'))
			{
				dd = dd * 10 + double(a[i] - '0');
				i++;
			}
			if (a[i] == '.')
			{
				++i;
				int raz = i;
				double rezerv = 1;
				while ((a[i] >= '0') && (a[i] <= '9'))
				{
					ff = ff * 10 + double(a[i] - '0');
					i++;
				}
				for (int j = 0; j < i - raz; j++)
				{
				rezerv *= 10;
				}
				ff /= rezerv;
			}
			PrePolish.push_back(dd+ff);
			
		}

		else if ((a[i] == '+') || (a[i] == '-') || (a[i] == '/') || (a[i] == '(') || (a[i] == ')') || (a[i] == '*'))
		{
			DoPriority();
			PrePolish.push_back(a[i]);
			Lexem A = PrePolish.back();
			PrePolish.pop_back();

			if (a[i] == '-')
			{
				if (!(PrePolish.empty()))
				{
					Lexem B = PrePolish.back();
					if (!B.IsNum() && (B.GetOper()!=')'))
						A.IfUnar();
					
				}
				else {
					A.IfUnar();
				}

			
	
				PrePolish.push_back(A);
				i++;
			}
			else if ((a[i] == '*') || (a[i] == '/') || (a[i] == '+') || (a[i] == '(') || (a[i] == ')'))

			{
				PrePolish.push_back(a[i]);
				i++;
			}
			
			
		
		}
		else if ((a[i] >= 'a') && (a[i] <= 'z'))
		{
			
			Lexem A(a[i]);
			A.IfVal();
			PrePolish.push_back(A);
			i++;
		}
		else i++;

	}
	return PrePolish;
}

vector<Lexem> PutVal(double a, vector<Lexem> &s)
{
	Lexem A(a);
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i].IsNum() && ((s[i].GetOper() >= 'a') && (s[i].GetOper() <= 'z')))
		{
			s[i]=A;
		}
	}
	return s;
}



vector<Lexem> Polish(vector<Lexem> s)
{
	vector<Lexem> Polish;
	TStack<char> Op;

	for (int i = 0; i < s.size(); i++)
	{
		
		if (s[i].IsNum())
		{
			Polish.push_back(s[i]);
		}
		else 
		{
			if (!s[i].Binar())
			{
				while (!(s[i].IsNum()))
				i++;
				double a = s[i].GetNum();
				a = (-1)*a;
				Polish.push_back(a);
				
			}
			else if ((s[i].Binar())&&(Op.Empty()|| s[i].GetOper()=='(' || Op.CheckLast() == '(' || (priority[Op.CheckLast()] < priority[s[i].GetOper()])))
			{
				Op.Push(s[i].GetOper());
			}
			else if ((s[i].Binar()) && (priority[Op.CheckLast()] >= priority[s[i].GetOper()]))
			{
				if ((s[i].Binar()) && s[i].GetOper() == ')')
				{
					while (Op.CheckLast() != '(')
						Polish.push_back(Op.Pop());
					Op.Pop();
				}
				
				else
				{
					while (!Op.Empty() && (priority[Op.CheckLast()] >= priority[s[i].GetOper()]))
						Polish.push_back(Op.Pop());
					Op.Push(s[i].GetOper());
				}
			}
			 
		}
		
		if (i == (s.size()-1))
		{
			while (!Op.Empty())
				if (Op.CheckLast() == '(' || Op.CheckLast() == ')')
					Op.Pop();
				else Polish.push_back(Op.Pop());
			
		}
	}
	
	return Polish;
}



double Calc(vector<Lexem> s)
{
	TStack<double> Num;
	double Rez;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i].IsNum())
			Num.Push(s[i].GetNum());
		else if(!Num.Empty())
		{
			double frst=Num.Pop();
			switch (s[i].GetOper())
			{
			case '+':
				Rez = Num.Pop()+frst;
				Num.Push(Rez);
				break;
			case '-':
				Rez = Num.Pop()-frst;
				Num.Push(Rez);

				break;
			case '*':
				Rez = Num.Pop()*frst;
				Num.Push(Rez);

				break;
			case '/':
				if (frst != 0)
				{
					Rez = Num.Pop() / frst;
					Num.Push(Rez);
				}
				else throw ("Division by null");

				break;
			
			}
		}
	}
	return Rez;

}


bool Lexem::Binar()
{
	return binary;
}
double Lexem::GetNum()
{
	return num;
}
char Lexem::GetOper()
{
	return op;
}
bool Lexem::IsNum()
{
	return notop;
}
void Lexem::IfUnar()
{
	binary = false;
}
void Lexem::IfVal()
{
	notop = true;
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
			if(rez.Empty())
			{
				cout << "Wrong sintaxis" << endl;
				return false;
			}
			else rez.Pop();
		}
	}

	return rez.Empty();
}

bool CheckSequence(string s)
{
	if ((s[0] == '*') || (s[0] == '/') || (s[0] == '+'))
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
		if ((s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i]=='(') && (s[i + 1] == '+' || s[i + 1] == '*' || s[i + 1] == '/' || s[i+1]==')')) 
		{
			cout << "operation after operation" << endl;
			return false;
		}
	}
	return true;
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

void DoPriority()
{
	priority['('] = 0;
	priority[')'] = 0;
	priority['*'] = 2;
	priority['/'] = 2;
	priority['+'] = 1;
	priority['-'] = 1;

}

 ostream& operator<<(ostream &out, vector<Lexem> &lex)
{
	for (int i = 0; i<lex.size(); i++)
	 {
		if (lex[i].IsNum())
		out << lex[i].GetNum()<< " ";
		else
		out << lex[i].GetOper()<<" ";
		
	 }
	return out;

 }
 bool Checking_Block(string s, int valhere)
 {
	 if (!Skobki(s))
		 cout << "Error parentheses" << endl;
	 if (!CheckSequence(s))
		 cout << "Wrong syntax" << endl;
	 if (valhere == 1)
	 {
		 if (!ValisOne(s))
			 cout << "Please, use one value" << endl;
		 else  return (Skobki(s) && CheckSequence(s) && ValisOne(s));
	 }
		 
	 return (Skobki(s) && CheckSequence(s));

 }