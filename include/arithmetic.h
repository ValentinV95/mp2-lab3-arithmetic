#ifndef arifm
#define arifm

#include <string>
#include "map"
#include "cmath"
#include "stack.h"
#define eps 1e-10

using namespace std;

class Lexem{
private:
    double num;
    char op;
    string un_op;
public:
	Lexem(double a) { num = a, op = 0, un_op = ""; }
    Lexem(char a) {op = a;}
    Lexem(string a) {un_op = a;}
    ~Lexem() {};
    double Get_Num(){return num;}
    void Set_Param(double a) {num = a;}
    string Get_Op(){
        string s = "";
        s += op; 
        return s;
    }
    string Get_Un_Op(){return un_op;}
    bool Is_Num()
    {
        return (op == 0) && (un_op == "");
    }
	bool Is_Op()
	{
		return ((op == '+') || (op == '-') || (op == '*') || (op == '/'));
	}
    bool Is_Un_Op()
    {
		return ((un_op == "ln") || (un_op == "sqrt") || (un_op == "exp") || (un_op == "sin") || (un_op == "cos") || (un_op == "--"));
    }
};

void priority_creation();

bool Is_Digit(char n);
bool Is_Letter(char n);

bool check_parameters();
void clear_parameters();
vector<double> enter_parameters();
void set_parameters(vector<Lexem>& str, vector<double> par);

bool check(Lexem last, Lexem& cur, int& flag); //Check order of operations and operands
void from_string_to_vector(string s, vector<Lexem>& str); //Create vector<Lexem> && validates correctness of the string

void do_op(Stack<double>&a, char s); //Performs the appropriate operations
double calc(vector<Lexem> str); //Calculates the value of an expression
string error_message(int i); 
#endif