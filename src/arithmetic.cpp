#include "arithmetic.h"

map<string, double> variables;

bool isDot(const char& ch)
{
    bool flag = (ch == '.');
    return flag;
}

bool isOperation(const char& ch)
{
    bool flag = (ch == '+' || ch == '*' ||
        ch == '-' || ch == '/');
    return flag;
}

bool isOperation(const Token& tok) 
{
    bool flag = (tok == MUL) || (tok == PLUS) ||
                (tok == MINUS) || (tok == DIV);
    return flag;
}

bool isBracket(const char& ch)
{
    bool flag = (ch == '(' || ch == ')');
    return flag;
}

bool isFunction(const string& name) 
{
    bool flag = (name == "sin") || (name == "cos") ||
                (name == "exp") || (name == "log");
    return flag;
}

bool isFunction(const Token& tok) 
{
    bool flag = (tok == SIN) || (tok == COS) ||
                (tok == EXP) || (tok == LOG) || (tok == UNARY_MINUS);
    return flag;
}

int getPriority(const Token& tok)
{
    int priority;
    if (tok == PLUS || tok == MINUS) {
        priority = 0;
    }
    else if (tok == MUL || tok == DIV) {
        priority = 1;
    }
    else if (tok == RP || tok == LP) {
        priority = -1;
    }
    else if (isFunction(tok)) {
        priority = 2;
    } 
    else {
        throw Exception("cannot return priority");
    }
    return priority;
}

double stringToDouble(string str, size_t* pos)
{
    // начиная с позиции pos в строке str выписваем отдельно число

    string strNumber; // строка в которую выписываем посимвольно число 

    // собираем целую часть числа
    while (isdigit(str[*pos])) {
        strNumber.push_back(str[(*pos)++]);
    }

    if (isDot(str[(*pos)])) {
        strNumber.push_back(str[(*pos)++]);
        // собираем дробную часть числа
        while (isdigit(str[(*pos)])) {
            strNumber.push_back(str[(*pos)++]);
        }
    }

    double res = atof(strNumber.c_str());

    (*pos)--; // теперь pos указывает на последную цифру в числе

    return res;
}

Lexems convertToArrayLexem(string str)
{
    Lexems lexemsArray;
    size_t length = str.length();

    // цикл по строке
    for (size_t i = 0; i < length; i++) {
         if (isspace(str[i])) {
             // пропускаем пробельные символы
             continue;
         }
         else if (isdigit(str[i]) || isDot(str[i])) {
            // если i-ый символ строки - цифра
            // добавляем в поле tokens значение NUMBER
            lexemsArray.tokens.push_back(NUMBER);

            // начиная с i-ой позиции считываем из строки число 
            double val = stringToDouble(str, &i);

            // добавлем считанное значение в очередь values
            lexemsArray.values.push(val);
        }
        else if (isOperation(str[i]) || isBracket(str[i])) {
            // преобразовываем char в Token и добавляем в tokens
            Token tok = Token(str[i]);

            if (str[i] == '-' && !lexemsArray.tokens.empty()) {
                // обрабатываем случай унарного минуса
                if (lexemsArray.tokens.back() == LP) {
                    // унарный минус идёт только после '('
                    tok = UNARY_MINUS;
                }
            }
            else if (str[i] == '-' && i == 0) {
                // случай, когда унарный минус стоит в начале выражения
                tok = UNARY_MINUS;
            }

            lexemsArray.tokens.push_back(tok);
        }
        else if (isalpha(str[i])) {
            // если i-ый символ строки - буква латинского алфавита

            string name;
            // записываем имя переменной
            while (isalnum(str[i])) {
                name.push_back(str[i++]);
                if (i >= length) {
                    break;
                }
                else if (isFunction(name)) {
                    break;
                }
            }
            // уменьшаем индекс на единицу для корректного прохода по строке
            i--;

            // проверяем не является ли имя переменной названием функции
            if (name == "sin") {
                lexemsArray.tokens.push_back(SIN);
            }
            else if (name == "cos") {
                lexemsArray.tokens.push_back(COS);
            }
            else if (name == "exp") {
                lexemsArray.tokens.push_back(EXP);
            }
            else if (name == "log") {
                lexemsArray.tokens.push_back(LOG);
            } else {
                // если нашем именем оказалась не функция
                // то инициализируем переменную
                double val;
                // ищем переменную в глобальном списке переменных
                if (variables.count(name) >= 1) {
                    // получаем из списка переменных нужное значение
                    val = variables[name];
                } else {
                    // если в глобальном списке переменной нет
                    // просим пользователя ввести значение переменной
                    cout << "enter variable value " <<  name << " = ";
                    cin >> val;
                    // добавляем перменную в глобальный список
                    variables[name] = val;
                }

                lexemsArray.tokens.push_back(NUMBER);
                lexemsArray.values.push(val);
            }
         
        }
        else {
            string error = "invalid character";
            error += " '";
            error += str[i];
            error += "'";
            throw Exception(error);
        }
    }

    return lexemsArray;
}

