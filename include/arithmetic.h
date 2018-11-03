#ifndef _ARITHMETIC_H_
#define _ARITHMETIC_H_
#include <string>
#include <vector>
#include <set>
using namespace std;
enum type { number, binary_operation, unary_operation, op_bracket, cl_bracket, no_type };

union elem_or_oper
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

double Solver(const vector<TLexeme>& s);
double Сonverting_number(const string& s, int index, int sign);
TLexeme Check_number(const string &s, int &i, const set<char>& num, int sign);
vector<TLexeme> Create_lexeme_array(const string& s);
string New_line_without_spaces(const string &s);

#endif _ARITHMETIC_H_