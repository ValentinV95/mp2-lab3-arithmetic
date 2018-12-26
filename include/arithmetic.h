// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#include "stack.h"
using namespace std;
class Lexem
{
private:
	double IsNum;
	char IsOper;
	int k;
public:
	Lexem() {};
	~Lexem() {};
	Lexem(char, int);
	Lexem(double, int);
	void set(char, int);
	void set(double, int);
	int sign();
	double number();
	char operation();
};
int priority(char operation);
Lexem* PolishRecord(string, int &);
double result(Lexem*, int);
bool errors(string);
