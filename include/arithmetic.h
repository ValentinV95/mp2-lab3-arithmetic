#ifndef arithmetic_h
#define arithmetic_h

#include <string>
#include "map"
#include "cmath"
#include "stack.h"
#define eps 1e-10

using namespace std;

void priority_creation();

bool Is_Digit(char n);
bool Is_Letter(char n);
bool Is_Operation(string op);
bool Is_Unary_Operation(string un_op);

class Lexem{
private:
    double num;
    bool is_num;
    bool is_op;
    bool is_un_op;
    string op;
    string un_op;
public:
	Lexem(double a) {is_num = true, is_op = false, is_un_op = false, num = a;}
    Lexem(string a) 
    {
        is_num = false;
        if(Is_Unary_Operation(a))
        {
            is_un_op = true, is_op = false;
            un_op = a;
        }
        else
        {
            is_op = true, is_un_op = false;
            op = a;
        }
    }
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
        return is_num;
    }
	bool Is_Op()
	{
		return is_op;
	}
    bool Is_Un_Op()
    {
		return is_un_op;
    }
};

void Push_Double(vector<Lexem>& str, string& s, int& i);
void Push_Math_F(vector<Lexem>& str, string& s, int& i);
void Push_Unary_Minus(vector<Lexem>& str, string& s, int& i);

bool check_parameters();
void clear_parameters();
vector<double> enter_parameters();
void set_parameters(vector<Lexem>& str, vector<double> par);

bool check(Lexem last, Lexem& cur, int& flag); //Check order of operations and operands
void from_string_to_vector(string s, vector<Lexem>& str); //Create vector<Lexem> && validates correctness of the string
vector<Lexem> RPN(vector<Lexem> str);

void do_op(Stack<double>&a, char s); //Performs the appropriate operations
double calc(vector<Lexem> str); //Calculates the value of an expression
string error_message(int i); 
#endif