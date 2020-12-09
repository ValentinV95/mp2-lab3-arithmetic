// реализация пользовательского приложения

#include "Arithmetic.h"

int main()
{
    try
   {
        Arithmetic a1;
        cout << "Write your term:" << endl << "Term is:";
        string str;
        getline(cin, str);
        cout << "Term is after translting str:";
        a1.translateStrToTerm(str);
         a1.PrintVecT();
         cout << "PolishNote: ";
        a1.TermToPolishNote();
        a1.PrintVectP();
        cout << "Result term:";
        a1.calculate();
    }
    catch (char* error) 
    {
        cout << error << endl;
    }
}
