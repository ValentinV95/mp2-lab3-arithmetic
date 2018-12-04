// реализация функций и классов для вычисления арифметических выражений


#include "stack.h"
#include "arithmetic.h"
#include "iostream"
using namespace std;

//Реализация методов класса Error

Error::Error()
{
}

Error::~Error()
{
}

Error::Error(string s)
{
	err = s;
}


void Error::Print()
{
	cout << "Error:" <<err << endl;
}

//Реализация методов класса Lexeme

Lexeme::Lexeme()
{
}

Lexeme::~Lexeme()
{
}

Lexeme::Lexeme(TTag t, double v)
{
	Type = t;
	Value = v;
}

Lexeme::Lexeme(TTag t, string n, double d)
{
	Type = t;
	Name = n;
	Value = d;
}

bool Lexeme::operator==(const Lexeme& x) const
{
	if (Type == x.Type && Name == x.Name && Value == x.Value)
		return(true);
	else
		return(false);
}

bool Lexeme::operator!=(const Lexeme& x) const
{
	if ((*this) == x)
		return(false);
	else
		return(true);
}

TTag Lexeme::GetType()
{
	return(Type);
}

double Lexeme::GetValue()
{
	return(Value);
}

string Lexeme::GetName()
{
	return(Name);
}

 void Lexeme::SetValue(double v)
 {
	 Value = v;
 }

 //Реализация функций для вычисления арифметических выражений

 map <string, int> Priority = { {"+",1}, {"-",1}, {"*",2}, {"/",2}, {"unar-", 3}, {"(", 0}, {")",0} };


double Expression_result( vector<Lexeme> postf )
{
	TStack<double> s;
	int i = 0;

	while (i < postf.size())
	{

		if (postf[i].GetType() != OPERATION)
			s.Push(postf[i].GetValue());
		else 
		{
			double op = s.Pop();

			if (postf[i].GetName() == "+")
				s.Push(s.Pop() + op);

			if (postf[i].GetName() == "-")
				s.Push(s.Pop() - op);

			if (postf[i].GetName() == "*")
				s.Push(s.Pop() * op);

			if (postf[i].GetName() == "/")
			{
				if (op == 0.0)
					throw Error("Division by zero");

				s.Push(s.Pop() / op);
			}

			if (postf[i].GetName() == "unar-")
				s.Push(-op);
		}

		i++;
	}

	return(s.Pop());

}

vector<Lexeme> Convert_to_postfix_notation(vector<Lexeme> parsed)
{
	TStack<Lexeme> s;
	int size = 0;


	for (int i = 0; i < parsed.size(); i++)
	{
		if (parsed[i].GetType() != BRACKET)
			size++;
	}


	vector<Lexeme> postf(size);
	int i = 0, j = 0;


	while(i < parsed.size())
	{

		if (parsed[i].GetType() == OPERATION)
		{
			if (s.IsEmpty() || Priority[parsed[i].GetName()] > Priority[s.CheckTop().GetName()])
			{
				s.Push(parsed[i]);
			}
			else
			{
				if (parsed[i].GetName() == "unar-")
				{
					s.Push(parsed[i]);
				}
				else 
				{
					while (Priority[parsed[i].GetName()] <= Priority[s.CheckTop().GetName()])
					{
						postf[j] = s.Pop();
						j++;

						if (s.IsEmpty())
							break;

					}
					s.Push(parsed[i]);
				}
			}
		}


		if (parsed[i].GetType() == BRACKET)
		{
			if (parsed[i].GetName() == "(")
			{
				s.Push(parsed[i]);
			}
			else
			{
				while (s.CheckTop().GetName() != "(")
				{
					postf[j] = s.Pop();
					j++;
				}
				s.Pop();
			}
		}
		

		if(parsed[i].GetType() == NUMBER || parsed[i].GetType() == VARIABLE)
		{
			postf[j] = parsed[i];
			j++;
		}

		i++;

	}

	while (!s.IsEmpty())
	{
		postf[j] = s.Pop();
		j++;
	}

	return(postf);
}

