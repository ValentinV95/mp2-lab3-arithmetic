// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#ifndef arif_H
#define arif_H
#include "stack.h"
#include <string>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>
using namespace std;

TStack <double> Num;
TStack <char> Op;



class Lexem
{
	char op;
	int prior;
	double num;
	bool notop;
	bool binary;

public:
	Lexem(double number) { num = number; notop = true; binary = false; }
	Lexem(char oper){num = 0; notop = false; op = oper; prior = 0; binary = true;}
	void Parsing(string a);
	void Unar()
	{
		binary = !(binary);
	}
	int GetPrior()
	{
		return prior;
	}
	void Putprior(int a)
	{
		prior = a;
	}
	void SetVal(double a)
	{
		num = a;
	}
	double GetNum()
	{
		return num;
	}
	char GetOper()
	{
		return op;
	}
	bool GetType()
	{
		return notop;
	}



	~Lexem() {};
	friend ostream& operator<<(ostream &out, const Lexem &lex); 

};


vector<Lexem> PrePolish;
// checking block
 bool Skobki(string s);
 bool CheckSequence(string s);
 bool ValisOne(string s);
void BlockforString(string s);




#endif