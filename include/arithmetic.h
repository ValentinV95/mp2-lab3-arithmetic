// объявление функций и классов для вычисления арифметических выражений

#ifndef _ARITHMETIC_
#define _ARITHMETIC_

#include <stack.h>
//#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

struct Lex
{
	int OpType; // 1-число,2-операция
	double Value;
	char *Op;
	int Priority;
};

ostream &operator<<(ostream &ostr, const struct Lex &f) // вывод
{
	if (f.OpType == 1)
		ostr << f.Value;
	else ostr << f.Op;
	return ostr;
}

void Error(int i, int j)
{
	cout << "You have something wrong!"<<endl;
	switch (j)
	{
	case 1:
		cout << "Symbol number error " << i <<endl;
		cout << "Opertion is expected! Opening bracket error." << endl;
		break;
	case 2:
		cout << "Symbol number error " << i <<endl;
		cout << "Operand expected! Closing bracket error." << endl;
		break;
	case 3:
		cout << "Symbol number error " << i <<endl;
		cout << "Too many closing brackets." << endl;
		break;
	case 4:
		cout << "Symbol number error " << i <<endl;
		cout << "Operand expected!Statement '+' error." << endl;
		break;
	case 5:
		cout << "Symbol number error " << i <<endl;
		cout << "Operand expected!Statement '-' error." << endl;
		break;
	case 6:
		cout << "Symbol number error " << i <<endl;
		cout << "Operand expected!Statement '*' error." << endl;
		break;
	case 7:
		cout << "Symbol number error " << i <<endl;
		cout << "Operand expected!Statement '/' error." << endl;
		break;
	case 8:
		cout << "Symbol number error " << i <<endl;
		cout << "Unresolved symbol!" << endl;
		break;
	case 9:
		cout << "Symbol number error " << i <<endl;
		cout << "Operation is expected!" << endl;
		break;
	case 10:
		cout << "Expression is not compliete!" << endl;
		break;
	case 11:
		cout << "Too many opening brakets!" << endl;
		break;
	case 12:
		cout << "Symbol number error " << i <<endl;
		cout << "Expression inside brackets is expected!"<< endl;
	default:
		break;
	}
}
class Computer
{
protected:
	TStack <struct Lex> Val;
	TStack <struct Lex> Oper;
public:
	Computer(){}

	void Check(char *f, char end)
	{
		int Open = 0, i = 0, k = 0;
		struct Lex lex1;
		lex1.OpType = 0;
		lex1.Op = " ";
		while (*f && (*f != end))
		{
			switch (*f)
			{
			case ' ':
			case '\r':
			case'\n':
				f++;
				i++;
				continue;

			case '(':
				i++;
				if ((lex1.OpType == 0)||(lex1.OpType == 2) && (lex1.Op != ")"))
				{}
				else {Error(i, 1); k++;/*throw "Opertion is expected! Opening bracket error.";*/}
				Open++;
				lex1.OpType = 2;
				lex1.Op = "(";
				f++;
				break;
			case ')':
				i++;
				if((lex1.OpType == 1) || ((lex1.Op == ")")))
				{
				}
				else if (lex1.Op == "(")
				{
					Error(i, 12); k++;
				}
				else {Error(i, 2);k++;/* throw "Operand expected! Closing bracket error.";*/}
				Open--;
				lex1.OpType = 2;
				lex1.Op = ")";
				if (Open < 0)
				{Error(i, 3); /*throw "Too many closing brackets.";*/}
				f++;
				break;
			case '+':
				i++;
				if ((lex1.OpType == 1)||(lex1.Op == ")"))
				{
				}
				else {Error(i, 4); k++;/*throw "Operand expected!Statement '+' error.";*/}
				lex1.OpType = 2;
				lex1.Op = "+";
				f++;
				break;
			case '-':
				i++;
				//if ((lex1.OpType == 0) || (lex1.OpType == 1)||(lex1.Op == ")") || (lex1.Op == "("))
				//{}
				//else {Error(i, 5);k++;/*throw "Operand expected!Statement '-' error.";*/ }
				lex1.OpType = 2;
				lex1.Op = "-";
				f++;
				break;
			case '*':
				i++;
				if ((lex1.OpType == 1)||(lex1.Op == ")"))
				{}
				else {Error(i, 6);k++;/*throw "Operand expected!Statement '*' error.";*/ }
				lex1.OpType = 2;
				lex1.Op = "*";
				f++;
				break;
			case '/':
				i++;
				if ((lex1.OpType == 1)||(lex1.Op == ")"))
				{}
				else {Error(i, 7);k++;/*throw "Operand expected!Statement '/' error.";*/}
				lex1.OpType = 2;
				lex1.Op = "/";
				f++;
				break;
			default:
				if (!strchr ("0123456789", *f))
				{i++; Error(i, 8);k++;/*throw "Unresolved symbol!";*/ f++; lex1.OpType = 4;}
				else 
				{ 
					if ((lex1.OpType == 0) ||(lex1.OpType == 2) && (lex1.Op != ")"))
					{}
					else {Error(i, 9);k++;/*throw "Operation is expected!";*/}

					lex1.OpType = 1;
					char* a = f;
					lex1.Value = strtod(f, &f);
					i = i + (int)(f-a);
					while ((strchr(" \n\r", *f)) && (*f) && (*f != end)) 
					{
						f++;
						i++;
					}
				}
				break;
			}
			if ((*(f) == end)||(!*(f)) )
				if ((lex1.Op != ")") && (lex1.OpType != 1))
				{Error(i, 10);/*throw "Expression is not compliete!";*/ k++;}
		}
		if (Open != 0 )
		{Error(i, 11);/*throw "Too many opening brakets!";*/ k++;}
		if (k !=0) throw "Errors in the expression recording!";
	}

