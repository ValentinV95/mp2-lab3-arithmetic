#include "arithmetic.h"


TFormula::TFormula()
{
	n = 0;
}

TFormula::TFormula(string s)
{
	formula=s;
	this->Converter();
}

TFormula::~TFormula()
{
	n = 0;
	formula.clear();
	lecs.clear();
	rev_lecs.clear();
}

void TFormula::Write()
{
	getline(cin, formula);
	this->Converter();
	cout << formula << endl;
}

bool TFormula::Checker()
{
	int n_brace = 0;//количество скобок
	int i = 0;
	int indicator=1;//индикатор корректности выражения
	while (i < lecs.size()-1)
	{
		//если текущая лексема число, то следующая лексема либо унарный минус, либо открывающая скобка
		if (lecs[i].isNum)
			if((!lecs[i + 1].isNum) && (lecs[i + 1].b != UN_MINUS) && (lecs[i + 1].b != O_BRACE))
			;
			else
			{
				indicator = 0;
				cout << "Введен недопустимый символ после числа!" << endl;
			}

		//если текущая лексема открывающая скобка, то следующая лексема либо число, либо открывающая скобка,либо унарный минус
		if ((!lecs[i].isNum) && (lecs[i].b == O_BRACE))
		{
			if (((!lecs[i + 1].isNum) && ((lecs[i + 1].b == O_BRACE)|| (lecs[i + 1].b ==UN_MINUS))) || (lecs[i + 1].isNum))
				;
			else
			{
				indicator = 0;
				cout<<"Ввведен недопустимый символ после открывающей скобки!" << endl;
			}
			n_brace++;
		}

		//если текущая лексема закрывающая скобка, то следующая лексема либо операция, либо закрывающая скобка
		if ((!lecs[i].isNum) && (lecs[i].b == C_BRACE))
		{
			if (((!lecs[i + 1].isNum) && (lecs[i + 1].b !=O_BRACE)))
				;
			else
			{
				indicator = 0;
				cout<< "Введен недопустимый символ после закрывающей скобки!" << endl;
			}
			n_brace--;
		}

		//если текущая лексема операция, то следующая лексема либо число, либо закрывающая скобка, либо унарный минус
		if ((!lecs[i].isNum) && (lecs[i].b != C_BRACE) && (lecs[i].b != O_BRACE))
		{
			if ((lecs[i + 1].isNum) || ((!lecs[i + 1].isNum) && ((lecs[i + 1].b == O_BRACE) || (lecs[i + 1].b == UN_MINUS))))
				;
			else
			{
				indicator = 0;
				cout<<"Введен недопусимый символ после операции!" << endl;
			}
		}

		//Проверка порядка скобок
		if (n_brace >= 0)
			;
		else
		{
			indicator = 0;
			cout<< "Введен неправильный порядок скобок!" << endl;
		}
		i++;
	}

	/*В данной реализации выражение заключается в скобки, 
	поэтому последний элемент заведомо закрывающая скобка, которую надо учесть.*/
			n_brace--;

	//Проверка количества скобок
	if(n_brace==0)
	 ;
	else
	{
		cout << "Введено некорректное число скобок!" << endl;
		indicator = 0;
	}

	if (indicator)
	{
		return true;
	}	
	else
	{
		this->~TFormula();
		return false;
	}
}

