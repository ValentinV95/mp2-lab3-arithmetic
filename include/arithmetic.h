// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#ifndef __ARITHMETIC_

#define __ARITHMETIC_

#include <iostream>
#include <string>
#include <stdexcept>
#include "stack.h"

typedef int Ssize_t;

class arithmetic {
public:
    arithmetic(std::string str) {
        if (isCorrect(str))
            transform(str);
        else
            throw std::invalid_argument("String is incorrect."); //проверка до трансформации
    }

    static bool isCorrect(std::string str);
    double count() const;
    
private:
    void transform(std::string str);
    std::string res;
};

std::string deleteSpaces(std::string str);

short priority(char operation);

Ssize_t leftCharacter(std::string str, size_t index);

size_t rightCharacter(std::string str, size_t index);

bool isSymbolsCorrect(std::string str);

void printPointer(std::string str, size_t index);

#endif
