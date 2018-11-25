
#include "arithmetic.h"
#include "stack.h"
#include "iostream"

Oper_or_numb::Oper_or_numb()
{
	on = oper;
}
Oper_or_numb::Oper_or_numb(char c)
{
	on = oper;
	switch (c)
	{
	case '+':
	{
		lvl = 1;
		op = '+';
		break;
	}
	case '-':
	{
		lvl = 1;
		op = '-';
		break;
	}
	case '*':
	{
		lvl = 2;
		op = '*';
		break;
	}
	case '/':
	{
		lvl = 2;
		op = '/';
		break;
	}
	case '(':
	{
		op = '(';
		break;
	}

	}
};
Oper_or_numb::Oper_or_numb(double a)
{
	on = num;
	val = a;
}
Oper_or_numb& Oper_or_numb::operator=(Oper_or_numb& a)
{
	lvl = a.lvl;
	op = a.op;
	on = a.on;
	val = a.val;
	return(*this);
}
Lexeme::Lexeme( char* c1)
{
	
	kind = new type[strlen(c1)];
	c = c1;
	int t = 0;
	double a;
	double k = 1;
	switch (c1[0])
	{
	case('1'):
	case('2'):
	case('3'):
	case('4'):
	case('5'):
	case('6'):
	case('7'):
	case('8'):
	case('9'):
	case('0'):
	{
		
		a = c1[0]-'0';
		kind[0] = num;
		TStack.Set(a);
		break;
	}
	case('('):
	{
		t++;
		kind[0] = o_b;
		if (c1[1] == '-')
			kind[0] = num;
		
		break;
	}
	default:
	{
		throw "Not able lexeme";
		break;
	}
	}
	
	switch (c1[1])
	{
	case('('):
	{
		t++;
		kind[1] = o_b;
		if (c1[2] == '-')
			kind[1] = num;
		break;
	}
	case('.'):
	{
		
		if ((kind[0] != num) && (kind[2] != num))
			throw "Point out of number";
		else
		{
			k *= 0.1;
			kind[1] = num;
		}
		break;
	}
	case('1'):
	case('2'):
	case('3'):
	case('4'):
	case('5'):
	case('6'):
	case('7'):
	case('8'):
	case('9'):
	case('0'):
	{
		kind[1] = num;
		if (kind[0] == num)
		{
			TStack.Get();
			a =10*a+ c1[1] - '0';
		}
		else
		{
			a = c1[1] - '0';
		}
		TStack.Set(a);
		break;
	}
	case('+'):
	case('-'):
	case('*'):
	case('/'):
	{

		if ((c1[1] == '-') && (c1[0] == '('))
			switch (c1[2])
			{
			case('1'):
			case('2'):
			case('3'):
			case('4'):
			case('5'):
			case('6'):
			case('7'):
			case('8'):
			case('9'):
			case('0'):
			case('('):
			{
				kind[1] = num;
				break;
			}
			default:
			{
				throw "Not able lexeme";
				break;
			}
			}
		else
			kind[1] = oper;
			break;
	}

	default:
	{
		throw "Not able lexeme";
		break;
	}
	}

	for (int i = 2;i < strlen(c1);i++)
	{
		if (t >= 0)
			switch (c1[i])
			{
			case('1'):
			case('2'):
			case('3'):
			case('4'):
			case('5'):
			case('6'):
			case('7'):
			case('8'):
			case('9'):
			case('0'):
			{
				
				if (c1[i - 1] == ')')
					throw "Closed bracket before number";
				if (kind[i - 1] == num)
				{

					if (k != 1)
					{
						TStack.Get();
						if (a >= 0)
							a += k * (c1[i] - '0');
						else
							a -= k * (c1[i] - '0');
						k *= 0.1;

					}
					else
						if (c1[i - 1] == '-')
						{
							a = -1 * (c1[i] - '0');
							
						}
						else
							if (c1[i - 1] == '(')
								break;
							else
							{
								TStack.Get();
								if(a>=0)
									a = a * 10 + (c1[i] - '0');
								else
									a = a * 10 - (c1[i] - '0');
							}
				}
				else
					a = (c1[i] - '0');
				TStack.Set(a);
				kind[i] = num;
				break;
			}
			case('+'):
			case('-'):
			case('*'):
			case('/'):
			{
				
				if ((kind[i - 1] != num) && (kind[i - 1] != c_b))
					throw "Open bracket or operator before operator";
				k = 1;
				if (i + 1 >= strlen(c1))
					throw "Operator in the end";
				if ((c1[i] == '-') && (c1[i - 1] == '('))
					switch (c1[i + 1])
					{
					case('1'):
					case('2'):
					case('3'):
					case('4'):
					case('5'):
					case('6'):
					case('7'):
					case('8'):
					case('9'):
					case('0'):
					case('('):
					{
						kind[i] = num;
						break;
					}
					default:
					{
						throw "Not able lexeme";
						break;
					}
					}
				else
					kind[i] = oper;
				break;

			}

			case('('):
			{
				if ((kind[i - 1] != o_b) && (kind[i - 1] != oper)&&(c[i-1]!='-'))
					throw "Number or closed bracket before open bracket";
				
				t++;
				kind[i] = o_b;
				if ((i + 1 < strlen(c1)) && (c1[i + 1] == '-'))
				{
					kind[i] = num;
				}
				break;
			}
			case(')'):
			{
				if ((kind[i - 1] != num) && (kind[i - 1] != c_b))
					throw "Operator or open bracket before closed bracket";
				k = 1;
				t--;
				kind[i] = c_b;
				if ((kind[i - 1] == num) && (a < 0))
					kind[i] = num;
				break;
			}
			case('.'):
			{
				if ((kind[i - 1] != num) && (kind[i + 1] != num))
					throw "Point out of number";
				else
				{
					k *= 0.1;
					kind[i] = num;

				}
				break;
			}
			default:
			{
				throw "Not able lexeme";
				break;
			}
			}
		else
			throw "Close bracket before open bracket";
	}
	if (t!=0)
		throw "Not equal open and close brackets";
}
Oper_or_numb* Lexeme::RPN()
{
	Oper_or_numb* o;
	Oper_or_numb o1;
	o = new Oper_or_numb[strlen(c)];
	int j = 0;
	int s = 0;
	int i;
	int t=0;
	int k = 0;
	int a = 1;
	int b = 0;
	Stack <double> S;
	Stack <Oper_or_numb> S1;
	int v = TStack.Get_pos();
	for (int i = 0;i < v;i++)
	{
		S.Set(TStack.Get());
	}
	for (int i = 0;i < strlen(c);i++)
	{
		switch (Get_kind(i))
		{
		case num:
		{
			if ((i > 0) && (c[i - 1] == '-') && (c[i - 2] == '('))
			{
				o[j].Set(-1.0);
				k++;
				t++;
				j++;
				s++;
				o1.Set(c[i]);
				S1.Set(o1);
			}
			while ((i < strlen(c) - 1) && (kind[i + 1] == num)&&(c[i+1]!='('))
			{
				i++;
			}

		
			
				if ((c[i] != '-')||(kind[i]==oper))
				{
					o[j].Set(S.Get());
					j++;
					s++;
				}
				
			
			break;
		}
		case oper:
		{
			o1.Set(c[i]);
			if (S1.IsEmpty())
			{
				S1.Set(o1);
				
			}
			else
			{
				
				if (S1.Top().Get_op() == '(') 
				{
					S1.Set(o1);
					
				
				}
				else
				if (S1.Top().Get_lvl() >= o1.Get_lvl())
				{
					o[j].Set(S1.Get().Get_op());
					S1.Set(o1);
					s++;
					j++;
					
				}
				else
				{
				
					S1.Set(o1);
					s++;
				}
			}
			break;
		}
		case o_b:
		{
			t++;
			if ((i > 0) && (c[i - 1] == '-') && (c[i - 2] == '('))
			{
				
				o[j].Set(-1.0);
				k ++;
				t++;
				j++;
				s++;
			}
			o1.Set(c[i]);
			S1.Set(o1);
			break;
		}
		case c_b:
		{
				t--;
				
				
				
				if (((t == 0) || (t - k == 0)) && (k))
				{
					
					k--;
					a++;
					o[j+a-1].Set('*');
					j++;
					s++;
				}
				else
				{
					if (a)
					{
						
						o[j - a + 1].Set(S1.Get().Get_op());
						a--;
						j++;
						s++;
						S1.Get();
					}
					else
					{

						o[j].Set(S1.Get().Get_op());
						j++;
						s++;
						S1.Get();

					}
				}
			
			break;
		}
		}
	}
	for (;j <= s;j++)
	{
		o[j].Set(S1.Get().Get_op());
	}
	
	

	n = j+1;
	return(o);
}
double Lexeme::Answer(Oper_or_numb* o)
{
	
	double a, b;
	Stack<double> S;

	for (int i = 0;i < n;i++)
	{
		if (o[i].Get_type() == num)
		{
			S.Set(o[i].Get_value());
		}
			else
			switch (o[i].Get_op())
			{
			case '*':
			{
				a = S.Get();
				b = S.Get();
				b *= a;
				S.Set(b);
				break;
			}
			case '-':
			{
				a = S.Get();
				b = S.Get();
				b -= a;
				S.Set(b);
				break;
			}
			case '+':
			{
				a = S.Get();
				b = S.Get();
				b += a;
				S.Set(b);
				break;
			}
			case '/':
			{
				a = S.Get();
				b = S.Get();
				b /= a;
				S.Set(b);
				break;
			}
			}
	}
	
	return(S.Get());
}

