// объявление функций и классов для вычисления арифметических выражений
#ifndef _ARITHMETIC_H_
#define _ARITHMETIC_H_
#include <string>
#include "stack.h" 

using namespace std;

class lexem {
	double n;
	string o;
	bool p;	
public:
	lexem() {}
	lexem(double x) {
		n = x;
		p = true;
	}
	lexem(string s) {
		o = s;
		p = false;	
	}
	~lexem() {}

	double getnum() {return n;}

	string getop() {
		string s = "";
        s += o; 
        return s;}

	bool isnum() {return p;}

	bool isop() {return !p;}

	int getprior() { // метод для получения приоритета операции
		if (o == "+") {return 2;}
		else if (o == "-") {return 2;}
		else if (o == "*") {return 3;}
		else if (o == "/") {return 3;}
		else if (o == "(") {return 1;}
		else if (o == ")") {return 0;}
		else if (o == "un-") {return 4;}
		else if (o == "sin") {return 4;}
		else if (o == "cos") {return 4;}
		else if (o == "ln") {return 4;}
		else if (o == "exp") {return 4;}
	}
	void operator= (double x) {		
		n = x;
		p = true;
		/*cout << "x.getnum()" << endl;
		cout << p << endl;*/
	}
	void operator= (lexem x) {
		if (x.isnum()) {
			n = x.getnum();
			p = true;
		} else {		
		o = x.getop();
		p = false;
		}
		
		/*cout << "x.getop()" << endl;
		cout << o << endl;
		cout << p << endl;*/
	}

	void operator= (string x) {				
		o = x;
		p = false;
		
	}
};

double solve( string );

int proverka (lexem* , int );

double calculate (lexem* , int ); 
#endif _ARITHMETIC_H_