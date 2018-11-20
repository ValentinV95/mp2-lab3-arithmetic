// объявление функций и классов для вычисления арифметических выражений


#include "stack.h"
#include <string>
#include <iostream>
#include "stdlib.h"

using namespace std;



class TLexems
{
	public:
	string symbols;//
	int priority;//
	int UnOrBinOrDig;//


	TLexems ()
	{}
	TLexems (string sym)
	{
		symbols=sym;
		priority = WhatP(sym);
		UnOrBinOrDig = WhatT(sym);
	}
	
	

	int WhatT(string symbol)
	{
		if((symbol=="+")||(symbol=="-")||(symbol=="*")||(symbol=="/"))
			return 2;
		if((symbol=="(")||(symbol==")"))
			return 3;

		return 0;
	}

	int WhatP(string symbol)
		{
		if((symbol=="+")||(symbol=="-"))
			return 1;
		if((symbol=="*")||(symbol=="/"))
			return 3;
		if((symbol==")")||(symbol=="("))
			return 5;
		return 0;
	}
};

double interpreter(string Str);
void firstcontrol(string Str);
void secondcontrol(Stack<TLexems> res);
double notation(Stack<TLexems> res);
double calculate(Stack<TLexems> not);
