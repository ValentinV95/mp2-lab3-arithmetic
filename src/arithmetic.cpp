#include "arithmetic.h"


string error_message(int i)
{
	switch (i)
	{
		case 1: return "Point_before_digits_in_symbol: (";
		case 2: return "Wrong_bracket_sequence_in_symbol: (";
		case 3: return "Unacceptable_symbol: ("; 
		case 4: return "Missed_operation_in_symbol: ("; 
		case 5: return "Missed_operand_in_symbol: (";
		case 6: return "Incorrect_first_symbol";
        case 7: return "Unacceptable_substring: ";
        case 8: return "Incorrect_last_symbol";
        case 9: return "Error: out of range of function: ln(";
        case 10: return "Error: out of range of function: sqrt(";
        case 11: return "Division by zero is impossible: ";
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

vector<vector<int>> parameter(26);
bool check_parameters()
{
    for(int i = 0; i < parameter.size(); i++)
    {
        if(!parameter[i].empty())
        {
            return true;
        }
    }
    return false;
}
void clear_parameters()
{
    for(int i = 0; i < parameter.size(); i++)
    {
        if(!parameter[i].empty()) {parameter[i].clear();}
    }
}
vector<double> enter_parameters()
{
    vector<double> par;
    cout << "Please, enter parameter's value:" << endl;
    for(int i = 0; i < parameter.size(); i++)
    {
        if(!parameter[i].empty())
        {
            double val;
            cout << (char)(i + 97) << " = ";
            cin >> val;
            par.push_back(val);
        }
    }
	return par;
}
void set_parameters(vector<Lexem>& str, vector<double> par)
{
    int k = -1;
    for(int i = 0; i < parameter.size(); i++)
    {
        for(int j = 0; j < parameter[i].size(); j++)
        {
            if(j == 0) {k++;}
            str[parameter[i][j]].Set_Param(par[k]);
        }
    }
}

bool check(Lexem last, Lexem& cur, int& flag) 
{
    //catch unary minus
    if((last.Get_Op() == "(") && cur.Get_Op() == "-")
    {
        string un_sub = "--";
		Lexem curt(un_sub);
        cur = curt;
        return true;
    }
    //incorrect lexem after operand
    if( last.Is_Num() && ( cur.Is_Num() || (cur.Get_Op() == "(") || cur.Is_Un_Op() ))
    {
        flag = 0;
        return false;
    }
    //incorrect lexem after operation
    if( last.Is_Op() && ( cur.Is_Op() || (cur.Get_Op() == ")") ))
    {
        flag = 1;
        return false;       
    }
    //incorrect lexem after closing bracket
    if( (last.Get_Op() == ")") && ( cur.Is_Num() || (cur.Get_Op() == "(") || cur.Is_Un_Op() ))
    {
        flag = 0;
        return false;
    }   
    //incorrect lexem after opening bracket
    if( (last.Get_Op() == "(") && ( cur.Is_Op() || (cur.Get_Op() == ")") ))
    {
        flag = 1;
        return false;       
    }
    //incorrect lexem after unary operation
    if( last.Is_Un_Op() && ( (cur.Get_Op() == ")") || cur.Is_Op() ))
    {
        flag = 1;
        return false;       
    }
    return true;
}

void from_string_to_vector(string s, vector<Lexem>& str)
{
    Stack<char> bkt; //Checking the bracket sequence
    double integer = 0.0; //The integer part of number
    double fract = 0.0; //Fractional part of the number
    string math_f = ""; //Name of mathematical function
	if (!Is_Digit(s[0]) && s[0] != '(' && s[0] != '-' && !Is_Letter(s[0])) //Ckeck the first element
	{
        throw(6);
	}
    int k = 0;
    if(s[0] == '(')
    {
        str.push_back(s[0]);
		bkt.push('(');
        k++;
    }
    else if(s[0] == '-')//Catch unary minus
    {
        string un_sub = "--";
        str.push_back(un_sub);
        k++;
    }
    for(int i = k; i < s.size(); i++)
    {
        int f = i; //Flag for reading number
		Lexem cur(s[i]); //The current lexem 
		int flag; //Flag to determine the type of error
        while(Is_Digit(s[i])) //Read integer part of number
        {
            integer = integer * 10.0 + double(s[i] - 48);
            i++;
        }
        if(s[i] == '.')
        {
            if(f == i) //If find '.' before digits
            {
                throw(make_pair(1,i + 1));
            }
            ++i;
            int f1 = i;
            while(Is_Digit(s[i])) //Read fractional part of number
            {
                fract = fract * 10.0 + double(s[i] - 48);
                i++;
            }
            double m = 1.0;
            for(int j = 0; j < i - f1; j++)
            {
                m *= 10.0;
            }
            fract /= m;
        }
        if(f != i) //Check whether the number was read
        {
            Lexem curnum(integer + fract);
            if(!str.empty() && !check(str.back(),curnum,flag)) //Wrong order of operation and operands
            {
                throw(make_pair(4 + flag,i + 1));
            }
            i--;
            str.push_back(curnum);
            integer = 0.0;
            fract = 0.0;
            continue;
        }
        while(Is_Letter(s[i])) //Read mathematical function
        {
            math_f += s[i];
            i++;
        }
        if(f == i - 1)//Check whether the parameter was read
        {
            Lexem curnum(42.42);
            if(!str.empty() && !check(str.back(),curnum,flag)) //Wrong order of operations and parameters
            {
                throw(make_pair(4 + flag,i + 1));
            }
            --i;
            parameter[int(s[i] - 97)].push_back(str.size());
            str.push_back(curnum);
            math_f = ""; 
            continue;
        }
        if(f != i)//Check whether the math function was read
        {
            --i;
            Lexem temp(math_f);
            if(!temp.Is_Un_Op()) //Math function input validation
            {
                throw(make_pair(7,math_f));            
            }
            if(!str.empty() && !check(str.back(),temp,flag)) //Wrong order of operations and operands
            {
                throw(make_pair(4 + flag,i + 1));
            }
            math_f = ""; 
            str.push_back(temp);
            continue;
        }
        if(!cur.Is_Op()) 
        {
            if(s[i] == '(') //Check right braket sequence
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
                    throw(make_pair(2,i + 1));
                }
            }        
            else    //Unacceptable symbol
            {    
                throw(make_pair(3,i + 1));
            }
        }
        if(!check(str.back(),cur,flag)) //Wrong order of operations and operands
        {
            throw(make_pair(4 + flag,i + 1));
        }
        str.push_back(cur);
    }
	if (!bkt.IsEmpty()) //No matching closing bracket
	{
        throw(make_pair(2,s.size() + 1));
	}
    int flag;
    if(str.size() > 1) //Ckeck the last element
    {
        if(!str.back().Is_Num() && str.back().Get_Op() != ")")
        {
            throw(8);
        }
        if(!check(str[str.size() - 2],str.back(),flag)) //Wrong order of operations and operands
        {
            throw(make_pair(4 + flag, str.size() + 1));
        }
    }
}
void do_op(Stack<double>&a, string s)
{
	double num2 = a.front();
	a.pop();
    Lexem t(s);
    if(t.Is_Un_Op())
    {
        if(s == "ln") 
        {
            if(num2 <= 0)
            {   
                throw(make_pair(9, num2));  
            }
            a.push(log(num2));
        }
        else if(s == "sqrt") 
        {
            if(num2 < 0)
            {
                throw(make_pair(10, num2));      
            }
            a.push(sqrt(num2));
        } 
        else if(s == "cos") {a.push(cos(num2));}
        else if(s == "sin") {a.push(sin(num2));}
        else if(s == "exp") {a.push(exp(num2));}
        else {a.push(-(num2));}
    }
    else{
        double num1 = a.front();
        a.pop();
        if(s == "+") a.push(num1 + num2);
        else if(s == "-") a.push(num1 - num2);
        else if(s == "*") a.push(num1 * num2);
        else  
        {
            if(abs(num2) < eps)
            {
                throw(num1); 
            }
            a.push(num1 / num2); 
        }
    }
}
double calc(vector<Lexem> str)
{
    Stack<double> elem; //operands
    Stack<string> opr; //operations
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i].Is_Num())
        {
            elem.push(str[i].Get_Num());
        }
        else if (str[i].Is_Op() || str[i].Is_Un_Op())
        {
            string temp = str[i].Is_Op() ? str[i].Get_Op() : str[i].Get_Un_Op();
            if(opr.IsEmpty())
            {
                opr.push(temp);
                continue;
            }
            while (!opr.IsEmpty() &&
                (str[i].Is_Op() && (priority[temp] <= priority[opr.front()])) || //binary operations in a row
                (str[i].Is_Un_Op() && (priority[temp] < priority[opr.front()])))//unary operations from right to left
            {
                do_op(elem, opr.front());
                opr.pop();
            }
            opr.push(temp);
        }
        else if (str[i].Get_Op() == ")")
        {
            while (!opr.IsEmpty() && opr.front() != "(")
            {
                do_op(elem, opr.front());
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
        do_op(elem, opr.front());
        opr.pop();
    }
    return elem.front();
}
