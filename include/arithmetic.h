#ifndef arif_H
#define arif_H

#include "stack.h"
#include <string>
#include <stdio.h>
#include <map>
#include <vector>
#include <iostream>
using namespace std;



class Lexem
{
	char op;
	
	double num;
	bool notop;
	bool binary;

public:
	Lexem() {}
	Lexem(double number) { num = number; notop = true; binary = false; }
	Lexem(char oper){num = 0; notop = false; op = oper;  binary = true;}
	bool Binar();
	void IfUnar();
	double GetNum();
	char GetOper();
	bool GetType();
	void PutVal(double a, vector<Lexem> s);



	~Lexem() {};
	friend ostream& operator<<(ostream &out, vector<Lexem> &lex); 

};


vector<Lexem> Parsing(string a);
vector<Lexem> Calc(vector<Lexem> s);


// checking block
 
bool Skobki(string s);
bool CheckSequence(string s);
bool ValisOne(string s);
void DoPriority();
#endif