// объявление функций и классов для вычисления арифметических выражений


#include "stack.h"
#include <string>
#include <iostream>
#include "stdlib.h"

using namespace std;

int WhatPriority(string symbol);
int WhatTip(string symbol);

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
		priority = WhatPriority(sym);
		UnOrBinOrDig = WhatTip(sym);
	}
};

double interpreter(string Str);
void firstcontrol(string Str);
void secondcontrol(Stack<TLexems> res);
double notation(Stack<TLexems> res);
double calculate(Stack<TLexems> not);
