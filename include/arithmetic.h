#ifndef _ARITHMETIC_H_
#define _ARITHMETIC_H_
#include "stack.h"
#include <string>
using namespace std;

enum type 
{	
	number, 
	binary_operation, 
	unary_operation, 
	op_bracket, 
	cl_bracket,
	no_type
};
enum sign 
{	
	positive, 
	negative 
};
enum errors 
{	
	division_by_zero, 
	incorrect_point, 
	unknown_symbol, 
	incorrect_first_symbol, 
	incorrect_last_symbol, 
	wrong_bracket_sequence, 
	missed_operation_or_operand
};

struct elem_or_oper
{
	double elem;
	char oper;
};

class TLexeme
{
private:
	elem_or_oper value;
	int type_elem;
public:
	TLexeme();
	TLexeme(char, int t = binary_operation);
	TLexeme(double);
	TLexeme(const TLexeme&);
	TLexeme& operator=(const TLexeme&);
	~TLexeme() {};
	elem_or_oper GetValue() const;
	int GetType() const;
};

double Calculate(const string& s);
double Solver(const vector<pair<TLexeme, int>>& s);
double Сonverting_number(const string& s, int index, int sign);
TLexeme Check_number(const string &s, int &i, int sign);
vector<pair<TLexeme, int>> Create_lexeme_array(const string& s);
string New_line_without_spaces(const string &s);
vector<pair<TLexeme,int>> Create_RPN_array(const vector<pair<TLexeme, int>>& v);
void Error_checking(const vector<pair<TLexeme, int>>& v);
bool Type_checking(const vector<pair<TLexeme, int>>& v, int type);
string Error_output(pair<int, int> err);
pair<bool, int> Check_unary_minus(const string& str, int &i);

#endif _ARITHMETIC_H_