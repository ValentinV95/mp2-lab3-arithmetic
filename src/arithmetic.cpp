#include "arithmetic.h"

std::string deleteSpaces(std::string str) {
    for (size_t i = 0; i < str.size(); i++)
        if (str[i] == ' ')
            str.erase(str.begin() + i);
    return str;
}

short priority(char operation) {
    if (operation == '+' || operation == '-')
        return 1;
    else if (operation == '*' || operation == '/')
        return 2;
    return 0;
}

Ssize_t leftCharacter(std::string str, size_t index) {
    Ssize_t i;
    for (i = index - 1; i >= 0 && str[i] == ' '; i--);
    return i;
}

size_t rightCharacter(std::string str, size_t index) {
    size_t i;
    size_t n = str.size();
    for (i = index + 1; i <= n && str[i] == ' '; i++);
    return i;
}

bool isSymbolsCorrect(std::string str) {
    size_t n = str.size();
    for (size_t i = 0; i < n; i++) {
        if (!(str[i] == '.' || str[i] >= '0' && str[i] <= '9' ||
            str[i] == '+' || str[i] == '*' || str[i] == '-' || str[i] == '/' ||
            str[i] == '(' || str[i] == ')' || str[i] == ' ')) {
            std::cout << "Incorrect symbol in position " << i + 1 << "." << std::endl;
            printPointer(str, i + 1);
            return false;
        }
    }
    return true;
}

void printPointer(std::string str, size_t index) { //печать места ошибки
    index--;
    size_t n = str.size();

    std::cout << str;
    std::cout << std::endl;
    size_t i;
    for (i = 0; i < index; i++)
        std::cout << ' ';
    std::cout << '^';
    for (i++; i < n; i++)
        std::cout << ' ';
    std::cout << std::endl;
}

void arithmetic::transform(std::string str) {
    str = deleteSpaces(str);

    TStack<char> stack;
    size_t n = str.size();
    for (size_t i = 0; i < n; i++)
        if (str[i] >= '0' && str[i] <= '9' || str[i] == '.') {
            for (; i < n &&
                str[i] >= '0' && str[i] <= '9' || str[i] == '.';
                i++)
                res.push_back(str[i]);
            i--;
            res.push_back(' ');
        }
        else if (str[i] == '-' && (i == 0 || str[i - 1] == '('))
            stack.push('_');
        else if (str[i] == '(')
            stack.push(str[i]);
        else if (str[i] == ')') {
            while (stack.top() != '(')
                res.push_back(stack.pop());
            stack.pop();
        }
        else if (str[i] == '+' || str[i] == '*' ||
            str[i] == '-' || str[i] == '/') {
            while (!stack.empty() && (stack.top() == '_'
                || priority(stack.top()) >= priority(str[i])))
                res.push_back(stack.pop());
            stack.push(str[i]);
        }
    while (!stack.empty())
        res.push_back(stack.pop());
}

double arithmetic::count() const {
    TStack<double> stack;

    size_t n = res.size();
    for (size_t i = 0; i < n; i++)
        if (res[i] >= '0' && res[i] <= '9' || res[i] == '.') {
            double numb = 0;
            for (; i < n && res[i] >= '0' && res[i] <= '9'; i++)
                numb = numb * 10 + (res[i] - '0');

            if (res[i] == '.') {
                double divide = 1;
                for (i++; i < n && res[i] >= '0' && res[i] <= '9'; i++) {
                    numb = numb * 10 + (res[i] - '0');
                    divide *= 10;
                }
                numb /= divide;
            }

            stack.push(numb);
            i--;
        }
        else if (res[i] == '+' || res[i] == '*' ||
            res[i] == '-' || res[i] == '/') {
            double b = stack.pop();
            double a = stack.pop();
            if (res[i] == '+')
                stack.push(a + b);
            else if (res[i] == '-')
                stack.push(a - b);
            else if (res[i] == '*')
                stack.push(a * b);
            else if (res[i] == '/')
                stack.push(a / b);
        }
        else if (res[i] == '_')
            stack.push(stack.pop() * -1);

    return stack.pop();
}

