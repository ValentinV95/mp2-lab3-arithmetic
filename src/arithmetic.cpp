#include "C:\lab\mp2-lab3-arithmetic\include\arithmetic.h"
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
string error_message(int i)
{
	switch (i)
	{
		case 1: return "Point_before_digits_in_symbol: ";
		case 2: return "Wrong_bracket_sequence_in_symbol: ";
		case 3: return "Unacceptable_symbol: "; 
		case 4: return "Missed_operation_in_symbol: "; 
		case 5: return "Missed_operand_in_symbol: ";
		case 6: return "Uncorrect_first_symbol";
		default: return "Unknown_exception";
	}
}
bool Is_Digit(char n)
{
	return (n >= '0') && (n <= '9');
}
bool check(Lexem last, Lexem cur, int& flag)
{
    if((last.Is_Num() && cur.Is_Num()) || (last.Is_Num() && (cur.Get_Op() == '(')))
    {
        flag = 0;
        return false;
    }
    if((last.Is_Op() && cur.Is_Op()) || (last.Is_Op() && (cur.Get_Op() == ')')))
    {
        flag = 1;
        return false;       
    }
    if(((last.Get_Op() == ')') && cur.Is_Num()) || ((last.Get_Op() == ')') && (cur.Get_Op() == '(')))
    {
        flag = 0;
        return false;
    }   
    if(((last.Get_Op() == '(') && cur.Is_Op()) || ((last.Get_Op() == '(') && (cur.Get_Op() == ')')))
    {
        flag = 1;
        return false;       
    }
    return true;
}
void from_string_to_vector(string s, vector<Lexem>& str, bool& check_er)
{
    Stack<char> bkt;
    double b = 0.0;
    double b1 = 0.0;
	if (!Is_Digit(s[0]) && s[0] != '(')
	{
		cout << error_message(6) << endl;
		check_er = false;
		return;
	}
    for(int i = 0; i < s.size(); i++)
    {
        int f = i;
		Lexem cur(s[i]);
		int flag;
		check_er = true;
        while(Is_Digit(s[i]))
        {
            b = b * 10.0 + double(s[i] - 48);
            i++;
        }
        if(s[i] == '.')
        {
            if(f == i) // if find '.' before digits
            {
                cout << error_message(1) << i + 1 << endl;
                check_er = false;
                return;
            }
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
        if(s[i] == '(')
        {
            bkt.push('(');
        }
        else if(s[i] == ')')
        {
            if(!bkt.IsEmpty() && bkt.front() == '(')
            {
                bkt.pop();
            }
            else //no matching opening bracket
            {
                cout << error_message(2) << i + 1 << endl;
                check_er = false;
                return;
            }
        }
        else if(!cur.Is_Op()) //unacceptable symbol
        {
            cout << error_message(3) << i + 1 << endl;
            check_er = false;
            return;
        }
        else if(!check(str.back(),cur,flag)) //wrong order operation and operands
        {
            cout << error_message(4 + flag) << i + 1 << endl;
            check_er = false;
            return;
        }
        str.push_back(s[i]); 
    }
	if (!bkt.IsEmpty()) //no matching closing bracket
	{
        cout << error_message(2) << s.size() + 1 << endl;
        check_er = false;
		return;
	}
}
void do_op(Stack<double>&a, char s, bool& check_er)
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
	case '/': 
    {
        if(num2 == 0)
        {
            cout << "Division by zero is impossible: 1/";
            check_er = false;
            return;
        }
        a.push(num1 / num2); 
    }
    break;
	}
}
double calc(vector<Lexem> str)
{
	Stack<double> elem;
	Stack<char> opr;
    bool check_er = true;
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
				do_op(elem, opr.front(),check_er);
                if(!check_er)
                {
                    return 0;
                }
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
				do_op(elem, opr.front(),check_er);
                if(!check_er)
                {
                    return 0;
                }
				opr.pop();
			}
			opr.pop();
		}
	}
	while (!opr.IsEmpty())
	{
		do_op(elem, opr.front(),check_er);
        if(!check_er)
        {
            return 0;
        }
		opr.pop();
	}
	return elem.front();
}
