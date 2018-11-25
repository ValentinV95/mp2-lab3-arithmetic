// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#include <string>
#include "stack.h"
enum type{oper,num,o_b,c_b};
class Oper_or_numb
{
private:
	int lvl;
	char op;
	type on;
	double val;
public:
	Oper_or_numb();
	Oper_or_numb(char c);
	Oper_or_numb(double a);
	~Oper_or_numb() { lvl = 0; val = 0; };
	void Set(double a) 
	{
		on = num;
		val = a;
	}
	void Set(char c) {
		on = oper;
		switch (c)
		{
		case '+':
		{
			lvl = 1;
			op = '+';
			break;
		}
		case '-':
		{
			lvl = 1;
			op = '-';
			break;
		}
		case '*':
		{
			lvl = 2;
			op = '*';
			break;
		}
		case '/':
		{
			lvl = 2;
			op = '/';
			break;
		}
		case '(':
		{
			op = '(';
			break;
		}

		}
	};;
	//void Set(type)
	type Get_type() { return on; }
	double Get_value() { return val; }
	int Get_lvl() { return lvl; };
	char Get_op() { return op; };
	Oper_or_numb& operator=(Oper_or_numb& a);
};
class Lexeme
{
private:
	Stack <double> TStack;
	char* c;
	type* kind;
	int n;
public:
	Lexeme( char* c1);
	type Get_kind(int i) { return kind[i]; };
	char Get_c(int i) { return c[i]; };
	double Answer(Oper_or_numb* o);
	Oper_or_numb* RPN();
};
