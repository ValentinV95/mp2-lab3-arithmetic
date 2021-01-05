// ���������� ������� � ������� ��� ���������� �������������� ���������
#include < string>
#include< iostream>
#include"stack.h"
using namespace std;

class Split
{
private:
	string s;
	int index;
public:
	Split(string t)
	{
		s = t;
		index = 0;
	}
	Split()
	{
		s = "";
		index = 0;
	}
	string GetLex()
	{
		string Lex = "";
		if (s[index] >= '0' && s[index] <= '9' || s[index]=='.' || 
			s[index] >= 'a' && s[index] <= 'z' ||
			s[index]=='-' &&(index==0 || s[index-1]>'9' || s[index-1]<'0'))// ��� �����
		{
			int i = index;
			while (s[i] >= '0' && s[i] <= '9' || s[i] == '.'|| 
				   s[i] >= 'a' && s[i] <= 'z' ||
				   s[i]=='-'&&(i == 0 || s[i - 1] > '9' || s[i - 1] < '0'))
				i++;
			Lex = s.substr(index, i - index);
			index = i;
		}
		else if (index < s.length())
		{
			Lex = string(1, s[index]);


			index++;
		}
		return Lex;
	}
	string GetLex(char k)
	{
		string Lex = "";
		if (s[index] >= '0' && s[index] <= '9' || s[index] == '.' ||
			s[index] >= 'a' && s[index] <= 'z' ||
			s[index] == '-' && (index == 0 || s[index - 1] > '9'|| s[index - 1] < '0'))// ��� �����
		{
			int i = index;
			while (s[i] >= '0' && s[i] <= '9' || s[i] == '.'|| 
				   s[i] >= 'a' && s[i] <= 'z' ||
				   s[i] == '-' && (i == 0 || s[i - 1] > '9' || s[i - 1] < '0'))
				i++;
			Lex = s.substr(index, i - index);
			index = i;
			if (s[index] == k)
				index++;
		}
		else if (index < s.length())
		{
			Lex = string(1, s[index]);
			index++;
			if (s[index] == k)
				index++;
		}
		return Lex;
	}
	int Getposition()
	{
		return index;
	}
};

class arithmetic 
{
	string input;
	string output; 
	double result;

public:
	arithmetic(string s)
	{
		input = s;
		output = "";
		result = 0;
	}
	string Process() 
	{
		string nomber = "";
		 output = "";
		TStack<int> st;
		Split str(input);

		string lexsema = str.GetLex();
		while (lexsema != "")
		{
			if (lexsema[0] >= '0' && lexsema[0] <= '9'|| lexsema[0]=='-' && lexsema.length() > 1 
				|| lexsema[0]>='a'&& lexsema[0]<='z')// ����� �����
			{
				output += lexsema;
				output += " ";
			}
			else // + - *  / ()
			{
				//output += " ";
				if (lexsema[0] == '(')
				{
					st.Put(lexsema[0]);
				}
				else if (st.IsEmpty())
				{
					int d = Prioritet(lexsema[0]);
					if (d < 0)
					{
						std::cout << " not correct operation";
						std::cout << " position " << str.Getposition() << endl;
						throw "not correct operation";
						return "";
					}
					st.Put(lexsema[0]);
				}
				else
				{
					if (lexsema[0] == ')')// ��������� ������� �� ����� � �������� ������ �� ��� ���, ���� �� �������� � ����� ����������� ������
					{
						int c;
						if (!st.IsEmpty())
							c = st.Get();
						else
						{
							std::cout << " not found ( ";
							std::cout << " position " << str.Getposition() << endl;
							throw "( not found";
							return "";
						}

						while (c != '(')
						{
							output += c;
							output += " ";//
							if (!st.IsEmpty())
								c = st.Get();
							else
							{
								std::cout << " not found ( ";
								std::cout << " position " << str.Getposition() << endl;
								throw "( not found";
								return "";
							}

						}
					}

					//if (Prioritet(input[i] > Prioritet(st.See())))
					else
					{
						int d = Prioritet(lexsema[0]);
						if (d < 0)
						{
							std::cout << " not correct operation";
							std::cout << " position " << str.Getposition() << endl;
							throw "not correct operation";
							return"";
						}

						if (Prioritet(lexsema[0]) > Prioritet(st.See()))
						{
							st.Put(lexsema[0]);// ��������� � ����( �� �������)
						}
						else
						{
							while (Prioritet(lexsema[0]) <= Prioritet(st.See()))
							{
								output += st.Get();
								output += " ";
							}
							st.Put(lexsema[0]);
						}
					}
				}
			}
			lexsema = str.GetLex();
		}

		while (!st.IsEmpty())
		{
			int c = st.Get();
			if (c == '(')
			{
				std::cout << " found ( with out )" << endl;
				throw ") not found";
				return "";
			}
			output += c;
			output += " ";
		}
		return output;
	}

	double calculat()
	{
		result = 0;
		TStack<double>  st;
		Split str(output);

		string lexsema = str.GetLex(' ');

		while (lexsema != "")
		{
			int k = lexsema.length();
			if (lexsema[0] >= '0' && lexsema[0] <= '9'|| lexsema[0]=='-'&& lexsema.length()>1
				|| lexsema[0] >= 'a' && lexsema[0] <= 'z')
			{ 
				double r;
				if (lexsema[0] >= 'a' && lexsema[0] <= 'z')
				{
					cout << lexsema << " = ";
					cin >> r;
				}
				else
				{
					r = atof(lexsema.c_str());
				}
				st.Put(r);
			}
			else
			{
				double a = st.Get();
				double b = st.Get();

				// ����� ��� �������� �� ����� � ��������� ��������
				result = oper(a, b, lexsema[0]);
				st.Put(result);

			}
			lexsema = str.GetLex(' ');
		}
		result = st.Get();
		return result;
	}

	double GetResult()
	{
		return result;
	}

	double oper(double a, double b, char code)
	{
		switch (code)
		{
		case '+':
			return a + b;
		case '-':
			return  b - a;
		case '*':
			return a * b;
		case '/':
			if (a == 0)
			{
				std::cout << " not devision 0" << endl;
				throw "devision by 0";
				return 0;
			}

			return b / a;
		default:
			return 0;
		}
	}

	int Prioritet(char op)
	{
		switch (op)
		{
		case'(':
			return 1;

		case '+':
		case '-':
			return 2;

		case '*':
		case '/':
			return 3;

		default:
			throw "unknown operation";
			return -1;
		}
	}
};