bool isCorrect(const Lexems& lexemsArray)
{
    int counterBracket = 0;

    Token first = lexemsArray.tokens.front();
    // первый символ не может быть операцией или ')'
    if (first == RP) {
        throw Exception("closing bracket cannot be at the beginning");
    }
    else if (isOperation(first)) {
        throw Exception("operation cannot be at the beginning");
    }

    Token last = lexemsArray.tokens.back();
    // последний символ не может быть унарным минусом, операцией или '('
    if (isOperation(last)) {
        throw Exception("operation cannot be at the end");
    }
    else if (last == LP) {
        throw Exception("opening bracket cannot be at the end");
    }
    else if (last == UNARY_MINUS) {
        throw Exception("unary minus cannot be at the end");
    }

    for (size_t i = 0; i < lexemsArray.tokens.size() - 1; i++) {

        Token curr = lexemsArray.tokens[i];
        Token next = lexemsArray.tokens[i + 1];
        
        // после числа не может идти число, функция или ')'
        if ((curr == NUMBER) && (next == LP)) {
            throw Exception("'(' cannot be after number");
        }
        else if ((curr == NUMBER) && (next == NUMBER)) {
            throw Exception("number cannot be after number");
        }
        else if ((curr == NUMBER) && isFunction(next)) {
            throw Exception("function cannot be after number");
        }

        // после функции (кроме унарного минуса) должен идти '('
        // после унарного минуса может идти только число или '('
        if (isFunction(curr) && (curr != UNARY_MINUS) && (next != LP)) {
            throw Exception("after funciton can be only '('");
        }
        else if ((curr == UNARY_MINUS) && (next != NUMBER) && (next != LP)) {
            throw Exception("after unary minus can be only number or '('");
        }

        // после операции не может идти унарный минус, операция или '('
        if (isOperation(curr) && (next == RP)) {
            throw Exception("')' cannot be after operation");
        }
        else if (isOperation(curr) && (next == UNARY_MINUS)) {
            throw Exception("unary minus cannot be after");
        }
        else if (isOperation(curr) && isOperation(next)) {
            throw Exception("operation cannot be after operation");
        }

        // после ')' может идти только операция или ')' 
        if ((curr == RP) && ((next != RP) && !isOperation(next))) {
            throw Exception("after ')' can be only operation or ')'");
        }

        // после '(' не может идти ')' или операция
        if ((curr == LP) && (next == RP)) {
            throw Exception("')' cannot be after '('");
        }
        else if ((curr == LP) && isOperation(next)) {
            throw Exception("operation cannot be after '('");
        }

        // считаем колличество открывающих и закрывающих скобок
        if (next == RP) {
            counterBracket++;
        }
        else if (curr == LP) {
            counterBracket--;
        }
    }

    // обрабатываем случаи когда не хватает (или есть лишние) скобок
    if (counterBracket > 0) {
        throw Exception("closing brackets more than opening brackets");
    }
    else if (counterBracket < 0) {
        throw Exception("opening brackets more than closing brackets");
    }

    return true;
}

