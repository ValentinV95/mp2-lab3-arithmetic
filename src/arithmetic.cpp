#include "arithmetic.h"
map <char, int> priority;
void priority_creation()
{
	priority['('] = 0;
	priority[')'] = 0;
	priority['+'] = 1;
	priority['-'] = 1;
	priority['*'] = 2;
	priority['/'] = 2;
}
bool Is_Digit(char n)
{
	return (n >= '0') && (n <= '9');
}
void from_string_to_vector(string s, vector<Lexem>& str)
{
    double b = 0.0;
    double b1 = 0.0;
    for(int i = 0; i < s.size(); i++)
    {
        int f = i;
        while(Is_Digit(s[i]))
        {
            b = b * 10.0 + double(s[i] - 48);
            i++;
        }
        if(s[i] == '.')
        {
            ++i;
            int f1 = i;
            while(Is_Digit(s[i]))
            {
                b1 = b1 * 10.0 + double(s[i] - 48);
                i++;
            }
            double m = 1.0;
            for(int j = 0; j < i - f1; j++)
            {
                m *= 10.0;
            }
            b1 /= m;
        }
        if(f != i)
        {
            i--;
            str.push_back(b + b1);
            b = 0.0;
            b1 = 0.0;
            continue;
        }
        str.push_back(s[i]);
    }
}
void do_op(Stack<double>&a, char s)
{
	double num2 = a.front(), num1;
	a.pop();
	num1 = a.front();
	a.pop();
	switch (s)
	{
	case '+':  a.push(num1 + num2); break;
	case '-':  a.push(num1 - num2); break;
	case '*':  a.push(num1 * num2); break;
	case '/':  a.push(num1 / num2); break;
	}
}
double calc(vector<Lexem> str)
{
	Stack<double> elem;
	Stack<char> opr;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i].Is_Num())
		{
			elem.push(str[i].Get_Num());
		}
		else if (str[i].Is_Op())
		{
			while (!opr.IsEmpty() && (priority[str[i].Get_Op()] <= priority[opr.front()]))
			{
				do_op(elem, opr.front());
				opr.pop();
			}
			opr.push(str[i].Get_Op());
		}
		else if (str[i].Get_Op() == '(')
		{
			opr.push(str[i].Get_Op());
		}
		else
		{
			while (opr.front() != '(')
			{
				do_op(elem, opr.front());
				opr.pop();
			}
			opr.pop();
		}
	}
	while (!opr.IsEmpty())
	{
		do_op(elem, opr.front());
		opr.pop();
	}
	return elem.front();
}