vector<Lexeme> Convert_to_lexeme_array(string exp)
{
	vector<Lexeme> v;
	bool error = true;

	for(int i = 0; i < exp.size(); i++)
	{
		if ( (exp[i] >= 'A' && exp[i] <= 'Z') || (exp[i] >= 'a' && exp[i] <= 'z') )
		{
			string name;

			while ((exp[i] >= 'A' && exp[i] <= 'Z') || (exp[i] >= 'a' && exp[i] <= 'z'))
			{
				name += exp[i];
				i++;
			}

			i--;
			Lexeme temp(VARIABLE, name);
			v.push_back(temp);
			error = false;
		}


		if (exp[i] >= '0' && exp[i] <= '9')
		{
			string integ, fract, res;

			while (exp[i] >= '0' && exp[i] <= '9')
			{
				integ += exp[i];
				i++;
			}

			if (exp[i] == '.')
			{
				i++;
				while (exp[i] >= '0' && exp[i] <= '9')
				{
					fract+= exp[i];
					i++;
				}
				
				i--;
				res = integ + "." + fract;
			}
			else
			{
				i--;
				res = integ;
			}
			
			Lexeme temp(NUMBER, atof(res.c_str()));
			v.push_back(temp);
			error = false;
		}


		if (exp[i] == '-')
		{
			if (!i || v.back().GetType() == OPERATION ||  v.back().GetName() == "(")
			{
				Lexeme temp(OPERATION, "unar-");
				v.push_back(temp);
				error = false;
			}
			else
			{
				Lexeme temp(OPERATION, "-" );
				v.push_back(temp);
				error = false;
			}
		}


		if (exp[i] == '+' || exp[i] == '*' || exp[i] == '/')
		{
			string str;
			str += exp[i];

			Lexeme temp(OPERATION, str);
			v.push_back(temp);
			error = false;
		}


		if (exp[i] == '(' || exp[i] == ')')
		{
			string str;
			str += exp[i];

			Lexeme temp(BRACKET, str);
			v.push_back(temp);
			error = false;
		}

		if (exp[i] == '.')
		{
			throw Error("Unresolved dot in expression");
		}

		if (error)
		{
			throw Error("Invalid symbol in expression");
		}

		error = true;
	}

	return(v);
}

bool Checking_correctness(vector<Lexeme> exp)
{
	bool res = true;
	Lexeme first = exp[0], last = exp[exp.size() - 1];
	TStack<string> s;



	for (int i = 0; i < exp.size(); i++)
	{
		if (exp[i].GetType() == BRACKET)
		{
			if (exp[i].GetName() == "(")
			{
				s.Push(exp[i].GetName());
			}
			else
			{
				if (s.IsEmpty())
				{
					throw Error("Incorrect placement of brackets");
				}
				else
				{
					s.Pop();
				}
			}
		}
	}

	if (!s.IsEmpty())
	{
		throw Error("Incorrect placement of brackets");
	}

	

	if ((first.GetType() == OPERATION && first.GetName() != "unar-") || first.GetName() == ")")
	{
		throw Error("Unresolved lexeme at first");
	}



	if (last.GetType() == OPERATION || last.GetName() == "(")
	{
		throw Error("Unresolved lexeme at last");
	}


	for (int i = 0; i < exp.size() - 1; i++)
	{
		if (exp[i].GetType() == NUMBER || exp[i].GetType() == VARIABLE)
		{
			if (exp[i + 1].GetType() == NUMBER || exp[i + 1].GetType() == VARIABLE || exp[i + 1].GetName() == "unar-" ||
				exp[i + 1].GetName() == "(")
			{
				throw Error("Unresolved lexeme after number/variable");
			}
		}

		if (exp[i].GetType() == OPERATION)
		{
			if ((exp[i + 1].GetType() == OPERATION && exp[i + 1].GetName() != "unar-") || exp[i + 1].GetName() == ")")
			{
				if (exp[i].GetName() == "unar-")
				{
					throw Error("Unresolved lexeme after unary operation.");
				}
				else
				{
					throw Error("Unresolved lexeme after binary operation.");
				}
			}
		}

		if (exp[i].GetName() == "(")
		{
			if ((exp[i + 1].GetType() == OPERATION && exp[i + 1].GetName() != "unar-") || exp[i + 1].GetName() == ")")
			{
				throw Error("Unresolved lexeme after opening bracket");
			}
		}

		if (exp[i].GetName() == ")")
		{
			if (exp[i + 1].GetType() == NUMBER || exp[i + 1].GetType() == VARIABLE || exp[i + 1].GetName() == "unar-" ||
				exp[i + 1].GetName() == "(")
			{
				throw Error("Unresolved lexeme after closing bracket");
			}
		}

	}

	return(res);
}

 void Set_values(vector<Lexeme>& exp)
{
	 /*for (int i = 0; i < exp.size(); i++)
		 if (exp[i].GetType() == VARIABLE)
		 {
			 double temp;
			 cout << "Enter variable value " << exp[i].GetName() << " = ";
			 cin >> temp;
			 exp[i].SetValue(temp);
		 }*/

	 vector<Lexeme> var;
	 bool key = true;

	 for (int i = 0; i < exp.size(); i++)
	 {
		 if (exp[i].GetType() == VARIABLE)
		 {
			 for (int j = 0; j < var.size(); j++)
			 {
				 if (exp[i].GetName() == var[j].GetName())
				 {
					 exp[i].SetValue(var[j].GetValue());
					 key = false; 
					 break;
				 }	
			 }

			 if (key)
			 {
				 double temp;
				 cout << "Enter variable value " << exp[i].GetName() << " = ";
				 cin >> temp;
				 exp[i].SetValue(temp);
				 var.push_back(exp[i]);
			 }

			 key = true;
		 }
	 }
}