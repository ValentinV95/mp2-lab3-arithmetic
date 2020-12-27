#include <iostream>
#include <string>
#include "interface.h"
#include "arithmetic.h"

int main() {
    char c;
    std::string str;
    while (true) {
        menu();
        c = choose();
        switch (c) {
        case 'c':
            std::cout << "Enter expression: " << std::endl;
            std::getline(std::cin, str);
            if (arithmetic::isCorrect(str))
                std::cout << "Expression is correct." << std::endl;
            break;
        case 'r':
            c = choose2();
            if (c == 'n') {
                std::cout << "Enter expression: " << std::endl;
                std::getline(std::cin, str);
            }
            if (arithmetic::isCorrect(str))
                std::cout << "Count of exspression: " << arithmetic(str).count() << std::endl;
            break;
        case 'e':
            std::cout << "Program is over." << std::endl;
            return 0;
        }
    }

    return 0;
}
