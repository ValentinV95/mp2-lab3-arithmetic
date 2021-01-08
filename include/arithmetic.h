#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__

#include <string>
#include "stack.h"
#include<iostream>
#include "math.h"

using namespace std;   

class TPostfix
{
    string infix;
    string postfix;
    public:
    TPostfix(string s)
    {
        infix = s;
        postfix = s;
    }
    string GetInfix() { return infix; }
    string GetPostfix()
    {
        return postfix;
    }
    int GetSizeInfix() { return infix.length(); }
    string ToPostfix();
    double Calculate(); 
    int Priort(char c);
};

#endif