bool arithmetic::isCorrect(std::string str) {
    TStack<size_t> stack;
    size_t n = str.size();

    if (!isSymbolsCorrect(str))
        return false;

    for (size_t i = 0; i < n; i++) {
        if (str[i] == '(')
            stack.push(i);
        else if (str[i] == ')') {
            if (stack.empty()) {
                std::cout << "Missed opening brake for brake in position " << i + 1 << "." << std::endl;
                printPointer(str, i + 1);
                return false;
            }
            stack.pop();
        }
        else if (str[i] == '.' || str[i] >= '0' && str[i] <= '9') { //начало числа
            Ssize_t ind = leftCharacter(str, i);
            if (ind != -1)
                if (str[ind] == ')') {
                    std::cout << "Missed operator in position " << ind + 2 << "." << std::endl;
                    printPointer(str, ind + 2);
                    return false;
                }
                else if (str[ind] >= '0' && str[ind] <= '9' || str[ind] == '.') {
                    std::cout << "Extra operand in position " << i + 1 << "." << std::endl;
                    printPointer(str, i + 1);
                    return false;
                }
            if (str[i] >= '0' && str[i] <= '9')
                for (i += 1; i < n && str[i] >= '0' && str[i] <= '9'; i++); //нужно перебрать число до точки или пробела

            if (i != n && str[i] == '.') {
                size_t ind2 = rightCharacter(str, i);
                if (ind2 != n && str[ind2] == '.') {
                    std::cout << "Extra point in position " << ind2 + 1 << "." << std::endl;
                    printPointer(str, ind2 + 1);
                    return false;
                }
                i++;   //уходим от точки
                for (; i < n && str[i] >= '0' && str[i] <= '9'; i++); //нужно перебрать число после точки
            }
            size_t ind2 = (i == n ? n : rightCharacter(str, i - 1)); //берём последнюю цифру/точку и убираем пробелы от неё вправо

            if (ind2 != n && str[ind2] == '(') {
                std::cout << "Missed operator in position " << i + 1 << "." << std::endl;  //лишний элемент проверится выше (проверка влево)
                printPointer(str, i + 1);
                return false;
            }
            else
                i--;        //необрабатываемый символ, возвращаем курсор на него
        }
        else if (str[i] == '+' || str[i] == '*' || str[i] == '/' || str[i] == '-') {
            Ssize_t ind = leftCharacter(str, i);

            if (ind == -1)
                if (str[i] == '-')
                    continue;
                else {
                    std::cout << "Missed operand before operator in position " << i + 1 << "." << std::endl;
                    printPointer(str, i + 1);
                    return false;
                }

            if (!(str[ind] == '.' || str[ind] >= '0' && str[ind] <= '9' || //если до знака стоит точка или цифра
                str[ind] == ')' ||                                            //или если скобка до знака закрывающая
                (str[i] == '-' && str[ind] == '('))) {                        //или если знак - минус и до него стоит открывающая скобка
                std::cout << "Missed operand in position " << i + 2 << "." << std::endl;
                printPointer(str, i + 2);
                return false;
            }

            size_t ind2 = rightCharacter(str, i);

            if (ind2 == n) {
                std::cout << "Missed operand in position " << i + 2 << "." << std::endl;
                printPointer(str, i + 2);
                return false;
            }
            if (!(str[ind2] == '.' || str[ind2] >= '0' && str[ind2] <= '9' ||
                str[ind2] == '(')) {
                std::cout << "Missed operand in position " << i + 2 << "." << std::endl;
                printPointer(str, i + 2);
                return false;
            }
        }
    }

    if (!stack.empty()) {
        std::cout << "Missed closing brake for brake in position " << stack.top() + 1 << "." << std::endl;
        printPointer(str, stack.top() + 1);
        return false;
    }

    return true;
}
