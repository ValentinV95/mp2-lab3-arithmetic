#ifndef arifm
#define arifm

#include <string>
#include "map"
#include "stack.h"

using namespace std;
class Lexem{
private:
    double num;
    char op;
public:
    Lexem(double a) {
        num = a;
        op = 0;
    }
    Lexem(char a) {
        op = a;
    }
    ~Lexem() {};
    double Get_Num(){return num;}
    char Get_Op(){return op;}
    bool Is_Num()
    {
        return op == 0;
    }
	bool Is_Op()
	{
		return ((op == '+') || (op == '-') || (op == '*') || (op == '/'));
	}
};
void priority_creation();
bool Is_Digit(char n);
void from_string_to_vector(string s, vector<Lexem>& str, bool& check_er);
double calc(vector<Lexem> str);
void do_op(Stack<double>&a, char s, bool& check_er);
bool check(Lexem last, Lexem cur, int& flag);
string error_message(int i);
#endif