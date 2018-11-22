// реализация пользовательского приложения

#include "arithmetic.h"


string getNewString()
{
    string newString;
    getline(cin, newString);
    return newString;
}

int main()
{
    while (cin) {
        try {
            // получаем строку из командной строки
            string str = getNewString();
            // преобразовываем полученную строку в массив лексем
            Lexems arithmeticExp = convertToArrayLexem(str);
           
            // проверяем на корректность арифметическое выражение
            if (arithmeticExp.tokens.empty()) {
                cout << endl;
            } else if (isCorrect(arithmeticExp)) {
                // преобразовавыем арифм. выражение в опз
                Lexems rpn = convertToRpn(arithmeticExp);
                // считаем результат выражения по опз
                double res = computeResult(rpn);
                cout << res << endl;
            }
        }
        catch (Exception) {
            cerr << "press enter and repeat";
        } 
    }
    system("pause");
    return 0;
}
