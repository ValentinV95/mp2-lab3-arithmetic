#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__

#include <vector>
#include <queue>
#include <map>
#include "stack.h"

using namespace std;

// перечисление, которое предназначенно для хранения типа лексемы
enum Token 
{
    NUMBER,
    SIN, COS, EXP, LOG, UNARY_MINUS,
    LP = '(', RP = ')',
    PLUS = '+', MINUS = '-', MUL = '*', DIV = '/',
};

// Lexems - класс, который предстваляет из себя массив лексем.
// tokens - массив с типами лексем, для каждой лексемы типа NUMBER
// есть свое числовое значение из очереди value, лексемы же остальных 
// типов имееют свое значение, которое им было предписано в перечеслении Token
class Lexems
{
    public:
        queue<double> values;
        vector<Token> tokens;
        bool operator==(const Lexems& lex) const 
        {
            return (values == lex.values) && (tokens == lex.tokens);
        }
        void print()
        {
            cout << endl;
            for (size_t i = 0; i < tokens.size(); i++) {
                cout << tokens[i] << " ";
            }
            cout << endl;
            queue<double> vals = values;
            while (!vals.empty()) {
                cout << vals.front();
                 vals.pop();
            }
        }
};

extern map<string, double> variables;  //список глобальных переменных, задаваймых пользователем

bool isDot(const char& ch);       // функция определяет является ли данный символ точкой 
bool isOperation(const char& ch); // функция определяет является ли данный символ операцией
bool isOperation(const Token& tok);      // функция определяет является ли данный знак операцией
bool isBracket(const char& ch);   // функция определяет является ли данный символ скобкой
bool isFunction(const Token& tok);       // функция определяет является ли данный знак функцией
bool isFunction(const string& name);     // функция определяет является ли строка названием функции

int getPriority(const Token& tok);    // функций возращает приоритет операции 

double stringToDouble(string str, size_t* pos); // функция начиная с позиции pos извлекает из строки str число 

Lexems convertToArrayLexem(string str); // функция преобразовывает строку в массив лексем

bool isCorrect(const Lexems& lexemsArray); // функция проверяет арифметическое выражение на корректность

Lexems convertToRpn(const Lexems& lexemArray); // функция преобразует массив лексем в обратную польскую запись

double computeResult(Lexems rpn); // функция вычисляет результат выражения по обратной пользой записи

#endif