	char *Parse(char *f, char end)
	{ 
		struct Lex lex;

		lex.OpType = 0;
		while (*f && (*f != end))
		{
			switch(*f)
			{
			case ' ':
			case '\r':
			case'\n':
				f++;
				continue;
			case '(':
				lex.OpType = 2;
				lex.Op = "(";
				lex.Priority = 0;
				f++;
				Oper.Push(lex);
				continue;

			case ')':
				f++;
				if (!Oper.IsEmpty())
				{
					struct Lex lex2 = Oper.pop();
					while(lex2.Op != "(")
					{
						Val.Push(lex2);
						lex2 = Oper.pop();
					}
				}
				else throw "" ;
				continue;

			case '-':
				if (lex.OpType != 1)
				{
					while ((strchr(" \n\r", *f)) && (*f) && (*f != end)) f++;
					if(strchr ("0123456789", *(f+1)))
					{
						f++;
						lex.OpType = 1;
						lex.Value = (-1)*strtod(f, &f);
						while ((strchr(" \n\r", *f)) && (*f) && (*f != end)) f++;
					}
					else 
					{
						lex.OpType = 2;
						lex.Op = "-";
						lex.Priority = 3;
						f++;
					}
				}
				else 
				{
					lex.OpType = 2;
					lex.Op = "-";
					lex.Priority = 1;
					f++;
				}
				break;

			case '+':
				lex.OpType = 2;
				lex.Op = "+";
				lex.Priority = 1;
				f++;
				break;

			case '*':
				lex.OpType = 2;
				lex.Op = "*";
				lex.Priority = 2;
				f++;
				break;

			case '/':
				lex.OpType = 2;
				lex.Op = "/";
				lex.Priority = 2;
				f++;
				break;

			default:
				lex.OpType = 1;
				lex.Value = strtod(f, &f);
				while ((strchr(" \n\r", *f)) && (*f) && (*f != end)) f++;
			}
			if (lex.OpType == 2)
			{
				struct Lex lex2;
				if (!Oper.IsEmpty())
				{
					lex2 = Oper.pop();
					if ( lex2.Priority >= lex.Priority)
						Val.Push(lex2);
					else Oper.Push(lex2);
				}
				Oper.Push(lex);
			}
			else Val.Push(lex);
		}
		while (!Oper.IsEmpty())
			Val.Push(Oper.pop());
		return f;
	}

	double Compute (){
		double tmp,a,b, res;
		TStack <struct Lex> In;
		TStack <double> Res;
		struct Lex lex;

		res = 0;
		while ( !Val.IsEmpty())
			In.Push(Val.pop());
		while( !In.IsEmpty())
		{
			lex = In.pop();
			if (lex.OpType == 1)
				Res.Push(lex.Value);
			else
			{
				a = Res.pop();
				switch (lex.Op[0])
				{
				case '+':
					b = Res.pop();
					tmp =b + a;
					break;

				case '-':
					if (lex.Priority == 1)
					{
					if (Res.IsEmpty())
						b = 0;
					else b = Res.pop();
					tmp = b - a;
					}
					else 
					{
						tmp = 0 - a;
					}
					break;

				case '*':
					b = Res.pop();
					tmp = b * a;
					break;

				case '/':
					b = Res.pop();
					if (a != 0)
					{
						tmp = b/ a;
					}
					else throw "Division by zero is prohibited!";
					break;
				}
				res= tmp;
				Res.Push(res);
			}
		}
		return Res.pop();
	}
};
#endif _ARITHMETIC_