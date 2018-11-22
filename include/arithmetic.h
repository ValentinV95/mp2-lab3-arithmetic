// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#include <string>
#include <vector>
#include <sstream>
#include "stack.h"
using namespace std;

struct Operation
{
	char op;
	int prior;
};


class Lexeme
{
private:
	double number;
	Operation op;
	int check;
	int amount_of_arg;
public:
	Lexeme()
	{

	}
	Lexeme(double num)
	{
		number = num;
		check = 1;
	}
	Lexeme(char oper,int arg = 2)
	{
		op.op = oper;
		if (oper == '(')
		{
			op.prior = 0;
		}
		else if (oper == ')')
		{
			op.prior = 1;
		}
		else if (oper == '+' || oper == '-')
		{
			op.prior = 2;
		}
		else if (oper == '*' || oper == '/')
		{
			op.prior = 3;
		}
		else
		{
			op.prior = -1; //incorrect symbol
		}
		amount_of_arg = arg;
		check = 0;
	}
	bool can_go_next(vector <Lexeme>& a, int i);
	char get_oper();
	double get_number();
	int get_prior();
	bool is_op();
	bool is_op_br();
	bool is_cl_br();
	bool is_number();
	bool is_unary();
};

class Solver
{
private:
	vector <Lexeme> d;
public:
	void convert_string_to_lexeme(string& s);
	void convert_to_RPN();
	double solve();
};
