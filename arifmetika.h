#pragma once
#include <iostream>
#include "arifmetika.cpp"
using namespace std;
class Lexem
{
private:
	double n;
	string op;
	bool check;
public:
	Lexem() noexcept;
	Lexem(double x) noexcept;
	Lexem(string s);
	~Lexem() noexcept;
	double getn() noexcept;
	string getop();
	bool is_num() noexcept;
	bool is_op() noexcept;
	int priority();
	void operator= (double x);
	void operator= (Lexem x);
	void operator= (string x);
	double work(string s) 
	{
		int i = 0, j = 0;
		double tmp, x, d, a0, a1, a2, a3, a4;
		Lexem mas[100];
		bool f1 = true, f2 = true, f3 = true, f4 = true, f5 = true;
	}
	int checking(Lexem* mas, int n)
	{
	
	}
	double find_des(Lexem* mas, int n)
	{ 
	
	}
};