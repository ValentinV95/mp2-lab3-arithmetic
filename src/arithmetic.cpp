#include "arithmetic.h"
map <string, int> priority;
void priority_creation()
{
	priority["("] = 0;
	priority[")"] = 0;
	priority["+"] = 1;
	priority["-"] = 1;
	priority["*"] = 2;
    priority["/"] = 2;
    priority["--"] = 3;
    priority["ln"] = 3;
    priority["exp"] = 3;
    priority["cos"] = 3;
    priority["sin"] = 3;
    priority["sqrt"] = 3;
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
		case 6: return "Incorrect_first_symbol";
        case 7: return "Unacceptable_substring: ";
		default: return "Unknown_exception";
	}
}
bool Is_Digit(char n)
{
	return (n >= '0') && (n <= '9');
}
bool Is_Letter(char n)
{
    return (n >= 'a') && (n <= 'z');
}
bool check(Lexem last, Lexem& cur, int& flag)
{
    if((last.Get_Op() == "(") && cur.Get_Op() == "-")
    {
        string un_sub = "--";
		Lexem curt(un_sub);
        cur = curt;
        return true;
    }
    //incorrect lexem after operand
    if((last.Is_Num() && cur.Is_Num()) || (last.Is_Num() && (cur.Get_Op() == "(")) || (last.Is_Num() && cur.Is_Un_Op()))
    {
        flag = 0;
        return false;
    }
    //incorrect lexem after operation
    if((last.Is_Op() && cur.Is_Op()) || (last.Is_Op() && (cur.Get_Op() == ")")))
    {
        flag = 1;
        return false;       
    }
    //incorrect lexem after closing bracket
    if(((last.Get_Op() == ")") && cur.Is_Num()) || ((last.Get_Op() == ")") && (cur.Get_Op() == "(")) || ((last.Get_Op() == ")") && cur.Is_Un_Op()))
    {
        flag = 0;
        return false;
    }   
    //incorrect lexem after opening bracket
    if(((last.Get_Op() == "(") && cur.Is_Op()) || ((last.Get_Op() == "(") && (cur.Get_Op() == ")")))
    {
        flag = 1;
        return false;       
    }
    //incorrect lexem after unary operation
    if((last.Is_Un_Op() && (cur.Get_Op() == ")")) || (last.Is_Un_Op() && (cur.Is_Op())))
    {
        flag = 1;
        return false;       
    }
    return true;
}
void from_string_to_vector(string s, vector<Lexem>& str, bool& check_er)
{
    Stack<char> bkt; //Checking the bracket sequence
    double b = 0.0; //The integer part of number
    double b1 = 0.0; //Fractional part of the number
    string math_f = ""; //name of mathematical function
	if (!Is_Digit(s[0]) && s[0] != '(' && s[0] != '-' && !Is_Letter(s[0])) //Ckeck the first element
	{
		cout << error_message(6) << endl;
		check_er = false;
		return;
	}
    int k = 0;
    if(s[0] == '(')
    {
        str.push_back(s[0]);
		bkt.push('(');
        k++;
    }
    else if(s[0] == '-')
    {
        string un_sub = "--";
        str.push_back(un_sub);
        k++;
    }
    for(int i = k; i < s.size(); i++)
    {
        int f = i; //Flag for reading number
		Lexem cur(s[i]); //The current lexem 
		int flag; //Flag to check the correct sequence of operands and operations
		check_er = true; //Check incorrect enter
        while(Is_Digit(s[i]))
        {
            b = b * 10.0 + double(s[i] - 48);
            i++;
        }
        if(s[i] == '.')
        {
            if(f == i) //If find '.' before digits
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
        if(f != i) //Check whether the number was read
        {
            i--;
            str.push_back(b + b1);
            b = 0.0;
            b1 = 0.0;
            continue;
        }
        while(Is_Letter(s[i]))
        {
            math_f += s[i];
            i++;
        }
        if(f != i)//Check whether the math function was read
        {
            i--;
            Lexem temp(math_f);
            if(!temp.Is_Un_Op()) //math function input validation
            {
                cout << error_message(7) << math_f << endl;
                check_er = false;
                return;               
            }
            if(!str.empty() && !check(str.back(),temp,flag)) //Wrong order operation and operands
            {
                cout << error_message(4 + flag) << i + 1 << endl;
                check_er = false;
                return;
            }
            math_f = ""; 
            str.push_back(temp);
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
            else //No matching opening bracket
            {
                cout << error_message(2) << i + 1 << endl;
                check_er = false;
                return;
            }
        }
        else if(!cur.Is_Op()) //Unacceptable symbol
        {
            cout << error_message(3) << i + 1 << endl;
            check_er = false;
            return;
        }
        else if(!check(str.back(),cur,flag)) //Wrong order operation and operands
        {
            cout << error_message(4 + flag) << i + 1 << endl;
            check_er = false;
            return;
        }
        str.push_back(cur);
    }
	if (!bkt.IsEmpty()) //No matching closing bracket
	{
        cout << error_message(2) << s.size() + 1 << endl;
        check_er = false;
		return;
	}
}
void do_op(Stack<double>&a, string s, bool& check_er)
{
	double num2 = a.front(), num1;
	a.pop();
    Lexem t(s);
    if(t.Is_Un_Op())
    {
        if(s == "ln") 
        {
            if(num2 <= 0)
            {
                cout << "Error: out of range of function: ln(" << num2 << ")" << endl;
                check_er = false;
                return;            
            }
            a.push(log(num2));
        }
        else if(s == "sqrt") 
        {
            if(num2 < 0)
            {
                cout << "Error: out of range of function: sqrt(" << num2 <<")" << endl;
                check_er = false;
                return;            
            }
            a.push(sqrt(num2));
        } 
        else if(s == "cos") {a.push(cos(num2));}
        else if(s == "sin") {a.push(sin(num2));}
        else if(s == "exp") {a.push(exp(num2));}
        else {a.push(-(num2));}
    }
    else{
        num1 = a.front();
        a.pop();
        if(s == "+") a.push(num1 + num2);
        else if(s == "-") a.push(num1 - num2);
        else if(s == "*") a.push(num1 * num2);
        else  
        {
            if(num2 == 0)
            {
                cout << "Division by zero is impossible: " << num1 << "/";
                check_er = false;
                return;
            }
            a.push(num1 / num2); 
        }
    }
}
double calc(vector<Lexem> str)
{
	Stack<double> elem; //operands
	Stack<string> opr; //operations
    bool check_er = true; //check incorrect mathematical expression
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i].Is_Num())
		{
			elem.push(str[i].Get_Num());
		}
		else if (str[i].Is_Op() || str[i].Is_Un_Op())
		{
			string temp = str[i].Is_Op() ? str[i].Get_Op() : str[i].Get_Un_Op();
			while (!opr.IsEmpty() && 
				(str[i].Is_Op() && (priority[temp] <= priority[opr.front()]) ||    //binary operations in a row
					str[i].Is_Un_Op() && (priority[temp] < priority[opr.front()])))//unary operations from right to left
			{
				do_op(elem, opr.front(),check_er);
                if(!check_er)
                {
                    return 0;
                }
				opr.pop();
			}
			opr.push(temp);
		}
		else if (str[i].Get_Op() == ")")
		{
			while (!opr.IsEmpty() && opr.front() != "(")
			{
				do_op(elem, opr.front(), check_er);
				if (!check_er)
				{
					return 0;
				}
				opr.pop();
			}
			opr.pop();
		}
		else
		{
			opr.push(str[i].Get_Op());
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