void TFormula::Converter()
{
	int i = 0;
	string number;
	Lecsema temp;

	//обработка первого элемента
	temp.isNum = false;
	temp.b = O_BRACE;
	lecs.push_back(temp);

	while (i < formula.size())
	{
		
			switch (formula[i])
			{
			case '+':
			{
				temp.isNum = false; temp.b = PLUS;
				lecs.push_back(temp);
				break;
			}
			case '-':
			{
				if ((lecs.back().b != C_BRACE) && (!lecs.back().isNum))
				{
					temp.isNum = false; temp.b = UN_MINUS;//унарный минус
				}
				else
				{
					temp.isNum = false; temp.b = MINUS;//бинарный минус
				}
				lecs.push_back(temp);
				break;
			}
			case '*':
			{
				temp.isNum = false; temp.b = MULT;
				lecs.push_back(temp);
				break;
			}
			case '/':
			{
				temp.isNum = false; temp.b = DIV;
				lecs.push_back(temp);
				break;
			}
			case '(':
			{
				temp.isNum = false; temp.b = O_BRACE;
				lecs.push_back(temp);
				break;
			}
			case ')':
			{
				temp.isNum = false; temp.b = C_BRACE;
				lecs.push_back(temp);
				break;
			}
			default:
			{
				break;
			}
			}
			if (((formula[i] <= '9') && (formula[i] >= '0')) || (formula[i] == '.'))//встретилась цифра, начинается процесс записи числа
			{
				while (((formula[i] <= '9') && (formula[i] >= '0')) || (formula[i] == '.')) {//накопление числа в переменную number
					number.push_back(formula[i]); i++;
				}
				i--;
				temp.isNum = true;
				temp.a = stod(number);
				lecs.push_back(temp);
				number.clear();
			}
		i++;
	}

	temp.isNum = false;
	temp.b = C_BRACE;
	lecs.push_back(temp);
	n = lecs.size();
	/*печать вектора лексем(только на этапе отладки)
	for (int i = 0; i < n; i++)
		if(lecs[i].isNum)
			cout << lecs[i].a<<endl;
		else 
			cout << lecs[i].b<<endl;
			*/
}

void TFormula::Postfix_Entry()
{
	Lecsema temp;
	int i = 0; 
	Stack <Op> T(n);
	int Prior[7] = {2,2,3,3,0,1,4};//таблица приоритетов 

	while (i<n)
	{
		//если текущая лексема открывающая скобка
		if ((lecs[i].b == O_BRACE)&&(lecs[i].isNum == false))
		{
			temp.b = lecs[i].b;
			T.Push(temp.b);
		}
		else
		{
			//если текущая лексема число
			if (lecs[i].isNum) 
			{
				temp.a = lecs[i].a;
				temp.isNum = true;
				rev_lecs.push_back(temp);
			}
			else
				if (!T.isEmpty())
				{
					//если текущая лексема закрывающая скобка
					if (Prior[lecs[i].b] == 1)
					{
						//выполняем все операции до открывающей скобки
						while (T.Value() != O_BRACE)
						{
							temp.b = T.Pop();
							temp.isNum = false;
							rev_lecs.push_back(temp);
						}
						T.Pop();

					}
					//если текущая лексема операция
					else
					{
						//если текущая лексема унарный минус, и предыдущая лексема тоже унарный минус
						if((T.Value()==UN_MINUS)&&(lecs[i].b==UN_MINUS))
						{
							T.Push(lecs[i].b);
						}
						//если текущая лексема бинарная операция или впервые встретившийся унарный минус
						else
						{
							/*сравнение приоритетов текущей операции и операции из стека.
							Выполняем операции из стека до тех пор, 
							пока приоритет текущей операции меньше или равен приоритету операции в стеке*/
							while ((!T.isEmpty()) && (Prior[T.Value()] >= Prior[lecs[i].b]))
							{
								temp.b = T.Pop();
								temp.isNum = false;
								rev_lecs.push_back(temp);
							}
							T.Push(lecs[i].b);
						}
					}
				}
				else T.Push(lecs[i].b);
		}
	i++;	
	}
	//выполняем все оставшиеся в стеке операции
	while (!T.isEmpty())
	{
		temp.b = T.Pop(); 
		temp.isNum = false;
		rev_lecs.push_back(temp);
	}
	/*печать обратной польской записи(только на этапе отладки)
    for (int i = 0; i < rev_lecs.size(); i++)
		if (rev_lecs[i].isNum)
			cout << rev_lecs[i].a << endl;
		else
			cout << rev_lecs[i].b << endl;
			*/
}

double TFormula::Calculator()
{
	this->Postfix_Entry();

	Stack <double> T(rev_lecs.size());
	double a, b;
	
	for (int i = 0; i < rev_lecs.size(); i++)
	{
		//если число
		if (rev_lecs[i].isNum)
			T.Push(rev_lecs[i].a);
		//если операция
		else
		{
			if (rev_lecs[i].b == UN_MINUS)
			{
				a = T.Pop();
				T.Push((-1)*a);
			}
			else
			{
				b = T.Pop();
				a = T.Pop();
				switch (rev_lecs[i].b)
				{
				case PLUS:	T.Push(a + b); break;
				case MINUS:	T.Push(a - b); break;
				case MULT:	T.Push(a * b); break;
				case DIV:	T.Push(a / b); break;
				default:break;
				}
			}
		}
	}
	return T.Pop();
}