Lexems convertToRpn(const Lexems& lexemArray)
{
    Lexems rpn; // результирующий массив лексем 
                // в который мы будем записывать обратную польскую запись

    TStack<Token> operations; // стек операций
    queue<double> vals = lexemArray.values; // очередь значений сохраняем отдельно

    for (auto it : lexemArray.tokens) {

        if (it == NUMBER) {
            // если встретилось число, добавляем его в результирующий массив
            // добавляем в массив типов тип NUMBER
            rpn.tokens.push_back(NUMBER);
            // извлкаем из очереди число
            double val = vals.front();
            vals.pop();
            // добавляем число в очередь значений 
            rpn.values.push(val);
        }
        else if ((it == LP) || isFunction(it)) {
            // открывающую скобку или функцию всегда добавляем в стек
            operations.push(it);
        }
        else if (it == RP) {
            // до тех пор пока в стеке не встретилась открывающая скобка
            // достаем из стека операции и добавляем их в опз
            Token top = operations.getTop();
            while (top != LP) {
                rpn.tokens.push_back(operations.pop());
                top = operations.getTop();
            }

            // убираем открывающую скобку
            operations.pop();
        }
        else if (isOperation(it)) {
            while (!operations.isEmpty()) {
                Token top = operations.getTop();

                // сравниваем приоритет пришедшей операции и операции верхней в стеке
                if (getPriority(top) < getPriority(it)) {
                    break;
                }

                // если приоритет пришедшей операции меньше равен верхней,
                // то достаем из стека операцию и добавляем ее в опз
                rpn.tokens.push_back(operations.pop());
            }
            // пришедшею операцию добавляем в стек
            operations.push(it);
        }
        else {
            throw Exception("cannot convert to rpn. Invalid lexem");
        }

    }

    // записываем в опз, операции которые оставлись в стеке
    while (!operations.isEmpty()) {
        rpn.tokens.push_back(operations.pop());
    }

    return rpn;
}


// функция возращает результат бинарной операции
double calcBinaryOperation(const double& op1, const double& op2, const Token& tok)
{
    if (tok == PLUS) {
        return op1 + op2;
    }
    else if (tok == MINUS) {
        return op1 - op2;
    }
    else if (tok == MUL) {
        return op1 * op2;
    }
    else if (tok == DIV) {
        if (op2 == 0.0) {
            throw Exception("divide by null");
        }
        return op1 / op2;
    }
    else {
        throw Exception("non-existent operation");
    }
}

// функция возращает результат вычисления математической функции
double calcFunc(const double& arg, const Token& tok)
{
    if (tok == SIN) {
        return sin(arg);
    }
    else if (tok == COS) {
        return cos(arg);
    }
    else if (tok == EXP) {
        return exp(arg);
    }
    else if (tok == LOG) {
        return log(arg);
    }
    else if (tok == UNARY_MINUS) {
        return (-1.0)*arg; 
    } else {
        throw Exception("cannot calculate function: invalid function");
    }
}

double computeResult(Lexems rpn)
{
    TStack<double> operands; // стэк значений операндов

    for (auto it : rpn.tokens) {
        if (it == NUMBER) {
            // извлекаем операнд из очереди значений и помещаем его в стек
            double val = rpn.values.front();
            rpn.values.pop();
            operands.push(val);
        }
        else if (isFunction(it)) {
            // достаем с вершины стека аргумент функции
            double arg = operands.pop();

            // высчитываем значение функции от полученного аргумента
            double fx = calcFunc(arg, it);

            // помещаем его в стек
            operands.push(fx);
        }
        else {
            // достаем с вершины стека два операнда
            double op2 = operands.pop();
            double op1 = operands.pop();
            // вычисляем результат бинарной операции и помещаем его в стек
            double res = calcBinaryOperation(op1, op2, it);
            operands.push(res);
        }
    }

    // возращаем результат, который лежит на вершине стека
    return operands.pop();
}
