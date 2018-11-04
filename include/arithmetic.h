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
    Lexem(double a) {
        num = a;
        op = 0;
        un_op = "";
    }
    Lexem(char a) {
        op = a;
    }
    Lexem(string a) {
        un_op = a;
    }
    ~Lexem() {};
    double Get_Num(){return num;}
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
void from_string_to_vector(string s, vector<Lexem>& str);
double calc(vector<Lexem> str);
void do_op(Stack<double>&a, char s);
bool check(Lexem last, Lexem& cur, int& flag);
string error_message(int i);
#endif